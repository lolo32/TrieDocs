#ifdef __cplusplus
extern "C" {
#endif

// Active le moteur FTS4
#define SQLITE_ENABLE_FTS4
// Ajout du support des indexs R*Tree
//#define SQLITE_ENABLE_RTREE
// L'autovavuum est désactivé. Des vacuums seront exécutés de temps en temps
#define SQLITE_DEFAULT_AUTOVACUUM 0
// Les clés étrangères sont activées par défaut
#define SQLITE_DEFAULT_FOREIGN_KEYS 1
// L'accès concurent ne pause aucun problème
#define SQLITE_THREADSAFE 1
// Les fichiers temporaires sont en mémoire, mais peut être modifié par "PRAGMA temp_store"
#define SQLITE_TEMP_STORE 2
// Active la planification des requêtes la plus avancé
#define SQLITE_ENABLE_STAT4


// On ajoute le fichier source
#include "sqlite/sqlite3.c"

#ifdef __cplusplus
}
#endif
