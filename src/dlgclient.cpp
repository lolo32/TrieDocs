#include "commun.h"
#include "dlgclient.h"
#include "traduction.h"

#include <QComboBox>
#include <QDialogButtonBox>
#include <QEvent>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

/**
 * @brief Constructeur
 * @param qszServeur[in] nom du serveur sur lequel établir la connexion
 * @param parent[in]
 */
__attribute__((
   annotate("oclint:suppress[high ncss method]"),
   annotate("oclint:suppress[long method]"),
))
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

   // Création du lblStatut, zone de texte informative en haut de la fenêtre
   lblStatut = new QLabel(this);
   lblStatut->setAlignment(Qt::AlignCenter);
   QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
   sizePolicy.setHorizontalStretch(0);
   sizePolicy.setVerticalStretch(1);
   lblStatut->setSizePolicy(sizePolicy);
   mainLayout->addWidget(lblStatut);

   QVBoxLayout *verticalLayout = new QVBoxLayout();

   // Création du champ de saisie du nom d’utilisateur
   txtLogin = new QLineEdit(this);
   txtLogin->setInputMethodHints(Qt::ImhNoAutoUppercase|Qt::ImhPreferLowercase);
   txtLogin->setAlignment(Qt::AlignCenter);
   verticalLayout->addWidget(txtLogin);

   // Création du champ de saisie du mot de passe
   txtPassword = new QLineEdit(this);
   txtPassword->setEchoMode(QLineEdit::Password);
   txtPassword->setAlignment(Qt::AlignCenter);
   verticalLayout->addWidget(txtPassword);

   mainLayout->addLayout(verticalLayout);

   QHBoxLayout *horizonLayout = new QHBoxLayout();

   // Création du lblLangue, expliquant la signification de la liste déroulante suivante
   lblLangue = new QLabel(this);
   horizonLayout->addWidget(lblLangue);

   // Création de la liste déroulante contenant la liste des traductions de l’application
   // pour en changer
   cbxLangues = new QComboBox(this);
   sizePolicy = QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
   sizePolicy.setHorizontalStretch(1);
   sizePolicy.setVerticalStretch(0);
   cbxLangues->setSizePolicy(sizePolicy);
   horizonLayout->addWidget(cbxLangues);

   mainLayout->addLayout(horizonLayout);

   // Création des boutons de validation/annulation en bas
   QDialogButtonBox *btnBox = new QDialogButtonBox(this);
   btnOk = btnBox->addButton(QString(), QDialogButtonBox::AcceptRole);
   btnOk->setDefault(true);
   btnAnnuler = btnBox->addButton(QString(), QDialogButtonBox::RejectRole);
   mainLayout->addWidget(btnBox);

   // Indique les actions des boutons
   connect(btnBox, SIGNAL(accepted()), this, SLOT(on_btnBox_accepted()));
   connect(btnBox, SIGNAL(rejected()), this, SLOT(reject()));

   // Définit l’ordre des tabulations
   setTabOrder(txtLogin, txtPassword);
   setTabOrder(txtPassword, cbxLangues);
   setTabOrder(cbxLangues, btnBox);

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
      //: Please, login to access documents
      //~ Context Statut text on the top of the window
      str = tr("Veuillez vous identifier pour acc\303\251der aux documents");
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
   //: OK
   //~ Context Text on the OK button at the bottom
   btnOk->setText( tr("OK") );
   //: Cancel
   //~ Context Text on the cancel button at the bottom
   btnAnnuler->setText( tr("Annuler") );

   //: Identification
   //~ Context Window title
   this->setWindowTitle( tr("Identification") );
   //: Login
   //~ Context Place holder that indicate the use of the login input
   txtLogin->setPlaceholderText( tr("Identifiant de connexion") );
   //: Password
   //~ Context Place holder that indicate the use of the password input
   txtPassword->setPlaceholderText( tr("Mot de passe") );
   //: Language:
   //~ Context Text that explain the combobox (language switch)
   lblLangue->setText( tr("Langue\302\240:") );
   setStatutTexte();

   // Redimentionne la fenêtre à la taille optimale
this->adjustSize();
}

/**
 * @brief Fonction appelée pour valider les identifiants, et lançant la connexion/identification
 *
 * Cette fonction a pour but de vérifier les informations de connexion saisis par l’utilisateur
 * en envoyant au serveur le nom d’utilisateur ainsi que le mot de passe.
 */
void DlgClient::on_btnBox_accepted()
{
   QString nom = txtLogin->text();
   QString mdp = txtPassword->text();

   /*
   * TODO: Gestion de la connexion et vérification des identifiants
   */
   //: Connecting to server %1:"Server_name"
   //~ Context Statut text on the top of the window that explain the connection is establishing
   strStatut = tr("\303\211tablissement de la connexion avec le serveur %1").arg( p_qszServeur );
   setStatutTexte();

}

/**
 * @brief Gestion des évènements de la fenêtre
 * @param event[in] id de l’évènement
 */
void DlgClient::changeEvent(QEvent * event)
{
   traduction.retranslateUi(event, this);
   QDialog::changeEvent(event);
}
