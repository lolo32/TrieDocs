#include "dlgclient.h"
#include "ui_dlgclient.h"

#include "traduction.h"

/**
 * @brief Constructeur
 * @param qszServeur[in] nom du serveur sur lequel établir la connexion
 * @param parent[in]
 */
DlgClient::DlgClient(QString qszServeur, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgClient),
    p_qszServeur(qszServeur),
    p_initialise(false)
{
    ui->setupUi(this);
    traduction.rempli(ui->cbxLangues);
    p_initialise = true;
}

/**
 * @brief Destructeur
 */
DlgClient::~DlgClient()
{
    delete ui;
}

/**
 * @brief Fonction appelée lorsque l’utilisateur valide ses identifiants, et lançant la connexion/identification
 *
 * Cette fonction a pour but de vérifier les informations de connexion saisis par l’utilisateur en envoyant au serveur le
 * nom d’utilisateur ainsi que le mot de passe
 */
void DlgClient::on_buttonBox_accepted()
{
    QString nom = ui->txtLogin->text();
    QString mdp = ui->txtPassword->text();

    QString statusMessage( tr("Établissement de la connexion avec le serveur %1").arg( p_qszServeur ) );
}

/**
 * @brief Changement de la langue dans la liste
 * @param index[in] index du nouvel élément dans la liste
 */
void DlgClient::on_cbxLangues_currentIndexChanged(int index)
{
    if( p_initialise )
        traduction.set(index);
}

void::DlgClient::changeEvent(QEvent * event)
{
    if(0 != event)
    {
        switch(event->type())
        {
            // this event is send if a translator is loaded
            case QEvent::LanguageChange:
                ui->retranslateUi(this);
//                traduction.rempli(ui->cbxLangues);
                break;
            // this event is send, if the system, language changes
            case QEvent::LocaleChange:
                {
                    QString locale = QLocale::system().name();
                    locale.truncate(locale.lastIndexOf('_'));
                    traduction.set(locale);
                }
                break;
            default:
                break;
        }
    }

    QDialog::changeEvent(event);
}
