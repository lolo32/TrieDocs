# -----------------------------------------------------
# Paramèttres pour CPack

# Définition de la version des archives
SET( CPACK_PACKAGE_VERSION_MAJOR ${TrieDocs_VERSION_MAJOR} )
SET( CPACK_PACKAGE_VERSION_MINOR ${TrieDocs_VERSION_MINOR} )
SET( CPACK_PACKAGE_VERSION_PATCH ${TrieDocs_VERSION_PATCH} )
# On stripe les binaires
SET( CPACK_STRIP_FILES TRUE )

IF( APPLE )
  SET( CPACK_BINARY_DRAGNDROP TRUE  CACHE BOOL "Enable to build OSX Drag And Drop package" )
  SET( CPACK_BINARY_BUNDLE    FALSE CACHE BOOL "Enable to build OSX bundles" )
  SET( CPACK_BINARY_STGZ      FALSE CACHE BOOL "Enable to build STGZ packages" )
  SET( CPACK_BINARY_TGZ       FALSE CACHE BOOL "Enable to build TGZ packages" )

# Options pour Bundle
  #SET( CPACK_BUNDLE_NAME  "${PROJECT_NAME}—${VERSION_MAJEUR}.${VERSION_MINEUR}.${VERSION_REVISION}" )
  #SET( CPACK_BUNDLE_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist" )
  #SET( CPACK_BUNDLE_ICON  "${CMAKE_CURRENT_SOURCE_DIR}/icone.icns" )

# Options pour Drag&Drop
  #SET( CPACK_DMG_BACKGROUND_IMAGE  )
  SET( CPACK_DMG_DS_STORE      "${CMAKE_CURRENT_SOURCE_DIR}/DS_Store" )
  SET( CPACK_DMG_FORMAT        UDBZ ) # Archive bzipée
  SET( CPACK_DMG_VOLUME_NAME   "${PROJECT_NAME}—${TrieDocs_VERSION_MAJOR}.${TrieDocs_VERSION_MINOR}.${TrieDocs_VERSION_PATCH}" )
ENDIF( APPLE )

INCLUDE( CPack )
