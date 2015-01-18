SET(mysqlite3_SOURCES libmysqlite3.h libmysqlite3.c)

INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3party/sqlite-3.8.6 )

ADD_LIBRARY( mysqlite3 STATIC ${mysqlite3_SOURCES} )
