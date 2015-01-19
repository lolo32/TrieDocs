#include "traduction.h"

#include <QLocale>
#include <QDir>
#include <QDirIterator>
#include <QApplication>

Traduction traduction;

QString MajPremierCaractere( QString chaine )
{
    chaine[0] = chaine.at(0).toTitleCase();
    return chaine;
}

Traduction::Traduction() :
    p_bCharge(false),
    QObject()
{
}

void Traduction::initialise()
{
    QLocale locale;

    // On récupère la langue de l’utilisateur
    p_qszLangActuelle = QLocale::system().name(); // ex: "fr_FR"
    p_qszLangActuelle.truncate(p_qszLangActuelle.lastIndexOf('_')); // ex: "fr"

    // On ajoute la langue C, qui est le fr
    locale = QLocale( "fr" );
    QLocale::setDefault(locale);
    struct langue langue = {
        MajPremierCaractere( locale.nativeLanguageName() ),
        QString("fr")
    };
    p_Langues.append( langue );

    // On recherche la liste des langues incluses
    QDir dir( ":/i18n/" );
    QStringList fichiers = dir.entryList( QStringList("*.qm") );

    for (int i=0; i<fichiers.size(); ++i) {
        // récupère les traductions par le nom
        QString iso;
        iso = fichiers[i];                    // ex: "en.qm"
        iso.truncate( iso.lastIndexOf('.') ); // ex: "en"

        locale = QLocale( iso );
        langue.nom = MajPremierCaractere( locale.nativeLanguageName() );
        langue.iso = iso;

        p_Langues.append( langue );
    }

    // On trie par ordre croissant
    qSort( p_Langues.begin(), p_Langues.end(), Traduction::trieLangues);

    p_bCharge = true;
}

Traduction::~Traduction()
{

}

void Traduction::rempli(QMenu *menu, QWidget *parent)
{
    if( !p_bCharge )
        initialise();

    QActionGroup *groupeLangue = new QActionGroup(menu);
    groupeLangue->setExclusive(true);

    connect(groupeLangue, SIGNAL(triggered(QAction*)), parent, SLOT(slotLangueChangee(QAction*)));

    for (int i=0; i<p_Langues.size(); ++i) {
        struct langue langue = p_Langues.at(i);
        QIcon ico( QString(":/langs/%1.svg").arg(langue.iso) );

        QAction *action = new QAction( ico, langue.nom, menu );
        action->setCheckable(true);
        action->setData(langue.iso);
        if( p_qszLangActuelle == langue.iso )
            action->setChecked(true);

        menu->addAction(action);
    }
}

void Traduction::rempli(QComboBox *combo)
{
    if( !p_bCharge )
        initialise();

    // On vide la liste
    combo->clear();

    for (int i=0; i<p_Langues.size(); ++i) {
        struct langue langue = p_Langues.at(i);
        combo->insertItem(i, QIcon(QString(":/langs/%1.svg").arg(langue.iso)), langue.nom);
        if( langue.iso == p_qszLangActuelle ) {
            combo->setCurrentIndex(i);
        }
    }
}

bool Traduction::trieLangues(const struct langue &a, const struct langue &b)
{
    return a.nom < b.nom;
}

bool Traduction::set(int index)
{
    QString iso = p_Langues[index].iso;

    // test si la langue passée est différente de l’actuelle
    if(p_qszLangActuelle != iso) {
        // On recharge l’interface avec la nouvelle langue

        QLocale langue(iso);
        QLocale::setDefault(langue);

        qApp->removeTranslator(&p_traducteur);
        QString fichier = QString(":/i18n/%1.qm").arg(iso);
        bool charge = p_traducteur.load( fichier );
        if( charge )
            qApp->installTranslator( &p_traducteur );

        p_qszLangActuelle = iso;

        return true;
    }
    else
        return false;
}

bool Traduction::set(QString iso)
{
    for( int i=0; i<p_Langues.size(); ++i ) {
        if( p_Langues[i].iso == iso )
            return set(i);
    }
    return false;
}
