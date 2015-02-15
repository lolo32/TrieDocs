#ifndef DOCPDF_H
#define DOCPDF_H

#include "docgeneral.h"

class DocPdf : public DocGeneral
{
public:
   DocPdf();
   ~DocPdf();

   // support des extensions PDF, XPS et CBZ
   QStringList getExtentions() {
      return QStringList()
                     << QStringLiteral("pdf")
                     << QStringLiteral("xps")
                     << QStringLiteral("cbz");
   }
   // Contenu des documents
   QList<struct contenuPage> getContenu(const QString&);
};

#endif // DOCPDF_H
