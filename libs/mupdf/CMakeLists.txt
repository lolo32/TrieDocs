SET(ENV{mupdf_ROOT} "${PROJECT_SOURCE_DIR}/3party/mupdf-git" )

FILE(GLOB mupdf_cbz_HEADERS  "$ENV{mupdf_ROOT}/source/cbz/*.h")
FILE(GLOB mupdf_cbz_SOURCES  "$ENV{mupdf_ROOT}/source/cbz/*.c")

FILE(GLOB mupdf_fitz_SOURCES "$ENV{mupdf_ROOT}/source/fitz/*.c")
FILE(GLOB mupdf_fitz_HEADERS "$ENV{mupdf_ROOT}/source/fitz/*.h")
IF(NOT WIN32)
    # Li fichier n’est utilisé que sous Windows
    LIST(REMOVE_ITEM mupdf_fitz_SOURCES "$ENV{mupdf_ROOT}/source/fitz/time.c")
ENDIF(NOT WIN32)

FILE(GLOB mupdf_img_HEADERS  "$ENV{mupdf_ROOT}/source/img/*.h")
FILE(GLOB mupdf_img_SOURCES  "$ENV{mupdf_ROOT}/source/img/*.c")

FILE(GLOB mupdf_pdf_SOURCES  "$ENV{mupdf_ROOT}/source/pdf/*.c" "$ENV{mupdf_ROOT}/source/pdf/js/pdf-js-none.c")
FILE(GLOB mupdf_pdf_HEADERS  "$ENV{mupdf_ROOT}/source/pdf/*.h")

FILE(GLOB mupdf_tiff_HEADERS  "$ENV{mupdf_ROOT}/source/tiff/*.h")
FILE(GLOB mupdf_tiff_SOURCES  "$ENV{mupdf_ROOT}/source/tiff/*.c")

FILE(GLOB mupdf_xps_HEADERS  "$ENV{mupdf_ROOT}/source/xps/*.h")
FILE(GLOB mupdf_xps_SOURCES  "$ENV{mupdf_ROOT}/source/xps/*.c")

SET(      mupdf_gen_HEADERS
    "${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_gb.h"
    "${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_cns.h"
    "${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_japan.h"
    "${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_korea.h"
    "${CMAKE_CURRENT_BINARY_DIR}/gen_font_base14.h"
    "${CMAKE_CURRENT_BINARY_DIR}/gen_font_cjk.h"
    "${CMAKE_CURRENT_BINARY_DIR}/gen_font_cjk_full.h"
)

ADD_SUBDIRECTORY(freetype)
ADD_SUBDIRECTORY(jbig2dec)
ADD_SUBDIRECTORY(jpeg)
ADD_SUBDIRECTORY(openjpeg)

##############
# CMapDump
ADD_EXECUTABLE( cmapdump "$ENV{mupdf_ROOT}/scripts/cmapdump.c" )
FILE(GLOB CMAP_CNS_SRC   "$ENV{mupdf_ROOT}/resources/cmaps/cns/*" )
FILE(GLOB CMAP_GB_SRC    "$ENV{mupdf_ROOT}/resources/cmaps/gb/*" )
FILE(GLOB CMAP_JAPAN_SRC "$ENV{mupdf_ROOT}/resources/cmaps/japan/*" )
FILE(GLOB CMAP_KOREA_SRC "$ENV{mupdf_ROOT}/resources/cmaps/korea/*" )

ADD_CUSTOM_COMMAND(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_gb.h"
    COMMAND cmapdump "${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_gb.h" ${CMAP_GB_SRC}
    VERBATIM
)
ADD_CUSTOM_COMMAND(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_cns.h"
    COMMAND cmapdump "${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_cns.h" ${CMAP_CNS_SRC}
    VERBATIM
)
ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_japan.h
    COMMAND cmapdump "${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_japan.h" ${CMAP_JAPAN_SRC}
    VERBATIM
)
ADD_CUSTOM_COMMAND(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_korea.h"
    COMMAND cmapdump "${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_korea.h" ${CMAP_KOREA_SRC}
    VERBATIM
)

##############
# FontDump
ADD_EXECUTABLE( fontdump    "$ENV{mupdf_ROOT}/scripts/fontdump.c" )
FILE(GLOB FONT_BASE14_SRC   "$ENV{mupdf_ROOT}/resources/fonts/urw/*.cff")
SET(      FONT_CJK_SRC      "$ENV{mupdf_ROOT}/resources/fonts/droid/DroidSansFallback.ttc")
SET(      FONT_CJK_FULL_SRC "$ENV{mupdf_ROOT}/resources/fonts/droid/DroidSansFallbackFull.ttc")

ADD_CUSTOM_COMMAND(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/gen_font_base14.h"
    COMMAND fontdump "${CMAKE_CURRENT_BINARY_DIR}/gen_font_base14.h" ${FONT_BASE14_SRC}
    VERBATIM
)
ADD_CUSTOM_COMMAND(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/gen_font_cjk.h"
    COMMAND fontdump "${CMAKE_CURRENT_BINARY_DIR}/gen_font_cjk.h" ${FONT_CJK_SRC}
    VERBATIM
)
ADD_CUSTOM_COMMAND(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/gen_font_cjk_full.h"
    COMMAND fontdump "${CMAKE_CURRENT_BINARY_DIR}/gen_font_cjk_full.h" ${FONT_CJK_FULL_SRC}
    VERBATIM
)

SET( CMAKE_INCLUDE_CURRENT_DIR ON )
INCLUDE_DIRECTORIES( "${PROJECT_SOURCE_DIR}/3party/mupdf-git/include" )
# JPEG
INCLUDE_DIRECTORIES( "$ENV{mupdf_ROOT}/scripts/jpeg"                    )
INCLUDE_DIRECTORIES( "$ENV{mupdf_ROOT}/thirdparty/jpeg"                 )
# JBIG2
INCLUDE_DIRECTORIES( "$ENV{mupdf_ROOT}/thirdparty/jbig2dec"             )
# FreeType2
INCLUDE_DIRECTORIES( "$ENV{mupdf_ROOT}/thirdparty/freetype/include"     )
# OpenJPEG
INCLUDE_DIRECTORIES( "$ENV{mupdf_ROOT}/thirdparty/openjpeg/libopenjpeg" )
# Zlib via miniz
INCLUDE_DIRECTORIES( "$ENV{miniz_ROOT_libs}"                            )
INCLUDE_DIRECTORIES( "$ENV{miniz_ROOT}"                                 )

ADD_LIBRARY( mupdf STATIC
    ${mupdf_cbz_SOURCES}
    ${mupdf_cbz_HEADERS}

    ${mupdf_fitz_SOURCES}
    ${mupdf_fitz_HEADERS}

    ${mupdf_img_SOURCES}
    ${mupdf_img_HEADERS}

    ${mupdf_pdf_SOURCES}
    ${mupdf_pdf_HEADERS}

    ${mupdf_tiff_SOURCES}
    ${mupdf_tiff_HEADERS}

    ${mupdf_xps_SOURCES}
    ${mupdf_xps_HEADERS}

    ${mupdf_gen_HEADERS}
)
SET_TARGET_PROPERTIES(mupdf
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
)
# Indique que l’utilisation de mupdf requiert d’autres librairies
TARGET_LINK_LIBRARIES(mupdf
    freetype jbig2dec jpeg openjpeg miniz
)

#################################
# Programme test
ADD_EXECUTABLE(example_mupdf
    EXCLUDE_FROM_ALL
    "$ENV{mupdf_ROOT}/docs/example.c"
)
TARGET_LINK_LIBRARIES( example_mupdf
    mupdf
)
SET_TARGET_PROPERTIES(example_mupdf
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
)
