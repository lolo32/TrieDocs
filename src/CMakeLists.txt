# Version
SET( VERSION_MAJEUR 0 )
SET( VERSION_MINEUR 0 )
SET( VERSION_REVISION 1 )

# Find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)
# Support automatique des interfaces <fichier>.ui
SET(CMAKE_AUTOUIC ON)
# Compilation auto des ressources .qrc
SET(CMAKE_AUTORCC ON)

# Find the Qt5Core library
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Network REQUIRED)

GET_TARGET_PROPERTY(QtCore_location      Qt5::Core      LOCATION)
GET_TARGET_PROPERTY(QtWidgets_location   Qt5::Widgets   LOCATION)

# Fichiers sources par catégorie
FILE(GLOB TrieDocs_SOURCES   *.cpp )
FILE(GLOB TrieDocs_HEADERS   *.h   )
FILE(GLOB TrieDocs_RESOURCES *.qrc )

# Répertoire des librairies
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/libs/sqlite3 )
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/libs/miniz )

SET( APPS "\${CMAKE_INSTALL_PREFIX}/bin/TrieDocs")
IF( APPLE )
  INCLUDE(cmake/MacOS.txt)
ENDIF( APPLE )
IF( WIN32 )
  SET( TrieDocs_ICONE icone.rc )
  SET( APPS "\${CMAKE_INSTALL_PREFIX}/bin/TrieDocs.exe" )
  SET( LIBS_PLATFORM ws2_32 )
ENDIF( WIN32 )

# Executable
ADD_EXECUTABLE( TrieDocs WIN32 MACOSX_BUNDLE ${TrieDocs_SOURCES} ${TrieDocs_HEADERS} ${TrieDocs_RESOURCES} ${TrieDocs_ICONE} )
TARGET_LINK_LIBRARIES(TrieDocs
  Qt5::Core
  Qt5::Widgets
  myminiz mysqlite3
  ${LIBS_PLATFORM}
)

# Options d’installation
INSTALL( TARGETS TrieDocs
  BUNDLE DESTINATION . COMPONENT Runtime
  RUNTIME DESTINATION bin COMPONENT Runtime
)
IF( APPLE)
  INSTALL(CODE "
    file(GLOB_RECURSE QTPLUGINS
      \"\${CMAKE_INSTALL_PREFIX}/${plugin_dest_dir}/plugins/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\${QTPLUGINS}\" \"${DIRS}\")
    " COMPONENT Runtime
  )
ENDIF( APPLE )

INCLUDE(cmake/CPack.txt)
INCLUDE(cmake/Traductions.txt)
