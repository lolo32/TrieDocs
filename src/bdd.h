#ifndef BDD_H
#define BDD_H

#include "sqlite/sqlite3.h"
#include <string>

class QString;

extern class Bdd bdd;

class Bdd
{
public:
   Bdd() :
      _szBdNomFichier("donnees.db"),
      _iBdProgramVersion(1),
      _db(0)
   {  }
   ~Bdd();

   bool OuvreBdd();
   bool FermeBdd();
   bool ExecuteSQL(const char* sql);
   bool Compresser();
   QString LastError();

protected:

   void SetLastError(std::string msg);
   void SetLastError(int sqlite3_interr);

   //! Mise à jour de la base de données
   int Maj(int);
   //! Création de la base de données
   int Cree();

   const std::string   _szBdNomFichier;
   const unsigned int  _iBdProgramVersion;
   std::string         _szLastError;

   sqlite3 *   _db;
};

#endif // BDD_H
