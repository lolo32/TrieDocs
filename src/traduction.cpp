#include "traduction.h"

#include <QApplication>
#include <QComboBox>
#include <QDir>
#include <QDirIterator>
#include <QIcon>
#if INCLUT_QT_TRADS
#  include <QLibraryInfo>
#endif
#include <QMenu>
#include <QLocale>

Traduction traduction;

/**
 * @brief Permet de mettre une majuscule sur le premier caractère de la chaîne
 * @param chaine[in] Chaîne dont le premier caractère doit être mit en majuscule
 * @return La chaîne de caractères, avec la majuscule au début
 */
inline QString MajPremierCaractere( QString chaine )
{
    chaine[0] = chaine.at(0).toTitleCase();
    return chaine;
}

/**
 * @brief Constructeur
 */
Traduction::Traduction() :
    p_bCharge(false),
    p_qszLangActuelle( QLatin1String("fr") ),
    QObject()
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
    struct langue langue = {
        MajPremierCaractere( locale.nativeLanguageName() ),
        QLatin1String("fr")
    };
    p_Langues.append( langue );

    // On recherche la liste des langues incluses
    QDir dir( QStringLiteral(":/i18n/") );
    QStringList fichiers = dir.entryList( QStringList( QStringLiteral("*.qm") ) );

    for (int i=0; i<fichiers.size(); ++i) {
        // récupère les traductions par le nom
        QString iso;
        iso = fichiers[i];                                         // ex: "en.qm"
        iso.truncate( iso.lastIndexOf( QChar::fromLatin1('.') ) ); // ex: "en"

        locale = QLocale( iso );
        langue.nom = MajPremierCaractere( locale.nativeLanguageName() );
        langue.iso = iso;

        p_Langues.append( langue );
    }

    // On trie par ordre croissant
    qSort( p_Langues.begin(), p_Langues.end(), Traduction::trieLangues);

    // On tente de charger la langue par la langue de l’utilisateur
    this->set(qszLangueActuelle);

    p_bCharge = true;
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
        QIcon ico( QString( QLatin1String(":/langs/%1.svg") ).arg(langue.iso) );

        QAction *action = new QAction( ico, langue.nom, menu );
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
        combo->insertItem(i, QIcon(QString( QLatin1String(":/langs/%1.svg") ).arg(langue.iso)), langue.nom);
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
inline bool Traduction::trieLangues(const struct langue &a, const struct langue &b)
{
    return a.nom < b.nom;
}

/**
 * @brief Charge un nuveau fichier de traduction et le passe à l’application
 * @param fichier[in]     Chemin vers le .qm à charger
 * @param traducteur[out] QTranslator devant charger la traduction
 * @return  true si la traduction a été correctement chargée
 * @return  fakse en cas d’erreur
 */
inline bool Traduction::chargeTraducteur(const QString & fichier, QTranslator & traducteur)
{
    bool charge = traducteur.load( fichier );
    if( charge )
        charge = qApp->installTranslator( &traducteur );
    return charge;
}

/**
 * @brief Définit la nouvelle langue par le numéro d'index
 * @param index[in] index de la nouvelle langue devant être chargée
 * @return true si on a changé de langue
 * @return false sinon (erreur ou langue actuelle)
 */
bool Traduction::set(unsigned int index)
{
    // Vérifie que l’index est valide et ne dépasse pas le nombre de langues
    if(index >= p_Langues.count())
        return false;

    QString iso = p_Langues[index].iso;

    // test si la langue passée est différente de l’actuelle
    if( !p_bCharge || p_qszLangActuelle != iso) {
        // On recharge l’interface avec la nouvelle langue

        bool ret;

        QLocale langue(iso);
        QLocale::setDefault(langue);

        // Un traducteur a déjà été chargé, on le supprime si langue précédente != "C"
        if( p_qszLangActuelle != QLatin1String("fr") )
            ret = qApp->removeTranslator(&p_traducteur);
#if INCLUT_QT_TRADS
        if( p_qszLangActuelle != QLatin1String("en") )
            ret = qApp->removeTranslator(&p_traducteurQT);
#endif

        QString fichier;
        if( iso != QLatin1String("fr") ) {
            // La nouvelle langue est dfférente de "C"="fr", on charge un nouveau traducteur
            fichier = QString( QLatin1String(":/i18n/%1.qm") ).arg(iso);
            this->chargeTraducteur(fichier, p_traducteur);
        }
#if INCLUT_QT_TRADS
        if( iso != QLatin1String("en") ) {
            fichier = QLibraryInfo::location(QLibraryInfo::TranslationsPath)
                    .append(QDir::separator())
                    .append( QStringLiteral("qt_") )
                    .append(iso);
            this->chargeTraducteur(fichier, p_traducteurQT);
        }
#endif

        p_qszLangActuelle = iso;

        return true;
    }
    else
        return false;
}

/**
 * @brief Définit la nouvelle langue par son code iso
 * @param iso[in] code iso de la nouvelle langue à charger
 * @return true si on a changé de langue
 * @return false sinon (erreur ou langue actuelle)
 */
bool Traduction::set(QString iso)
{
    for( int i=0; i<p_Langues.size(); ++i ) {
        if( p_Langues[i].iso == iso )
            return set(i);
    }
    return false;
}

void Traduction::retranslateUi(QEvent *event, WidgetTraduit *widget)
{
    if(0 != event)
    {
        switch(event->type())
        {
            // this event is send, if the system, language changes
            case QEvent::LocaleChange:
                {
                    QString locale = QLocale::system().name();
                    locale.truncate(locale.lastIndexOf( QChar::fromLatin1('_') ));
                    this->set(locale);
                }
            // this event is send if a translator is loaded
            case QEvent::LanguageChange:
                widget->retranslateUi();
                return;
            default:
                return;
        }
    }
}
