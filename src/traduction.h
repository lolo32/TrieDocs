#ifndef TRADUCTION_H
#define TRADUCTION_H

#include <QString>
#include <QList>
#include <QTranslator>

class QAction;
class QComboBox;
class QEvent;
class QMenu;
class QWidget;

#define INCLUT_QT_TRADS 0

class WidgetTraduit
{
public:
    virtual void retranslateUi() = 0;
};

class Traduction : QObject
{
    Q_OBJECT

public:
    Traduction();
    ~Traduction();

    struct langue {
        QString nom;
        QString iso;
    };

    void rempli(QMenu *menu);
    void rempli(QComboBox *combo);
    bool set(unsigned int index);
    bool set(QString iso);

    void retranslateUi(QEvent *, WidgetTraduit *);

protected slots:
    void slotLangueChangee(QAction *action);
    void slotLangueChangee(int index);

protected:

    void initialise();
    static bool trieLangues(const struct langue&, const struct langue&);
    QString nomLangue(const QString&);

    QString               p_qszLangActuelle;
    QList<struct langue>  p_Langues;
    bool                  p_bCharge;
    QList<QTranslator*>   p_traducteurs;
};

extern Traduction traduction;

#endif // TRADUCTION_H
