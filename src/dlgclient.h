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
    void on_buttonBox_rejected();

private:
    Ui::DlgClient *ui;
    QString p_qszServeur;   /**< Adresse (IP ou DNS) du serveur distant */
};

#endif // DLGCLIENT_H
