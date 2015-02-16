SET( ENV{sqlite3_ROOT} ${PROJECT_SOURCE_DIR}/3party/sqlite-3.8.8.2 )

SET( sqlite3_SOURCES
    $ENV{sqlite3_ROOT}/sqlite/sqlite3.h
    $ENV{sqlite3_ROOT}/sqlite/sqlite3.c
)

INCLUDE_DIRECTORIES( $ENV{sqlite3_ROOT} )

# Active le moteur FTS4
ADD_DEFINITIONS( -DSQLITE_ENABLE_FTS4 )
# Ajout du support des indexs R*Tree
#ADD_DEFINITIONS( -DSQLITE_ENABLE_RTREE )
# L'autovavuum est désactivé. Des vacuums seront exécutés de temps en temps
ADD_DEFINITIONS( -DSQLITE_DEFAULT_AUTOVACUUM=0 )
# Les clés étrangères sont activées par défaut
ADD_DEFINITIONS( -DSQLITE_DEFAULT_FOREIGN_KEYS=1 )
# L'accès concurent ne pause aucun problème
ADD_DEFINITIONS( -DSQLITE_THREADSAFE=1 )
# Les fichiers temporaires sont en mémoire, mais peut être modifié par "PRAGMA temp_store"
ADD_DEFINITIONS( -DSQLITE_TEMP_STORE=2 )
# Active la planification des requêtes la plus avancé
ADD_DEFINITIONS( -DSQLITE_ENABLE_STAT4 )

ADD_LIBRARY( sqlite3 STATIC ${sqlite3_SOURCES} )
SET_TARGET_PROPERTIES(sqlite3
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
)

