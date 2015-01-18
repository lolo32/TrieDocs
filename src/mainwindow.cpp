#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnRechercher_clicked()
{
    // Clic sur le bouton rechercher
}

void MainWindow::on_action_Quitter_triggered()
{
    QApplication::quit();
}
