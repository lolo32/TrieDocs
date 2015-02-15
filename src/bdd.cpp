#include "commun.h"
#include "bdd.h"

#include "miniz.c"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QStandardPaths>

class Bdd bdd;

// Fonctions appelées pour compresser/decompresser les données
static void sqlcmd_compress( sqlite3_context *, int, sqlite3_value ** );
static void sqlcmd_decompress( sqlite3_context *,int, sqlite3_value ** );

/**
 * @brief destructeur
 */
Bdd::~Bdd()
{
   sqlite3_shutdown();
}

/**
 * @brief Se connecte à la base de données, gère les mises à niveau de la bdd
 * @return true en cas d'ouverture avec succès
 * @return false si une erreur est survenu durant l'ouverture
 */
__attribute__((
   annotate("oclint:suppress[avoid branching statement as last in loop]"),
   annotate("oclint:suppress[long method]"),
   annotate("oclint:suppress[high ncss method]")
))
bool Bdd::OuvreBdd()
{
   bool existe = false;
   QString qszBdd = QStandardPaths::writableLocation( QStandardPaths::DataLocation );
   QDir bddRep( qszBdd );

   // Vérifie si le répertoire existe, et le crée sinon
   if( ! bddRep.exists() ) {
      bddRep.mkpath( qszBdd );
   }

   // Détermine si la base de données existé déjà (présence du fichier)
   qszBdd.append( QDir::separator() ).append( QString::fromStdString(_szBdNomFichier) );
   qszBdd = QDir::toNativeSeparators( qszBdd );
   if( QFile::exists( qszBdd ) ) {
      existe = true;
   }

   // Initialise SQlite3
   int ret = sqlite3_initialize();
   if( ret != SQLITE_OK ) {
      SetLastError(ret);
      return false;
   }

   do {
      // Ouvre la base de données SQL
      ret = sqlite3_open(qszBdd.toUtf8().constData(), &_db);
      if( ret != SQLITE_OK )
         break;

      // Déclare les fonctions de compression/décompression
      ret = sqlite3_create_function(_db, "compress", 1, SQLITE_UTF8, 0, sqlcmd_compress, 0, 0);
      if( ret != SQLITE_OK )
          break;
      ret = sqlite3_create_function(_db, "decompress", 1, SQLITE_UTF8, 0, sqlcmd_decompress, 0, 0);
      if( ret != SQLITE_OK )
          break;

      if( existe ) {

         // La base de données existe déjà
         // On vérifie la version de la base, et la met à jour le cas échéant

         // On récupère le numéro de la version dans la base de données
         unsigned int bd_version;
         sqlite3_stmt *stmt = 0;
         // Requête de sélection
         const char requete[] = "SELECT parametre, valeur FROM conf WHERE parametre = 'version';";
         int len = strlen(requete) + 1;
         /*ret = */sqlite3_prepare_v2(_db, requete, len, &stmt, 0);
         /*ret = */sqlite3_step(stmt);
         bd_version = sqlite3_column_int(stmt, 1);
         /*ret = */sqlite3_finalize(stmt);

         if( bd_version != _iBdProgramVersion ) {
            // Effectuer la mise à jour de la base de données
            /*ret = */Maj(bd_version);
         }

      } else { // if( existe )

         // La base de données n'existe pas, on la crée
         Cree();

      } // else( existe )

      return true;

   } while (0);

   SetLastError(ret);
   return ! FermeBdd();
}

/**
 * @brief Crée la base de données et exécute les requêtes pour générer le schéma
 * @return 0 si aucune erreur lors de la création
 * @return 1 si une erreur est survenue
 */
int Bdd::Cree()
{
   // Ouvre la ressource de création de la base de données
   QFile bdCreateFile( QStringLiteral(":/res/db.sql") );
   bdCreateFile.open(QIODevice::ReadOnly | QIODevice::Text);
   QString bdCreateScript;

   bdCreateScript
         .append( QStringLiteral("BEGIN;") )
         .append( QString::fromUtf8( bdCreateFile.readAll() ) )
         .append( QStringLiteral("COMMIT;") );

   // Exécute les requêtes pour créer la base
   bool requete_ok = ExecuteSQL( bdCreateScript.toUtf8().constData() );
   if( requete_ok )
      // Création avec succès
      return 0;

   //else
   // Erreur lors de la création
   return -1;
}

/**
 * @brief Effectue la mise à jour de la base de données
 * @param version[in] numéro de version actuel de la base de données
 * @return
 */
int Bdd::Maj(int version)
{

//   int ret;

   // Ouvre une base de données temporaire pour effectuer la maj
   sqlite3 *bdd_prive = 0;
   /*ret = */sqlite3_open("", &bdd_prive);

   //
   // TODO Procédure de maj
   switch(version) {
      default:
      {
         // Numéro de version inconnu
         QMessageBox::critical(0,
               //: Invalid database version
               QApplication::translate("Bdd", "Version de base de donn\303\251es invalide"),

               //: The database version is not known.
               //: It may be created by a more recent version of TrieDocs.
               //:
               //: I can not continue and I will quit.
               QApplication::translate("Bdd",
                  "La version de la base de donn\303\251es n\342\200\231est pas reconnue.\n"
                  "Elle a peut-\303\252tre \303\251t\303\251 cr\303\251\303\251e par une version "
                     "de TrieDocs plus r\303\251cente.\n"
                  "\n"
                  "Je ne peux continuer et vais me fermer maintenant."
               ),
               QMessageBox::Ok,
               QMessageBox::Ok
         );

         qApp->exit(1);

         break;
      }
   }

   // On ferme la base de données temporaire pour la maj
   sqlite3_close(bdd_prive);

   return 0;
}

/**
 * @brief Ferme la base de données
 * @return true
 */
bool Bdd::FermeBdd()
{
   // ferme la base de données si elle a été ouverte précédement
   if( _db )
      sqlite3_close(_db);
   _db = 0;
   // Libère les ressources sqlite3
   sqlite3_shutdown();
   return true;
}

/**
 * @brief Exécute toutes les requetes
 * @param sql[in] la ou les requète(s) a exécuter
 * @return true si les requètes ont bien été exécutées
 * @return false si une requete n'a pas été exécutée
 */
__attribute__((annotate("oclint:suppress[goto statement]")))
    // Le goto sert à quitter le while, abandonner les modifications et nettoyer
bool Bdd::ExecuteSQL(const char * sql)
{
   int ret;

   sqlite3_stmt *stmt = 0;
   const char *restant = sql;
   while ( *restant ) {
      const char *old = restant;
      restant = 0;
      int len = strlen(old) + 1;
      /*ret = */sqlite3_prepare_v2(_db, old, len, &stmt, &restant);
      do {
         ret = sqlite3_step(stmt);
      } while (ret == SQLITE_ROW); // Ré-exécute si il y a plusieurs lignes en attente
      if( ret != SQLITE_DONE)
         goto annuler;
      /*ret = */sqlite3_finalize(stmt);
   }

   return true;

annuler:
   sqlite3_prepare_v2(_db, "ROLLBACK;", 10, &stmt, 0);
   sqlite3_step(stmt);
   sqlite3_finalize(stmt);
   _szLastError = QObject::tr("").toStdString();
   return false;
}

/**
 * @brief Exécute un nettoyage de la bdd
 * @return true si succès, false sinon
 */
bool Bdd::Compresser()
{
   return ExecuteSQL("VACUUM;");
}

/**
 * @brief Retourne la description de la dernière erreur SQL
 * @return la description de la dernière erreur SQL
 */
QString Bdd::LastError()
{
   return QObject::tr( _szLastError.c_str() );
}

/**
 * @brief définit la dernière erreur SQL par le code sqlite
 * @param sqlite3_interr[in] le code numérique de l'erreur
 */
__attribute__((annotate("oclint:suppress[long method]")))
void Bdd::SetLastError(int sqlite3_interr)
{
   if( ! sqlite3_interr )
      return;

   // Messages d'erreurs depuis les sources de sqlite3_UTF8
   const char* const aMsg[] = {
      //: SQL logic error or missing database
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "erreur de logique SQL ou base de donn\303\251es manquante"),
      0,
      //: access permission denied
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "acc\303\250s refus\303\251"),
      //: callback requested query abort
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "la fonction de retours a demand\303\251 l\342\200\231annulation de la requ\303\250te"),
      //: database is locked
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "base de donn\303\251es verrouill\303\251e"),
      //: database table is locked
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "table verrouill\303\251e"),
      //: out of memory
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "m\303\251moire insuffisante"),
      //: attempt to write a readonly database
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
        "tentative d\342\200\231\303\251criture dans une base de donn\303\251es en lecture seule"),
      //: interrupted
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "interrompu"),
      //: disk I/O error
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "erreur d\342\200\231entr\303\251e/sortie du disque"),
      //: database disk image is malformed
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "la base de donn\303\251e est corrompue"),
      //: unknown operation
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "op\303\251ration inconnue"),
      //: database or disk is full
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "base de donn\303\251es ou disque plein"),
      //: unable to open database file
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "impossible d\342\200\231ouvrir le fichier de la base de donn\303\251es"),
      //: locking protocol
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "protocole bloqu\303\251"),
      //: table contains no data
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "la table est vide"),
      //: database schema has changed
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "le sch\303\251ma de la base de donn\303\251es a chang\303\251"),
      //: string or blob too big
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "texte ou binaire trop long"),
      //: constraint failed
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "\303\251chec de contrainte"),
      //: datatype mismatch
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "type de donn\303\251e incorrect"),
      //: library routine called out of sequence
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "routine de biblioth\303\250que appel\303\251e hors de la s\303\251quence"),
      //: large file support is disabled
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "support des grands fichiers d\303\251sactiv\303\251"),
      //: authorization denied
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "autorisation refus\303\251e"),
      //: auxiliary database format error
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "erreur de format de base de donn\303\251es auxiliaire"),
      //: bind or column index out of range
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "bind ou index de colonne hors de la plage"),
      //: file is encrypted or is not a database
      QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr",
         "le fichier est chiffr\303\251 ou n\342\200\231est pas une base de donn\303\251es")
   };
   //: unknown error
   const char* zErr = QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "erreur inconnue");
   int index = --sqlite3_interr;
   if( aMsg[index] != 0 )
      zErr = aMsg[index];

   SetLastError(zErr);
}

/**
 * @brief définit la dernière erreur SQL en spécifiant un message
 * @param msg[in] la description de l'erreur
 */
void Bdd::SetLastError(std::string msg)
{
   _szLastError = msg;
}

// ----------------------------------------
// Code de fossil-scm.org
//    http://www.fossil-scm.org/fossil/artifact/c81155ddf8865c49bedeb771e051df0ca5dd2c9d
/*
** Implementation of the "compress(X)" SQL function.  The input X is
** compressed using zLib and the output is returned.
*/
static void sqlcmd_compress(
   sqlite3_context *context,
   int argc,
   sqlite3_value **argv
){
   const unsigned char *pIn;
   unsigned char *pOut;
   unsigned int nIn;
   unsigned long int nOut;

   (void)argc;

   pIn = (const unsigned char*)sqlite3_value_blob(argv[0]);
   nIn = sqlite3_value_bytes(argv[0]);
   nOut = 13 + nIn + (nIn+999)/1000;
   pOut = (unsigned char*)sqlite3_malloc( nOut+4 );
   pOut[0] = nIn>>24 & 0xff;
   pOut[1] = nIn>>16 & 0xff;
   pOut[2] = nIn>>8 & 0xff;
   pOut[3] = nIn & 0xff;
   mz_compress2(&pOut[4], &nOut, pIn, nIn, MZ_BEST_COMPRESSION);
   sqlite3_result_blob(context, pOut, nOut+4, sqlite3_free);
}

/*
** Implementation of the "decompress(X)" SQL function.  The argument X
** is a blob which was obtained from compress(Y).  The output will be
** the value Y.
*/
static void sqlcmd_decompress(
   sqlite3_context *context,
   int argc,
   sqlite3_value **argv
){
   const unsigned char *pIn;
   unsigned char *pOut;
   unsigned int nIn;
   unsigned long int nOut;
   int retUncompress;

   (void)argc;

   pIn = (const unsigned char*)sqlite3_value_blob(argv[0]);
   nIn = sqlite3_value_bytes(argv[0]);
   nOut = (pIn[0]<<24) + (pIn[1]<<16) + (pIn[2]<<8) + pIn[3];
   pOut = (unsigned char*)sqlite3_malloc( nOut+1 );
   retUncompress = mz_uncompress(pOut, &nOut, &pIn[4], nIn-4);
   if( retUncompress==Z_OK ){
      sqlite3_result_blob(context, pOut, nOut, sqlite3_free);
   }else{
      sqlite3_result_error(context, "input is not zlib compressed", -1);
   }
}
