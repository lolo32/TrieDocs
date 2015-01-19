#ifndef DLGCLIENT_H
#define DLGCLIENT_H

#include <QDialog>

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
    void on_buttonBox_accepted();
    void on_cbxLangues_currentIndexChanged(int index);

protected:
    /** this event is called, when a new translator is loaded or the system language is changed
     */
    void changeEvent(QEvent*);

private:
    Ui::DlgClient *ui;
    QString        p_qszServeur;   /**< Adresse (IP ou DNS) du serveur distant */
    bool           p_initialise;
};

#endif // DLGCLIENT_H
