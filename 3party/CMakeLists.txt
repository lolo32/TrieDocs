# Désactive les options de PolarSSL non utiles dans ce projet
SET( ENABLE_PROGRAMS          OFF CACHE BOOL "Build PolarSSL programs."  )
SET( ENABLE_TESTING           OFF CACHE BOOL "Build PolarSSL tests."     )
SET( INSTALL_POLARSSL_HEADERS OFF CACHE BOOL "Install PolarSSL headers." )
ADD_SUBDIRECTORY(polarssl-git)

ADD_SUBDIRECTORY(lzham-git)
