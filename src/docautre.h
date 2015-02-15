#ifndef DOCAUTRE_H
#define DOCAUTRE_H

#include "docgeneral.h"

class DocAutre : public DocGeneral
{
public:
   DocAutre();
   ~DocAutre();

   // support des autres extensions
   QStringList getExtentions() {
      return QStringList(QStringLiteral("*"));
   }
   // Contenu des documents
   QList<struct contenuPage> getContenu(const QString&);

};

#endif // DOCAUTRE_H
