
# Find includes in corresponding build directories
SET( CMAKE_INCLUDE_CURRENT_DIR ON )
# Instruct CMake to run moc automatically when needed.
SET( CMAKE_AUTOMOC ON )
# Support automatique des interfaces <fichier>.ui
SET( CMAKE_AUTOUIC ON )
# Compilation auto des ressources .qrc
SET( CMAKE_AUTORCC ON )

# Find the Qt5Core library
FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Widgets REQUIRED)

GET_TARGET_PROPERTY(QtCore_location      Qt5::Core      LOCATION)
GET_TARGET_PROPERTY(QtWidgets_location   Qt5::Widgets   LOCATION)

# Fichiers sources par catégorie
FILE(GLOB TrieDocs_SOURCES   *.cpp )
FILE(GLOB TrieDocs_HEADERS   *.h   )
FILE(GLOB TrieDocs_RESOURCES *.qrc )
FILE(GLOB TrieDocs_FENETRES  *.ui  )
FILE(GLOB TrieDocs_TRADS     "${CMAKE_CURRENT_SOURCE_DIR}/i18n/*.qm}" )
SET(TrieDocs_commun_cpp      "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/TrieDocs.dir/commun.cpp" )

# Répertoire des librairies
INCLUDE_DIRECTORIES( $ENV{sqlite3_root} )
INCLUDE_DIRECTORIES( $ENV{miniz_root}   )

# Librairies propres à la plateforme, le cas échéant
SET(LIBS_PLATFORM)

SET( APPS "\${CMAKE_INSTALL_PREFIX}/bin/TrieDocs")
IF( APPLE )
    INCLUDE(cmake/MacOS.cmake)
ENDIF( APPLE )
IF( WIN32 )
    INCLUDE(cmake/Windows.cmake)
ENDIF( WIN32 )

# Génération du fichier commun.cpp, contenant divers objets globaux
INCLUDE(cmake/GetGitRevisionDescription.cmake)
GET_GIT_HEAD_REVISION(GIT_REFSPEC GIT_SHA1)
CONFIGURE_FILE("commun.cpp.in" ${TrieDocs_commun_cpp} @ONLY)
LIST(APPEND TrieDocs_SOURCES ${TrieDocs_commun_cpp})

# Executable
ADD_EXECUTABLE( TrieDocs WIN32 MACOSX_BUNDLE ${TrieDocs_SOURCES} ${TrieDocs_HEADERS} ${TrieDocs_RESOURCES} ${TrieDocs_ICONE} ${TrieDocs_FENETRES} )
TARGET_LINK_LIBRARIES(TrieDocs
    Qt5::Core
    Qt5::Widgets
    miniz sqlite3
#    polarssl lzhamdecomp lzhamcomp scrypt
#    mupdf freetype jbig2dec jpeg openjpeg
  ${LIBS_PLATFORM}
)
SET_TARGET_PROPERTIES(TrieDocs
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
)

# Dépendance pour demander à CMake de générer les traductions avant de lancer automoc
ADD_DEPENDENCIES (TrieDocs i18n_target)

# Options d’installation
INSTALL( TARGETS TrieDocs
    BUNDLE  DESTINATION .   COMPONENT Runtime
    RUNTIME DESTINATION bin COMPONENT Runtime
)
# Copie les dépendances libqt* dans les bons dossiers
INSTALL(CODE "
    file(GLOB_RECURSE QT_PLUGINS
        \"\${CMAKE_INSTALL_PREFIX}/${plugin_dest_dir}/plugins/*${CMAKE_SHARED_LIBRARY_SUFFIX}\")
    set(PLUGINS_DIRS \"\")          # Répertoire devant contenir les plugins ci-dessus
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\${QT_PLUGINS}\" \"${PLUGINS_DIRS}\")
    " COMPONENT Runtime
)

INCLUDE(cmake/CPack.cmake)

# Règles pour forcer à supprimer les fichiers générés durant la compilation (moc, rcc, etc.)
FILE (GLOB FILES_moc_clean "${CMAKE_CURRENT_BINARY_DIR}/moc_*.cpp" )
FILE (GLOB FILES_ui_clean  "${CMAKE_CURRENT_BINARY_DIR}/ui_*.h" )
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${FILES_moc_clean};${FILES_ui_clean}" )

# Génération des traductions
INCLUDE( cmake/i18n.cmake )
