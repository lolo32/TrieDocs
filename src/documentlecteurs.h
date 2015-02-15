#ifndef DOCUMENTLECTEURS_H
#define DOCUMENTLECTEURS_H

#include <QList>
#include <QString>

class DocGeneral;

class DocumentLecteurs
{
public:
   DocumentLecteurs();
   ~DocumentLecteurs();

   //! Lit le fichier passé en paramètre, et stocke le contenu dans donnees
   void lit(const QString&);
   //! Retourne le numéros des pages, contenant le texte
   QList<int> getPagesNumero();
   //! retourne le texte associé à la page
   QString getPageTexte(const QString&);

private:
   struct page {
      QString numero;
      QString contenu;
   };
   QList<struct page> donnees;

   QList<DocGeneral*> documents;
};

#endif // DOCUMENTLECTEURS_H
