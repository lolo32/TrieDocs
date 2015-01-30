#ifndef DLGABOUT_H
#define DLGABOUT_H

#include <QDialog>

#include "traduction.h"

class QLabel;
class QPushButton;

namespace Ui {
    class DlgAbout;
}

class DlgAbout : public QDialog, WidgetTraduit
{
    Q_OBJECT

public:
    explicit DlgAbout(QWidget *parent = 0);
    ~DlgAbout();
    void retranslateUi();

protected:
    /** this event is called, when a new translator is loaded or the system language is changed
     */
    void changeEvent(QEvent*);

    QPushButton *btnFermer;
    QLabel      *lblTexte;
};

#endif // DLGABOUT_H
