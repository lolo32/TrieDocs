#include "dlgclient.h"

#include "traduction.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QEvent>
#include <QPushButton>

/**
 * @brief Constructeur
 * @param qszServeur[in] nom du serveur sur lequel établir la connexion
 * @param parent[in]
 */
DlgClient::DlgClient(QString qszServeur, QWidget *parent) :
    QDialog(parent),
    p_qszServeur(qszServeur),
    p_initialise(false),
    strStatut(QString())
{
    // On génère l'affichage
    // Le texte est ajouté plus loin, par la méthode retranslateUI()
    //       +--------------------------------+
    //       |         lblStatut              |
    //       |    Message d'information       |
    //       +--------------------------------+
    //       | _txtLogin______login__________ |
    //       | _txtPasword____mot de passe___ |
    //       | lblLangue         cbxLangues ▾ |
    //       |        btnBox      Cancel OK   |
    //       +--------------------------------+
    this->resize(400, 222);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    lblStatut = new QLabel(this);
    lblStatut->setAlignment(Qt::AlignCenter);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(1);
    lblStatut->setSizePolicy(sizePolicy);
    mainLayout->addWidget(lblStatut);

    QVBoxLayout *verticalLayout = new QVBoxLayout();

    txtLogin = new QLineEdit(this);
    txtLogin->setInputMethodHints(Qt::ImhNoAutoUppercase|Qt::ImhPreferLowercase);
    txtLogin->setAlignment(Qt::AlignCenter);
    verticalLayout->addWidget(txtLogin);

    txtPassword = new QLineEdit(this);
    txtPassword->setEchoMode(QLineEdit::Password);
    txtPassword->setAlignment(Qt::AlignCenter);
    verticalLayout->addWidget(txtPassword);

    mainLayout->addLayout(verticalLayout);

    QHBoxLayout *horizonLayout = new QHBoxLayout();

    lblLangue = new QLabel(this);
    horizonLayout->addWidget(lblLangue);

    cbxLangues = new QComboBox(this);
    sizePolicy = QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(1);
    sizePolicy.setVerticalStretch(0);
    cbxLangues->setSizePolicy(sizePolicy);
    horizonLayout->addWidget(cbxLangues);

    mainLayout->addLayout(horizonLayout);

    btnBox = new QDialogButtonBox(this);
    btnBox->setStandardButtons( QDialogButtonBox::Cancel | QDialogButtonBox::Ok );
    mainLayout->addWidget(btnBox);

    connect(btnBox, SIGNAL(accepted()), this, SLOT(on_btnBox_accepted()));
    connect(btnBox, SIGNAL(rejected()), this, SLOT(reject()));

    setTabOrder(txtLogin, txtPassword);
    setTabOrder(txtPassword, cbxLangues);

    retranslateUi();

    // Remplit la liste du choix des langues
    traduction.rempli(cbxLangues);
    p_initialise = true;

//    QMetaObject::connectSlotsByName(this);
}

/**
 * @brief Destructeur
 */
DlgClient::~DlgClient()
{

}

/**
 * @brief Met à jour le message à afficher dans la zone de statut
 */
void DlgClient::setStatutTexte()
{
    QString str;
    if( strStatut == QStringLiteral("") ) {
        str = tr("Veuillez vous identifier pour accéder aux documents");
    } else {
         str = strStatut;
    }
    lblStatut->setText( str );
}

/**
 * @brief Définit les textes à afficher des éléments, en effectuant les traductions
 */
void DlgClient::retranslateUi()
{
    this->setWindowTitle( tr("Identification") );
    txtLogin->setPlaceholderText( tr("Identifiant de connexion") );
    txtPassword->setPlaceholderText( tr("Mot de passe") );
    lblLangue->setText( tr("Langue :") );
    setStatutTexte();

    QPushButton *btn = btnBox->button(QDialogButtonBox::Ok);
    btn->setText( tr("OK") );
    btn = btnBox->button(QDialogButtonBox::Cancel);
    btn->setText( tr("Annuler") );
}

/**
 * @brief Fonction appelée lorsque l’utilisateur valide ses identifiants, et lançant la connexion/identification
 *
 * Cette fonction a pour but de vérifier les informations de connexion saisis par l’utilisateur en envoyant au serveur le
 * nom d’utilisateur ainsi que le mot de passe
 */
void DlgClient::on_btnBox_accepted()
{
    QString nom = txtLogin->text();
    QString mdp = txtPassword->text();

    /*
     * TODO: Gestion de la connexion et vérification des identifiants
     */
    strStatut = tr("Établissement de la connexion avec le serveur %1").arg( p_qszServeur );
    setStatutTexte();
}

/**
 * @brief Gestion des évènements de la fenêtre
 * @param event[in] id de l’évènement
 */
void DlgClient::changeEvent(QEvent * event)
{
    if(0 != event)
    {
        switch(event->type())
        {
            // this event is send if a translator is loaded
            case QEvent::LanguageChange:
                retranslateUi();
                break;
            // this event is send, if the system, language changes
            case QEvent::LocaleChange:
                {
                    QString locale = QLocale::system().name();
                    locale.truncate(locale.lastIndexOf( QChar::fromLatin1('_') ));
                    traduction.set(locale);
                    retranslateUi();
                }
                break;
            default:
                break;
        }
    }

    QDialog::changeEvent(event);
}
