#include "commun.h"
#include "documentlecteurs.h"

#include "docgeneral.h" // Classe mère
#include "docautre.h"   // Fallback
#include "docpdf.h"     // PDF

DocumentLecteurs::DocumentLecteurs()
{
   documents
         << new DocPdf()
         << new DocAutre();
}

DocumentLecteurs::~DocumentLecteurs()
{

}

QString DocumentLecteurs::getPageTexte(const QString &page)
{
   QListIterator<struct page> iterator(donnees);
   while(iterator.hasNext()) {
      const struct page &unePage = iterator.next();

      if(unePage.numero == page) {
         // Le numéro de page a été trouvé
         return unePage.contenu;
      }
   }

   // Si on est ici, c'est que le numéro de page n’a pas été trouvé,
   // on retourne une chaîne vide
   return QString();
}
