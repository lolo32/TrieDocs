# Options pour MacOSx
SET( MACOSX_BUNDLE_INFO_STRING "${PROJECT_NAME}, ${TrieDocs_VERSION_MAJOR}.${TrieDocs_VERSION_MINOR}.${TrieDocs_VERSION_PATCH} — 2015 — Laurent B." )

SET( TrieDocs_ICONE "${CMAKE_CURRENT_SOURCE_DIR}/icone.icns" )

SET( MACOSX_BUNDLE_ICON_FILE icone.icns )
# set where in the bundle to put the icns file
SET_SOURCE_FILES_PROPERTIES( ${TrieDocs_ICONE} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources" )

SET( MACOSX_BUNDLE_GUI_IDENTIFIER       "fr.baysse.${PROJECT_NAME}"                                                       )
SET( MACOSX_BUNDLE_LONG_VERSION_STRING  "${PROJECT_NAME} version ${TrieDocs_VERSION_MAJOR}.${TrieDocs_VERSION_MINOR}.${TrieDocs_VERSION_PATCH}"  )
SET( MACOSX_BUNDLE_BUNDLE_NAME          "${PROJECT_NAME}"                                                                 )
SET( MACOSX_BUNDLE_SHORT_VERSION_STRING "${TrieDocs_VERSION_MAJOR}.${TrieDocs_VERSION_MINOR}.${TrieDocs_VERSION_PATCH}"   )
SET( MACOSX_BUNDLE_BUNDLE_VERSION       "${TrieDocs_VERSION_MAJOR}.${TrieDocs_VERSION_MINOR}.${TrieDocs_VERSION_PATCH}"   )
SET( MACOSX_BUNDLE_COPYRIGHT            "Laurent B. — All rights reserved © 2015"                                         )

SET( APPS "\${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app" )
