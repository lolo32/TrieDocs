#include "bdd.h"
#include "dlgclient.h"
#include "mainwindow.h"

#include <QApplication>
#include <QString>
#include <QFile>
#include <QFileInfo>

/**
 * @brief Fonction d'enrée de l'application
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    {
        DlgClient dlgClient("hephaistos");
        int ret = dlgClient.exec();

        if( ret != 1) {
            // On quitte
            return ret;
        }
    }
    // On regarde si on est dans une situation Client/Server ou non
    //
    // Pour se faire, on ouvre le fichier exécutable et on lit les 4 derniers octets
    // pour vérifier la présence du code magique indiquant un exe client
    QString strAppliPath = QCoreApplication::applicationFilePath();

    QFile qfAppli(strAppliPath);
    bool ret = qfAppli.open(QIODevice::ReadOnly);
    if( ret ) {
        // Ouvert avec succès en lecture, on lit maintenant les 4 derniers octets
        QFileInfo qfi(qfAppli);
        qfAppli.seek( qfi.size()-4 );
        char signature[4];
        qfAppli.read(signature, 4);
        if( signature[0] == '\25' && signature[1] == '\50' && signature[2] == '\100' && signature[3] == '\200' ) {
            // Client/Serveur, on récupère les infos de connexion

            // On lit les sizeof(int) octets suivant, contenant la longueur de la chaîne de caractères su serveur
            // (adresse IP, nom DNS)
            int iAdresseServeurLong = 0;
            qfAppli.seek( qfi.size() - 4 - sizeof(int) );
            qfAppli.read( (char*) &iAdresseServeurLong, sizeof(int) );

            // On a maintenant la longueur de l’adresse du serveur, on lit l’adresse
            qfAppli.seek( qfi.size() - 4 - sizeof(int) - iAdresseServeurLong );
            QString qszServeur = qfAppli.read(iAdresseServeurLong);

            // On a les infos, on affiche la fenêtre de connexion et d’identification
            DlgClient dlgClient(qszServeur);
            int ret = dlgClient.exec();

            if( ret != 1) {
                // On quitte
                return ret;
            }

            // TODO: à implémenter

        } else {
            // Utilisation locale

            // On initialise SQLite
            bdd.OuvreBdd();
        }
        qfAppli.close();
    }

    MainWindow w;
    w.show();

    return a.exec();
}
