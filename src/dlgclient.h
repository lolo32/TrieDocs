#ifndef DLGCLIENT_H
#define DLGCLIENT_H

#include <QDialog>

#include "traduction.h"

class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;

class DlgClient : public QDialog, WidgetTraduit
{
   Q_OBJECT

public:
   explicit DlgClient(QString qszServeur, QWidget *parent = 0);
   ~DlgClient();

void retranslateUi();

private slots:
   void on_btnBox_accepted();

protected:
   /** this event is called, when a new translator is loaded or the system language is changed
   */
   void changeEvent(QEvent*);

void setStatutTexte();

private:
   QString        p_qszServeur;  //!< Adresse (IP ou DNS) du serveur distant
   bool           p_initialise;

   // Contrôles pour l’UI
   QLabel           *lblStatut;  //!< Messages d’informations en haut de la fenêtre
   QString           strStatut;  //!< Texte devant apparaitre dans le statut en haut de la fenêtre
   QLineEdit        *txtLogin;   //!< Champ de saisie du nom d’utilisateur
   QLineEdit        *txtPassword;//!< Champ de saisie du mot de passe
   QLabel           *lblLangue;  //!< Description de la liste déroulante
   QComboBox        *cbxLangues; //!< Liste déroulante des langues
   QPushButton      *btnOk;      //!< Boutton OK en bas de la fenêtre
   QPushButton      *btnAnnuler; //!< Boutton Annuler en bas de la fenêtre
};

#endif // DLGCLIENT_H
