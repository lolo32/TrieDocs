#ifndef DLGCLIENT_H
#define DLGCLIENT_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QComboBox;
class QDialogButtonBox;

namespace Ui {
    class DlgClient;
}

class DlgClient : public QDialog
{
    Q_OBJECT

public:
    explicit DlgClient(QString qszServeur, QWidget *parent = 0);
    ~DlgClient();

private slots:
    void on_btnBox_accepted();

protected:
    /** this event is called, when a new translator is loaded or the system language is changed
     */
    void changeEvent(QEvent*);

    void retranslateUi();
    void setStatutTexte();

private:
    Ui::DlgClient *ui;
    QString        p_qszServeur;   /**< Adresse (IP ou DNS) du serveur distant */
    bool           p_initialise;

    // Contrôles pour l’UI
    QLabel           *lblStatut;  //!< Messages d’informations en haut de la fenêtre
    QString           strStatut;  //!< Texte devant apparaitre dans le statut en haut de la fenêtre
    QLineEdit        *txtLogin;   //!< Champ de saisie du nom d’utilisateur
    QLineEdit        *txtPassword;//!< Champ de saisie du mot de passe
    QLabel           *lblLangue;  //!< Description de la liste déroulante
    QComboBox        *cbxLangues; //!< Liste déroulante des langues
    QDialogButtonBox *btnBox;     //!< Bouttons en bas de la fenêtre
};

#endif // DLGCLIENT_H
