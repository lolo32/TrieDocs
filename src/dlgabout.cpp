#include "dlgabout.h"

#include "traduction.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QDate>

DlgAbout::DlgAbout(QWidget *parent) :
    QDialog(parent)
{
    // On génère l'affichage
    // Le texte est ajouté plus loin, par la méthode retranslateUI()
    //       +--------+-----------------------+
    //       |        |                       |
    //       |        |                       |
    //       | lblIcon|  lblTexte             |
    //       |        |                       |
    //       |        |                       |
    //       +--------+-----------------------+
    //       |        btnBox          Close   |
    //       +--------------------------------+

    this->resize(482, 279);

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    QHBoxLayout *horizontalLayout = new QHBoxLayout();

    QLabel *lblIcon = new QLabel(this);
    lblIcon->setMinimumSize(QSize(64, 64));
    lblIcon->setMaximumSize(QSize(64, 64));
    lblIcon->setPixmap(QPixmap( QStringLiteral(":/icones/application.svg") ));
    lblIcon->setScaledContents(true);
    lblIcon->setText(QString());
    horizontalLayout->addWidget(lblIcon);

    lblTexte = new QLabel(this);
    lblTexte->setWordWrap(true);
    horizontalLayout->addWidget(lblTexte);

    verticalLayout->addLayout(horizontalLayout);

    QDialogButtonBox *btnBox = new QDialogButtonBox(this);
    btnBox->setOrientation(Qt::Horizontal);
    btnBox->setStandardButtons(QDialogButtonBox::Close);
    btnFermer = btnBox->button(QDialogButtonBox::Close);
    btnFermer->setDefault(true);

    verticalLayout->addWidget(btnBox);

    retranslateUi();
    QObject::connect(btnBox, SIGNAL(accepted()), SLOT(accept()));
    QObject::connect(btnBox, SIGNAL(rejected()), SLOT(reject()));

    //QMetaObject::connectSlotsByName(this);
}

DlgAbout::~DlgAbout()
{

}

void DlgAbout::retranslateUi()
{
    //: About TrieDocs
    //~ Context Windows title
    this->setWindowTitle( tr("\303\200 propos de TrieDocs") );
    // Convertit la date de compilation en natif
    QString strDateCompilation = QStringLiteral(__DATE__);
    QString      strMois = strDateCompilation.mid(0, 3);
    unsigned int uiMois = 0;
    unsigned int uiJour  = strDateCompilation.mid(4, 2).trimmed().toUInt();
    unsigned int uiAnnee = strDateCompilation.mid(7).toUInt();
    if (strMois == QLatin1String("Jan") )
            uiMois = 1;
    else if(strMois == QLatin1String("Feb") )
            uiMois = 2;
    else if(strMois == QLatin1String("Mar") )
            uiMois = 3;
    else if(strMois == QLatin1String("Apr") )
            uiMois = 4;
    else if(strMois == QLatin1String("May") )
            uiMois = 5;
    else if(strMois == QLatin1String("Jun") )
            uiMois = 6;
    else if(strMois == QLatin1String("Jul") )
            uiMois = 7;
    else if(strMois == QLatin1String("Aug") )
            uiMois = 8;
    else if(strMois == QLatin1String("Sep") )
            uiMois = 9;
    else if(strMois == QLatin1String("Oct") )
            uiMois = 10;
    else if(strMois == QLatin1String("Nov") )
            uiMois = 11;
    else if(strMois == QLatin1String("Dec") )
            uiMois = 12;

    QDate dateCompilation(uiAnnee, uiMois, uiJour);
#ifndef TRIEDOCS_VERSION_STR
#define TRIEDOCS_VERSION_STR "??.??.??"
#endif
    QString texte = QString( QStringLiteral("<p><span style=\"font-weight:600;\">TrieDocs %1</span></p><p>%2</p><p>%3</p><p>Copyright \302\2512015 Laurent B. (Lolo_32). %4</p><p>%5</p>")
                             .arg( QStringLiteral(TRIEDOCS_VERSION_STR) )
                             .arg(
                                 //: Based on Qt "Qt_compiled_version"
                                 tr("Bas\303\251 sur Qt %1").arg( QStringLiteral(QT_VERSION_STR) )
                                 )
                             .arg(
                                 //: Compiled on "Compilation_date".
                                 tr("Compil\303\251 le %1.").arg(dateCompilation.toString(Qt::DefaultLocaleLongDate))
                                 )
                             .arg(
                                 //: All rights reserved.
                                 tr("Tous droits r\303\251serv\303\251s.")
                                 )
                             .arg(
                                 //: The program is provided AS IS without ANY WARRANTY; WITHOUT EVEN THE IMPLIED WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
                                 tr("Le programme est fourni TEL QUEL sans GARANTIE D\342\200\231AUCUNE SORTE, Y COMPRIS DE GARANTIE DE LA CONCEPTION DE QUALIT\303\211 MARCHANDE ET D\342\200\231AD\303\211QUATION \303\200 UN USAGE PARTICULIER.")
                                 )
                             );
    lblTexte->setText(texte);

    //: Close
    //~ Context Text on the button at the bottom
    btnFermer->setText( tr("Fermer") );
} // retranslateUi

/**
 * @brief Gestion des évènements de la fenêtre
 * @param event[in] id de l’évènement
 */
void DlgAbout::changeEvent(QEvent * event)
{
    traduction.retranslateUi(event, this);
    QDialog::changeEvent(event);
}
