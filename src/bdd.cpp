#include "bdd.h"

#include "libmyminiz.h"

#include <QFile>
#include <QDir>
#include <QStandardPaths>

class Bdd bdd;

// Fonctions appelées pour compresser/decompresser les données
static void sqlcmd_compress( sqlite3_context *, int, sqlite3_value ** );
static void sqlcmd_decompress( sqlite3_context *,int, sqlite3_value ** );

// Se connecte à la base de données
bool Bdd::OuvreBdd()
{
    bool existe = false;
    QString qszBdd = QStandardPaths::writableLocation( QStandardPaths::DataLocation );
    QDir bddRep( qszBdd );

    // Vérifie si le répertoire existe, et le crée sinon
    if( ! bddRep.exists() ) {
        bddRep.mkpath( qszBdd );
    }

    qszBdd.append( QDir::separator() ).append( _szBdNomFichier.c_str() );
    qszBdd = QDir::toNativeSeparators( qszBdd );
    if( QFile::exists( qszBdd ) ) {
        existe = true;
    }

    int ret = sqlite3_initialize();
    if( ret != SQLITE_OK ) {
        SetLastError(ret);
        return false;
    }

    do {
        ret = sqlite3_open(qszBdd.toUtf8().constData(), &_db);
        if( ret != SQLITE_OK )
            break;

        ret = sqlite3_create_function(_db, "compress", 1, SQLITE_UTF8, 0, sqlcmd_compress, 0, 0);
        if( ret != SQLITE_OK ) break;
        ret = sqlite3_create_function(_db, "decompress", 1, SQLITE_UTF8, 0, sqlcmd_decompress, 0, 0);
        if( ret != SQLITE_OK ) break;

        if( ! existe ) {

            // La base de données n'existe pas, on la crée

            // Ouvre la ressource de création de la base de données
            QFile bdCreateFile(":/res/db.sql");
            bdCreateFile.open(QIODevice::ReadOnly | QIODevice::Text);
            QString bdCreateScript;

            bdCreateScript
                    .append( QStringLiteral("BEGIN;") )
                    .append( bdCreateFile.readAll() )
                    .append( QStringLiteral("COMMIT;") );

            // Crée la base
            bool b = ExecuteSQL( bdCreateScript.toUtf8().constData() );
            if( !b ) {
                break;
            }

        } else {

            // La base de données existe déjà
            // On vérifie la version de la base, et la met à jour le cas échéant
            unsigned int bd_version;
            sqlite3_stmt *stmt = 0;
            const char requete[] = "SELECT parametre, valeur FROM conf WHERE parametre = 'version';";
            int len = strlen(requete) + 1;
            ret = sqlite3_prepare_v2(_db, requete, len, &stmt, 0);
            ret = sqlite3_step(stmt);
            bd_version = sqlite3_column_int(stmt, 1);
            ret = sqlite3_finalize(stmt);

            if( bd_version != _iBdProgramVersion ) {
                // Effectuer la mise à jour de la base de données à partir d'ici

                // Ouvre une base de données temporaire pour effectuer la maj
                sqlite3 *bdd_prive = 0;
                ret = sqlite3_open("", &bdd_prive);

                //
                // TODO Procédure de maj

                // On ferme la base de données temporaire pour la maj
                sqlite3_close(bdd_prive);
            }
        }

        return true;
    } while (0);

    SetLastError(ret);
    return ! FermeBdd();
}

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

// Exécute toutes les requetes
bool Bdd::ExecuteSQL(const char * sql)
{
    int ret;

    sqlite3_stmt *stmt = 0;
    const char *restant = sql;
    while ( *restant ) {
        const char *old = restant;
        restant = 0;
        int len = strlen(old) + 1;
        ret = sqlite3_prepare_v2(_db, old, len, &stmt, &restant);
        do {
            ret = sqlite3_step(stmt);
        } while (ret == SQLITE_ROW); // Ré-exécute si il y a plusieurs lignes en attente
        if( ret != SQLITE_DONE)
            goto annuler;
        ret = sqlite3_finalize(stmt);
    }

    return true;

annuler:
    sqlite3_prepare_v2(_db, "ROLLBACK;", 10, &stmt, 0);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    _szLastError = QObject::tr("").toStdString();
    return false;
}

bool Bdd::Compresser()
{
    return ExecuteSQL("VACUUM;");
}

QString Bdd::LastError()
{
    return QObject::tr( _szLastError.c_str() );
}

void Bdd::SetLastError(int sqlite3_interr)
{
    if( ! sqlite3_interr )
        return;

    // Messages d'erreurs depuis les sources de sqlite3_UTF8
    const char* const aMsg[] = {
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "erreur de logique SQL ou base de données manquante"),
        0,
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "accès refusé"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "la fonction de retours a demandé l'annulation de la requète"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "base de données verrouillée"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "table verrouillée"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "mémoire insuffisante"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "tentative d'écriture dans une base de données en lecture seule"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "interrompu"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "erreur d'entrée/sortie du disque"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "la base de donnée est corrompue"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "opération inconnue"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "base de données ou disque plein"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "impossible d'ouvrir le fichier de la base de données"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "protocole bloqué"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "la table est vide"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "le schéma de la base de données a changé"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "texte ou binaire trop long"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "échec de contrainte"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "type de donnée incorrect"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "routine de bibliothèque appelé hors de la séquence"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "support des grands fichiers désactivé"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "autorisation refusée"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "erreur de format de base de données auxiliaire"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "bind ou index de colonne hors de la plage"),
        QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "le fichier est chiffré ou n'est pas une base de données")
    };
    const char* zErr = QT_TRANSLATE_NOOP_UTF8("sqlite_msgerr", "erreur inconnue");
    int i = --sqlite3_interr;
    if( aMsg[i] != 0 )
        zErr = aMsg[i];

    SetLastError(zErr);
}

void Bdd::SetLastError(std::string msg)
{
    _szLastError = msg;
}

// ----------------------------------------
// Code de fossil-scm.org
//     http://www.fossil-scm.org/fossil/artifact/c81155ddf8865c49bedeb771e051df0ca5dd2c9d
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
  int rc;

  (void)argc;

  pIn = (const unsigned char*)sqlite3_value_blob(argv[0]);
  nIn = sqlite3_value_bytes(argv[0]);
  nOut = (pIn[0]<<24) + (pIn[1]<<16) + (pIn[2]<<8) + pIn[3];
  pOut = (unsigned char*)sqlite3_malloc( nOut+1 );
  rc = mz_uncompress(pOut, &nOut, &pIn[4], nIn-4);
  if( rc==Z_OK ){
    sqlite3_result_blob(context, pOut, nOut, sqlite3_free);
  }else{
    sqlite3_result_error(context, "input is not zlib compressed", -1);
  }
}