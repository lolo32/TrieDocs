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
        QString iso;
        QString nom;
        QString traducteurs;
    };

    void rempli(QMenu *);
    void rempli(QComboBox *);
    bool set(unsigned int);
    bool set(QString);

    QString getTranslatorsName();
    QString getLangName();

    void retranslateUi(QEvent *, WidgetTraduit *);

    int getMoisAnglais(const QString&) const;

protected slots:
    void slotLangueChangee(QAction *action);
    void slotLangueChangee(int index);

protected:

    void initialise();
    static bool trieLangues(const struct langue&, const struct langue&);
    struct langue nomLangue(const QString&, const QString&);

    QString               p_qszLangActuelle;
    QList<struct langue>  p_Langues;
    bool                  p_bCharge;
    QList<QTranslator*>   p_traducteurs;
};

extern Traduction g_traduction;

#endif // TRADUCTION_H
