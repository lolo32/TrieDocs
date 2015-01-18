#include "dlgclient.h"
#include "ui_dlgclient.h"

DlgClient::DlgClient(QString qszServeur, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgClient),
    p_qszServeur(qszServeur)
{
    ui->setupUi(this);
}

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
}

/**
 * @brief Fonction appelée lorsque l’utilisateur annule la demande d’authentification
 */
void DlgClient::on_buttonBox_rejected()
{

}
