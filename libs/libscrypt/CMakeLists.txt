SET( myscrypt_ROOT ${PROJECT_SOURCE_DIR}/3party/libscrypt-git )

SET( myscrypt_SOURCES
    ${myscrypt_ROOT}/crypto-mcf.c
    ${myscrypt_ROOT}/crypto_scrypt-check.c
    ${myscrypt_ROOT}/crypto_scrypt-hash.c
    ${myscrypt_ROOT}/crypto_scrypt-nosse.c
    ${myscrypt_ROOT}/crypto-scrypt-saltgen.c
    ${myscrypt_ROOT}/slowequals.c
)
SET( myscrypt_HEADERS
    ${myscrypt_ROOT}/libscrypt.h
    ${myscrypt_ROOT}/slowequals.h
    ${myscrypt_ROOT}/sysendian.h
)
ADD_DEFINITIONS( -DWITH_POLARSSL )
ADD_LIBRARY( myscrypt STATIC ${myscrypt_SOURCES} ${myscrypt_HEADERS} )

INCLUDE_DIRECTORIES( ${myscrypt_ROOT} )
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3party/polarssl-git/include )

ADD_EXECUTABLE( asiantest
    EXCLUDE_FROM_ALL
    ${myscrypt_ROOT}/main.c
    ${myscrypt_ROOT}/crypto_scrypt-hexconvert.c
    ${myscrypt_ROOT}/crypto_scrypt-hexconvert.h
)
TARGET_LINK_LIBRARIES( asiantest
    myscrypt polarssl
)
