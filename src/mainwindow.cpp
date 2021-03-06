#include "commun.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "traduction.h"

/**
 * @brief constructeur
 * @param parent[in]
 */
MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   g_traduction.rempli(ui->menu_Langue);
}

/**
 * @brief Destructeur
 */
MainWindow::~MainWindow()
{
   delete ui;
}

/**
 * @brief Déclenché lorsque on clique sur le bouton rechercher
 */
void MainWindow::on_btnRechercher_clicked()
{
   // Clic sur le bouton rechercher
}

/**
 * @brief Déclenché lorsque l'on clique sur Fichier->Quitter
 */
void MainWindow::on_action_Quitter_triggered()
{
   QApplication::quit();
}
