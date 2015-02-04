#include "traduction.h"

#include <QApplication>
#include <QComboBox>
#include <QDir>
#include <QDirIterator>
#include <QIcon>
#include <QMenu>
#include <QLocale>

Traduction traduction;

QString Traduction::nomLangue(const QString &fichier)
{
    QTranslator trad;
    trad.load( fichier );
    //: This is the language name of the file
    QString langue = trad.translate("Language", "Fran\303\247ais");

    return langue.size() ? langue : QStringLiteral("Fran\303\247ais");
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
    struct langue langue = {
        nomLangue( QStringLiteral("fr") ),
        QLatin1String("fr")
    };
    p_Langues.append( langue );

    // On recherche la liste des langues incluses
    QDir dir( QStringLiteral(":/i18n/") );
    QStringList fichiers = dir.entryList( QStringList( QStringLiteral("*.qm") ), QDir::Files );

    QStringListIterator i(fichiers);
    while( i.hasNext() ) {
        // récupère les traductions par le nom
        QString nomFichier = i.next();
        QString iso = nomFichier;                                       // ex: "triedocs_en.qm"
        iso = iso.mid(9, iso.lastIndexOf( QChar::fromLatin1('.') )-9 ); // ex: "en"

        langue.nom = nomLangue( dir.filePath( nomFichier ) );
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
        QIcon ico;
        ico.addFile(QString( QLatin1String(":/langs/%1.svg") ).arg(langue.iso), QSize(), QIcon::Normal, QIcon::Off );

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
        while( p_traducteurs.size() ) {
            QTranslator *trad = p_traducteurs.first();
            ret = qApp->removeTranslator( trad );
            p_traducteurs.removeFirst();
            delete trad;
        }

        // La nouvelle langue est dfférente de "C"="fr", on charge un nouveau traducteur
        QString fichier = QString( QLatin1String("triedocs_%1") ).arg(iso);

        static QStringList dossiers;
        if( !dossiers.size() )
            dossiers
                    << QStringLiteral(":/i18n") // Répertoire interne
                    << QDir::currentPath();     // Répertoire courant de travail de l’application

        QStringListIterator i(dossiers);
        while( i.hasNext() ) {
            QTranslator *trad = new QTranslator();
            bool b = trad->isEmpty();
            bool ok = trad->load(fichier, i.next());
            b = trad->isEmpty();
            if( ok )
                ok = qApp->installTranslator( trad );

            if( ok )
                p_traducteurs.append( trad );
            else
                delete trad;
        }

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
