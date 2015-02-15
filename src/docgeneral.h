#ifndef DOCGENERAL_H
#define DOCGENERAL_H

#include <QList>
#include <QString>
#include <QStringList>

class DocGeneral
{
public:
   DocGeneral();
   ~DocGeneral();

   struct contenuPage {
      QString numero;
      QString contenu;
   };

   /**
    * @brief Doit retourner la liste des extensions prises en charge par le lecteur
    * @return la liste des extensions
    */
   virtual QStringList getExtentions() = 0;

   /**
    * @brief Retourne le contenu du document, trié par page
    * @return contenu lut
    */
   virtual QList<struct contenuPage> getContenu(const QString&) = 0;
};

#endif // DOCGENERAL_H
