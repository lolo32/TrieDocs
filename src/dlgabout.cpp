#include "commun.h"
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

   this->resize(500, 100);

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

__attribute__((annotate("oclint:suppress[long method]")))
void DlgAbout::retranslateUi()
{
   //: About TrieDocs
   //~ Context Windows title
   this->setWindowTitle( tr("\303\200 propos de TrieDocs") );
   // Convertit la date de compilation en natif
   // De la forme "Jan  1 2015"
   QString strDateCompilation = QStringLiteral(__DATE__);

   unsigned int uiAnnee = strDateCompilation.mid(7).toUInt();
   unsigned int uiMois = g_traduction.getMoisAnglais(strDateCompilation.mid(0, 3));
   unsigned int uiJour  = strDateCompilation.mid(4, 2).trimmed().toUInt();

   QDate dateCompilation(uiAnnee, uiMois, uiJour);
   QString texte = QString( QStringLiteral(
                                       "<p><span style=\"font-weight:600;\">TrieDocs %1</span></p>"
                                       "<p>%2</p>"
                                       "<p>%3</p>"
                                       "<p>%4</p>"
                                       "<p>Copyright \302\2512015 Laurent B. (Lolo_32). %5</p>"
                                       "<p>%6</p>"
                                       "<p>%7</p>")
                             .arg( QString::fromLatin1(g_TRIEDOCS_VERSION_STR) )
                             .arg(
                                //: Based on Qt %1:"Qt_compiled_version"
                                tr("Bas\303\251 sur Qt %1").arg( QStringLiteral(QT_VERSION_STR) )
                                )
                             .arg(
                                //: Compiled on %1:"Compilation_date".
                                tr("Compil\303\251 le %1.")
                                       .arg(dateCompilation.toString(Qt::DefaultLocaleLongDate))
                                )
                             .arg(
                                //: Revision: %1:"Revision_git"
                                tr("Révision\302\240: %1").arg( QString::fromLatin1(g_GIT_SHA1))
                                )
                             .arg(
                                //: All rights reserved.
                                tr("Tous droits r\303\251serv\303\251s.")
                                )
                             .arg(
                                //: %1:"Language_Name" translation by: %2:"Translator(s) name"
                                QString( tr("Traduction %1 par\302\240: %2") )
                                      .arg( g_traduction.getLangName() )
                                      .arg( g_traduction.getTranslatorsName() )
                                )
                             .arg(
                                //: The program is provided AS IS without ANY WARRANTY; WITHOUT
                                //: EVEN THE IMPLIED WARRANTY OF MERCHANTABILITY OR FITNESS FOR A
                                //: PARTICULAR PURPOSE.
                                tr(
                                    "Le programme est fourni TEL QUEL sans GARANTIE D\342\200\231"
                                    "AUCUNE SORTE, Y COMPRIS DE GARANTIE DE LA CONCEPTION DE "
                                    "QUALIT\303\211 MARCHANDE ET D\342\200\231AD\303\211QUATION "
                                    "\303\200 UN USAGE PARTICULIER."
                                   )
                                )
                          );
   lblTexte->setText(texte);

   //: Close
   //~ Context Text on the button at the bottom
   btnFermer->setText( tr("Fermer") );

   this->adjustSize();

} // retranslateUi

/**
 * @brief Gestion des évènements de la fenêtre
 * @param event[in] id de l’évènement
 */
void DlgAbout::changeEvent(QEvent * event)
{
   g_traduction.retranslateUi(event, this);
   QDialog::changeEvent(event);
}
