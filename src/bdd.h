#ifndef BDD_H
#define BDD_H

#include "libmysqlite3.h"
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
    bool OuvreBdd();
    bool FermeBdd();
    bool ExecuteSQL(const char* sql);
    bool Compresser();
    QString LastError();

protected:

    void SetLastError(std::string msg);
    void SetLastError(int sqlite3_interr);

    const std::string   _szBdNomFichier;
    const unsigned int  _iBdProgramVersion;
    std::string         _szLastError;

    sqlite3 *   _db;
};

#endif // BDD_H
