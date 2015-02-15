CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0 FATAL_ERROR)

# Nom du projet
PROJECT(TrieDocs
  VERSION 0.0.1.0
)

SET( BUILD_SHARED_LIBS   OFF CACHE BOOL "build shared/static libs" )
SET( BUILD_X64           ON  CACHE BOOL "build 64-bit"             )

IF( NOT CMAKE_BUILD_TYPE )
    SET( CMAKE_BUILD_TYPE Release )
ENDIF( NOT CMAKE_BUILD_TYPE )

# -Wall                    Message d’avertissements partout
# -Wextra                  D’avantage de messages d’avertissements
# -fno-strict-aliasing     *
SET( DEFAUT_COMPILE_FLAGS "-Wall -Wextra" )
IF(NOT APPLE)
    # -D_LARGEFILE64_SOURCE=1  Support des fichiers de plus de 2Go
    # -D_FILE_OFFSET_BITS=64   Support des fichiers de plus de 2Go
    SET( DEFAUT_COMPILE_FLAGS "${DEFAUT_COMPILE_FLAGS} -D_LARGEFILE64_SOURCE=1 -D_FILE_OFFSET_BITS=64" )
ENDIF(NOT APPLE)

IF( NOT BUILD_X64 )
    SET( DEFAUT_COMPILE_FLAGS "${DEFAUT_COMPILE_FLAGS} -m32" )
ENDIF()

MESSAGE( "* This is the options recommended to compile: \"${DEFAUT_COMPILE_FLAGS}\"" )

#ADD_SUBDIRECTORY(3party)
ADD_SUBDIRECTORY(libs)
ADD_SUBDIRECTORY(src)
