#include "commun.h"
#include "docautre.h"

#include <QFile>

DocAutre::DocAutre() :
   DocGeneral()
{

}

DocAutre::~DocAutre()
{

}

QList<struct DocGeneral::contenuPage> DocAutre::getContenu(const QString &nomFichier)
{
   QFile qFichier(nomFichier);

   QString entete = QString::fromLatin1( qFichier.read(4) );

   struct contenuPage ret;

   ret.numero = -1;

   // Vérifie si c’est un fichier UTF-8, avec le BOM au début
   if( entete[0]==0xEF && entete[1]==0xBB && entete[2]==0xBF ) {
      // contenu utf-8
      ret.contenu = QString::fromUtf8( qFichier.readAll() );
   } else if( (entete[0]==0xFE && entete[1]==0xFF)       // Contenu UTF-16, big endian
            || (entete[0]==0xFF && entete[1]==0xFE) ) {// Contenu UTF-16, little endian
      ret.contenu = QString::fromUtf16(
            reinterpret_cast<const ushort*>(qFichier.readAll().data())
      );
   }

   QList<struct contenuPage> contenu;
   contenu << ret;

   return contenu;
}
