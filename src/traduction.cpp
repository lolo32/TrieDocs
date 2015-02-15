#include "commun.h"
#include "traduction.h"

#include <QApplication>
#include <QComboBox>
#include <QDir>
#include <QDirIterator>
#include <QIcon>
#include <QMenu>
#include <QLocale>

Traduction traduction;

struct Traduction::langue Traduction::nomLangue(const QString &fichier, const QString &iso)
{
   QTranslator trad;

   trad.load( fichier );

   //: This is the language name of the file (ex: English, Español, Français, Русский)
   QString langue = trad.translate("Language", "Language name", "Translation informations");

   //: This is the translators name
   QString personne = trad.translate("Language", "Translators names", "Translation informations");

   struct langue ret;

   ret.iso = iso;
   ret.nom = langue.size() ? langue : QStringLiteral("Fran\303\247ais");
   ret.traducteurs = personne.size() ? personne : QStringLiteral("Laurent B.");

   return ret;
}

/**
 * @brief Constructeur
 */
Traduction::Traduction() :
   QObject(),
   p_qszLangActuelle( QLatin1String("fr") ),
   p_bCharge(false)
{

}

/**
 * @brief Destructeur
 */
Traduction::~Traduction()
{

}

/**
 * @brief Génère la liste des traductions disponibles dans les ressources
 */
void Traduction::initialise()
{
   QLocale locale;
   QString qszLangueActuelle;

   // On récupère la langue de l’utilisateur
   qszLangueActuelle = QLocale::system().name(); // ex: "fr_FR"
   qszLangueActuelle.truncate(qszLangueActuelle.lastIndexOf( QChar::fromLatin1('_') )); // ex: "fr"

   // On ajoute la langue C, qui est le fr
   locale = QLocale( QStringLiteral("fr") );
   QLocale::setDefault(locale);
   struct langue langue = nomLangue( QStringLiteral("fr"), QStringLiteral("fr") );
   p_Langues.append( langue );

   // On recherche la liste des langues incluses
   QDir dir( QStringLiteral(":/i18n/") );
   QStringList fichiers = dir.entryList( QStringList( QStringLiteral("*.qm") ), QDir::Files );

   QStringListIterator iterator(fichiers);
   while( iterator.hasNext() ) {
      // récupère les traductions par le nom
      QString nomFichier = iterator.next();
      QString iso = nomFichier;                                       // ex: "triedocs_en.qm"
      iso = iso.mid(9, iso.lastIndexOf( QChar::fromLatin1('.') )-9 ); // ex: "en"

      langue = nomLangue( dir.filePath( nomFichier ), iso );

      p_Langues.append( langue );
   }

   // On trie par ordre croissant
   qSort( p_Langues.begin(), p_Langues.end(), Traduction::trieLangues);

   // On tente de charger la langue par la langue de l’utilisateur
   this->set(qszLangueActuelle);

   p_bCharge = true;
}

/**
 * @brief Traduction::getLangName
 * @return le nom de la langue actuelle
 */
QString Traduction::getLangName()
{
   QListIterator<struct langue> iterator(p_Langues);
   while( iterator.hasNext() ) {
      const struct langue langue = iterator.next();
      if( langue.iso == p_qszLangActuelle)
         return langue.nom;
   }
   return QString();
}

/**
 * @brief Traduction::getTranslatorsName
 * @return
 */
QString Traduction::getTranslatorsName()
{
   QListIterator<struct langue> iterator(p_Langues);
   while( iterator.hasNext() ) {
      const struct langue langue = iterator.next();
      if( langue.iso == p_qszLangActuelle)
         return langue.traducteurs;
   }
   return QString();
}

/**
 * @brief Génère la liste des langues dans un menu
 * @param menu[in] menu devant contenir la liste des langues
 */
void Traduction::rempli(QMenu *menu)
{
   if( !p_bCharge )
      initialise();

   QActionGroup *groupeLangue = new QActionGroup(menu);
   groupeLangue->setExclusive(true);

   connect(groupeLangue, SIGNAL(triggered(QAction*)), SLOT(slotLangueChangee(QAction*)));

   for (int i=0; i<p_Langues.size(); ++i) {
      struct langue langue = p_Langues.at(i);
      QIcon ico;
      ico.addFile(
            QString( QLatin1String(":/langs/%1.svg") ).arg(langue.iso),
            QSize(),
            QIcon::Normal,
            QIcon::Off
      );

      QAction *action = new QAction( langue.nom, menu );
      action->setIcon(ico);
      action->setCheckable(true);
      action->setData(langue.iso);
      if( p_qszLangActuelle == langue.iso )
      action->setChecked(true);

      menu->addAction(action);
   }
}

/**
 * @brief Génère la liste des langues dans une liste déroulante
 * @param combo[in] liste déroulante devant contenir la liste des langues
 */
void Traduction::rempli(QComboBox *combo)
{
   if( !p_bCharge )
      initialise();

   // On vide la liste
   combo->clear();

   for (int i=0; i<p_Langues.size(); ++i) {
      struct langue langue = p_Langues.at(i);
      combo->insertItem(
            i,
            QIcon(QString( QLatin1String(":/langs/%1.svg") ).arg(langue.iso)),
            langue.nom
      );
      if( langue.iso == p_qszLangActuelle ) {
         combo->setCurrentIndex(i);
      }
   }

   connect(combo, SIGNAL(currentIndexChanged(int)), SLOT(slotLangueChangee(int)));
}

void Traduction::slotLangueChangee(int index)
{
    this->set(index);
}

/**
 * @brief Fonction déclenchée lorsque on choisit une autre langue dans le menu
 * @param action[in]
 */
void Traduction::slotLangueChangee(QAction *action)
{
   if( action != 0 ) {
      // Charge le nouveau language
      this->set(action->data().toString());
   }
}

/**
 * @brief Traduction::trieLangues
 * @param a
 * @param b
 * @return a < b
 */
inline bool Traduction::trieLangues(const struct langue &lang_a, const struct langue &lang_b)
{
   return lang_a.nom < lang_b.nom;
}

/**
 * @brief Définit la nouvelle langue par le numéro d'index
 * @param index[in] index de la nouvelle langue devant être chargée
 * @return true si on a changé de langue
 * @return false sinon (erreur ou langue actuelle)
 */
__attribute__((annotate("oclint:suppress[long method]")))
bool Traduction::set(unsigned int index)
{
   QString iso = p_Langues[index].iso;

   if(   // Vérifie que l’index est valide et ne dépasse pas le nombre de langues
         index >= p_Langues.count()

         // Vérifie que l’on a déjà initialisé les traducteurs, retourne sinon
      || !p_bCharge

         // Est-ce que la langue passée est la langue actuelle ?
      || p_qszLangActuelle == iso
   )
      return false;

   // On recharge l’interface avec la nouvelle langue

   QLocale langue(iso);
   QLocale::setDefault(langue);

   // Un traducteur a déjà été chargé, on le supprime
   while( p_traducteurs.size() ) {
      QTranslator *trad = p_traducteurs.first();
      qApp->removeTranslator( trad );
      p_traducteurs.removeFirst();
      delete trad;
   }

   // Vérifie si la nouvelle langue est "fr", auquel cas, il n’y a plus rien à faire
   if( iso == QStringLiteral("fr") )
      return true;

   // La nouvelle langue est dfférente de "C"="fr", on charge un nouveau traducteur
   QString fichier = QString( QLatin1String("triedocs_%1") ).arg(iso);

   // Génère la liste des dossiers pouvant contenir les traductions "XXXX.qm"
   static QStringList dossiers;
   if( !dossiers.size() )
      dossiers
              << QStringLiteral(":/i18n") // Répertoire interne
              << QDir::currentPath();     // Répertoire courant de travail de l’application

   // On tente de charger les traductions correspondant à la langue
   QStringListIterator iterator(dossiers);
   while( iterator.hasNext() ) {

      QTranslator *trad = new QTranslator();

      // Tente le chargement du fichier ".qm"
      bool traducteurOk = trad->load(fichier, iterator.next());

      if( traducteurOk )
         // Traduction chargée avec succès, on l’installe dans l’application
         traducteurOk = qApp->installTranslator( trad );

      if( traducteurOk )
         // Traduction ajoutée à l’application avec succès, on l’ajoute à la liste des
         // traducteurs pour pouvoir les supprimer plus tard en cas de changement de langue
         p_traducteurs.append( trad );

      else
         delete trad;
   }

   p_qszLangActuelle = iso;

   return true;
}

/**
 * @brief Définit la nouvelle langue par son code iso
 * @param iso[in] code iso de la nouvelle langue à charger
 * @return true si on a changé de langue
 * @return false sinon (erreur ou langue actuelle)
 */
bool Traduction::set(QString iso)
{
   int specialise = 1;

   do{

      for( int i=0; i<p_Langues.size(); ++i ) {
         if( p_Langues[i].iso == iso )
            return set(i);
      }

      // Comme la langue n’a pas été trouvée, on cherche de manière généraliste
      // "en_US" devient donc "en" par exemple
      iso.truncate(iso.lastIndexOf( QChar::fromLatin1('_') ));

      // On relance une tentative, avec la nouvelle langue

   } while(specialise--);

   return false;
}

/**
 * @brief Fonction appelée lorsque les fenêtres reçoivent un évènement
 * @param event[in]  nom de l’évènement reçu
 * @param widget[in] widget ayant reçu l’évènement
 */
void Traduction::retranslateUi(QEvent *event, WidgetTraduit *widget)
{
   if(0 != event)
   {

      // this event is send, if the system, language changes
      if(event->type() == QEvent::LocaleChange) {
         this->set(QLocale::system().name()); // Avec la locale de la forme "en_US"
         widget->retranslateUi();
         return;
      }

      // this event is send if a translator is loaded
      if( event->type() == QEvent::LanguageChange ) {
         widget->retranslateUi();
         return;
      }

   }
}

/**
 * @brief Retourne le numéro du mois correspondant au mois anglais, sur 3 lettres ou entier
 * @param strMois[in] le nom du mois, ou l’abréviation sur 3 lettres en anglais
 * @return Le numéro du mois
 */
__attribute__((
   annotate("oclint:suppress[long method]"),
   annotate("oclint:suppress[high cyclomatic complexity]"),
   annotate("oclint:suppress[high ncss method]"),
))
int Traduction::getMoisAnglais(const QString & strMois) const
{
   if(strMois.size() == 3) {

      if (strMois == QLatin1String("Jan") )
         return 1;
      else if(strMois == QLatin1String("Feb") )
         return 2;
      else if(strMois == QLatin1String("Mar") )
         return 3;
      else if(strMois == QLatin1String("Apr") )
         return 4;
      else if(strMois == QLatin1String("May") )
         return 5;
      else if(strMois == QLatin1String("Jun") )
         return 6;
      else if(strMois == QLatin1String("Jul") )
         return 7;
      else if(strMois == QLatin1String("Aug") )
         return 8;
      else if(strMois == QLatin1String("Sep") )
         return 9;
      else if(strMois == QLatin1String("Oct") )
         return 10;
      else if(strMois == QLatin1String("Nov") )
         return 11;
      else if(strMois == QLatin1String("Dec") )
         return 12;

   } else { //if(strMois.size() == 3)

      if (strMois == QLatin1String("January") )
         return 1;
      else if(strMois == QLatin1String("Febrary") )
         return 2;
      else if(strMois == QLatin1String("March") )
         return 3;
      else if(strMois == QLatin1String("April") )
         return 4;
      // May est fait par la condition du dessus
      else if(strMois == QLatin1String("June") )
         return 6;
      else if(strMois == QLatin1String("July") )
         return 7;
      else if(strMois == QLatin1String("August") )
         return 8;
      else if(strMois == QLatin1String("September") )
         return 9;
      else if(strMois == QLatin1String("October") )
         return 10;
      else if(strMois == QLatin1String("November") )
         return 11;
      else if(strMois == QLatin1String("December") )
         return 12;
   }

   return -1;
}
