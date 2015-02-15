SET( mupdf_root ${PROJECT_SOURCE_DIR}/3party/mupdf-git )
FILE(GLOB mupdf_fitz_SOURCES ${mupdf_root}/source/fitz/*.c)
FILE(GLOB mupdf_fitz_HEADERS ${mupdf_root}/source/fitz/*.h)
FILE(GLOB mupdf_pdf_SOURCES ${mupdf_root}/source/pdf/*.c ${mupdf_root}/source/pdf/js/pdf-js-none.c)
FILE(GLOB mupdf_pdf_HEADERS ${mupdf_root}/source/pdf/*.h)
SET(      mupdf_gen_HEADERS
    ${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_gb.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_cns.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_japan.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_korea.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen_font_base14.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen_font_cjk.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen_font_cjk_full.h
)

ADD_SUBDIRECTORY(freetype)
ADD_SUBDIRECTORY(jbig2dec)
ADD_SUBDIRECTORY(jpeg)
ADD_SUBDIRECTORY(openjpeg)

##############
# CMapDump
ADD_EXECUTABLE( cmapdump ${mupdf_root}/scripts/cmapdump.c )
FILE(GLOB CMAP_CNS_SRC   ${mupdf_root}/resources/cmaps/cns/* )
FILE(GLOB CMAP_GB_SRC    ${mupdf_root}/resources/cmaps/gb/* )
FILE(GLOB CMAP_JAPAN_SRC ${mupdf_root}/resources/cmaps/japan/* )
FILE(GLOB CMAP_KOREA_SRC ${mupdf_root}/resources/cmaps/korea/* )

ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_gb.h
    COMMAND cmapdump ${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_gb.h ${CMAP_GB_SRC}
    VERBATIM
)
ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_cns.h
    COMMAND cmapdump ${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_cns.h ${CMAP_CNS_SRC}
    VERBATIM
)
ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_japan.h
    COMMAND cmapdump ${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_japan.h ${CMAP_JAPAN_SRC}
    VERBATIM
)
ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_korea.h
    COMMAND cmapdump ${CMAKE_CURRENT_BINARY_DIR}/gen_cmap_korea.h ${CMAP_KOREA_SRC}
    VERBATIM
)

##############
# FontDump
ADD_EXECUTABLE( fontdump    ${mupdf_root}/scripts/fontdump.c )
FILE(GLOB FONT_BASE14_SRC   ${mupdf_root}/resources/fonts/urw/*.cff)
SET(      FONT_CJK_SRC      ${mupdf_root}/resources/fonts/droid/DroidSansFallback.ttc)
SET(      FONT_CJK_FULL_SRC ${mupdf_root}/resources/fonts/droid/DroidSansFallbackFull.ttc)

ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gen_font_base14.h
    COMMAND fontdump ${CMAKE_CURRENT_BINARY_DIR}/gen_font_base14.h ${FONT_BASE14_SRC}
    VERBATIM
)
ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gen_font_cjk.h
    COMMAND fontdump ${CMAKE_CURRENT_BINARY_DIR}/gen_font_cjk.h ${FONT_CJK_SRC}
    VERBATIM
)
ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gen_font_cjk_full.h
    COMMAND fontdump ${CMAKE_CURRENT_BINARY_DIR}/gen_font_cjk_full.h ${FONT_CJK_FULL_SRC}
    VERBATIM
)

SET( CMAKE_INCLUDE_CURRENT_DIR ON )
INCLUDE_DIRECTORIES( ${PROJECT_SOURCE_DIR}/3party/mupdf-git/include )
# JPEG
INCLUDE_DIRECTORIES( ${mupdf_root}/scripts/jpeg                    )
INCLUDE_DIRECTORIES( ${mupdf_root}/thirdparty/jpeg                 )
# JBIG2
INCLUDE_DIRECTORIES( ${mupdf_root}/thirdparty/jbig2dec             )
# FreeType2
INCLUDE_DIRECTORIES( ${mupdf_root}/thirdparty/freetype/include     )
# OpenJPEG
INCLUDE_DIRECTORIES( ${mupdf_root}/thirdparty/openjpeg/libopenjpeg )

ADD_LIBRARY( mupdf STATIC
  ${mupdf_fitz_SOURCES}
  ${mupdf_fitz_HEADERS}
  ${mupdf_pdf_SOURCES}
  ${mupdf_pdf_HEADERS}
  ${mupdf_gen_HEADERS}
)
SET_TARGET_PROPERTIES(mupdf
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
)
