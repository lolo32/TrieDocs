#ifndef TRADUCTION_H
#define TRADUCTION_H

#include <QString>
#include <QList>
#include <QComboBox>
#include <QMenu>
#include <QTranslator>

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
    bool set(int index);
    bool set(QString iso);

protected slots:
    void slotLangueChangee(QAction *action);

protected:

    void initialise();
    static bool trieLangues(const struct langue&, const struct langue&);
    QString               p_qszLangActuelle;
    QList<struct langue>  p_Langues;
    bool                  p_bCharge;
    QTranslator           p_traducteur;
};

extern Traduction traduction;

#endif // TRADUCTION_H
