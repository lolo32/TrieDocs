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
FIND_PACKAGE(Qt5LinguistTools REQUIRED)

GET_TARGET_PROPERTY(QtCore_location Qt5::Core LOCATION)
GET_TARGET_PROPERTY(QtWidgets_location Qt5::Widgets LOCATION)

# Fichiers sources par catégorie
FILE(GLOB TrieDocs_SOURCES   *.cpp )
FILE(GLOB TrieDocs_HEADERS   *.h   )
FILE(GLOB TrieDocs_RESOURCES *.qrc )

# Répertoire des librairies
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/libs/sqlite3 )
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/libs/miniz )



function(myQT5_ADD_TRANSLATION _qm_files)
    foreach(_current_FILE ${ARGN})
        get_filename_component(_abs_FILE ${_current_FILE} ABSOLUTE)
        get_filename_component(_abs_DIR ${_abs_FILE} DIRECTORY)
        get_filename_component(qm ${_abs_FILE} NAME_WE)
        set(qm "${_abs_DIR}/${qm}.qm")

        add_custom_command(OUTPUT ${qm}
            PRE_BUILD
            COMMAND ${Qt5_LRELEASE_EXECUTABLE}
            ARGS ${_abs_FILE} -qm ${qm} -compress -removeidentical
            DEPENDS ${_abs_FILE} VERBATIM
        )
        list(APPEND ${_qm_files} ${qm})
    endforeach()
    set(${_qm_files} ${${_qm_files}} PARENT_SCOPE)
endfunction()

FILE (GLOB TRANSLATIONS_FILES i18n/*.ts)

OPTION (UPDATE_TRANSLATIONS "Update source translation i18n/*.ts")
IF (UPDATE_TRANSLATIONS)
  QT5_CREATE_TRANSLATION(QM_FILES ${FILES_TO_TRANSLATE} ${TRANSLATIONS_FILES})
ELSE (UPDATE_TRANSLATIONS)
  myQT5_ADD_TRANSLATION(QM_FILES ${TRANSLATIONS_FILES})
ENDIF (UPDATE_TRANSLATIONS)

ADD_CUSTOM_TARGET (i18n_target DEPENDS ${QM_FILES})

#install(FILES ${QM_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/i18n)

# prevent the generated files from being deleted during make clean
#set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM true)



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
