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
#FIND_PACKAGE(Qt5LinguistTools REQUIRED)

GET_TARGET_PROPERTY(QtCore_location Qt5::Core LOCATION)
GET_TARGET_PROPERTY(QtWidgets_location Qt5::Widgets LOCATION)

# Fichiers sources par catégorie
SET(TrieDocs_SOURCES   bdd.cpp main.cpp mainwindow.cpp dlgclient.cpp )
SET(TrieDocs_HEADERS   bdd.h            mainwindow.h   dlgclient.h   )
SET(TrieDocs_RESOURCES resources.qrc)

# Répertoire des librairies
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/libs/sqlite3 )
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/libs/miniz )

SET( APPS "\${CMAKE_INSTALL_PREFIX}/bin/TrieDocs")
IF( APPLE )
  # Options pour MacOSx
  SET( MACOSX_BUNDLE_INFO_STRING "TrieDocs, ${VERSION_MAJEUR}.${VERSION_MINEUR}.${VERSION_REVISION} 2015 — Laurent B." )

#  SET( MACOSX_BUNDLE_ICON_FILE 
  # set where in the bundle to put the icns file
#  SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_SOURCE_DIR}/QtTest.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

#  SET( MACOSX_BUNDLE_GUI_IDENTIFIER 
  SET( MACOSX_BUNDLE_LONG_VERSION_STRING ${VERSION_MAJEUR}.${VERSION_MINEUR}.${VERSION_REVISION} )
  SET( MACOSX_BUNDLE_BUNDLE_NAME TrieDocs )
  SET( MACOSX_BUNDLE_SHORT_VERSION_STRING ${VERSION_MAJEUR}.${VERSION_MINEUR}.${VERSION_REVISION} )
  SET( MACOSX_BUNDLE_BUNDLE_VERSION ${VERSION_MAJEUR}.${VERSION_MINEUR}.${VERSION_REVISION} )
  SET( MACOSX_BUNDLE_COPYRIGHT "Laurent B. — Tous droits réservés © 2014" )

  SET( APPS "\${CMAKE_INSTALL_PREFIX}/TrieDocs.app" )
ENDIF( APPLE )
IF( WIN32 )
  SET( APPS "\${CMAKE_INSTALL_PREFIX}/bin/TrieDocs.exe" )
  SET( LIBS_PLATFORM ws2_32 )
ENDIF( WIN32 )

# Executable
ADD_EXECUTABLE( TrieDocs WIN32 MACOSX_BUNDLE ${TrieDocs_SOURCES} ${TrieDocs_HEADERS} ${TrieDocs_RESOURCES} )
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

# -----------------------------------------------------
# Paramèttres pour CPack

# Définition de la version des archives
SET( CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJEUR} )
SET( CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINEUR} )
SET( CPACK_PACKAGE_VERSION_PATCH ${VERSION_REVISION} )
# On stripe les binaires
SET( CPACK_STRIP_FILES TRUE )

INCLUDE( CPack )
