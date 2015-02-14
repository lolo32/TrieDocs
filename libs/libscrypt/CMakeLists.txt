SET( scrypt_ROOT ${PROJECT_SOURCE_DIR}/3party/libscrypt-git )

SET( scrypt_SOURCES
    ${scrypt_ROOT}/crypto-mcf.c
    ${scrypt_ROOT}/crypto_scrypt-check.c
    ${scrypt_ROOT}/crypto_scrypt-hash.c
    ${scrypt_ROOT}/crypto_scrypt-nosse.c
    ${scrypt_ROOT}/crypto-scrypt-saltgen.c
    ${scrypt_ROOT}/slowequals.c
)
SET( scrypt_HEADERS
    ${scrypt_ROOT}/libscrypt.h
    ${scrypt_ROOT}/slowequals.h
    ${scrypt_ROOT}/sysendian.h
)
ADD_DEFINITIONS( -DWITH_POLARSSL )
ADD_LIBRARY( scrypt STATIC ${scrypt_SOURCES} ${scrypt_HEADERS} )

INCLUDE_DIRECTORIES( ${scrypt_ROOT} )
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3party/polarssl-git/include )

ADD_EXECUTABLE( check_libscrypt
    EXCLUDE_FROM_ALL
    ${myscrypt_ROOT}/main.c
    ${myscrypt_ROOT}/crypto_scrypt-hexconvert.c
    ${myscrypt_ROOT}/crypto_scrypt-hexconvert.h
)
TARGET_LINK_LIBRARIES( check_libscrypt
    scrypt polarssl
)
