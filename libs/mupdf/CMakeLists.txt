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
    ${CMAKE_CURRENT_BINARY_DIR}/gen_font_droid.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen_font_cjk.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen_font_cjk_full.h
)

##############
# JPEG library from IJG
SET( mupdf_jpeg_root ${mupdf_root}/thirdparty/jpeg )
SET(mupdf_jpeg_SOURCES
    ${mupdf_jpeg_root}/jaricom.c
    ${mupdf_jpeg_root}/jcomapi.c
    ${mupdf_jpeg_root}/jdapimin.c
    ${mupdf_jpeg_root}/jdapistd.c
    ${mupdf_jpeg_root}/jdarith.c
    ${mupdf_jpeg_root}/jdatadst.c
    ${mupdf_jpeg_root}/jdatasrc.c
    ${mupdf_jpeg_root}/jdcoefct.c
    ${mupdf_jpeg_root}/jdcolor.c
    ${mupdf_jpeg_root}/jddctmgr.c
    ${mupdf_jpeg_root}/jdhuff.c
    ${mupdf_jpeg_root}/jdinput.c
    ${mupdf_jpeg_root}/jdmainct.c
    ${mupdf_jpeg_root}/jdmarker.c
    ${mupdf_jpeg_root}/jdmaster.c
    ${mupdf_jpeg_root}/jdmerge.c
    ${mupdf_jpeg_root}/jdpostct.c
    ${mupdf_jpeg_root}/jdsample.c
    ${mupdf_jpeg_root}/jdtrans.c
    ${mupdf_jpeg_root}/jerror.c
    ${mupdf_jpeg_root}/jfdctflt.c
    ${mupdf_jpeg_root}/jfdctfst.c
    ${mupdf_jpeg_root}/jfdctint.c
    ${mupdf_jpeg_root}/jidctflt.c
    ${mupdf_jpeg_root}/jidctfst.c
    ${mupdf_jpeg_root}/jidctint.c
    ${mupdf_jpeg_root}/jmemmgr.c
    ${mupdf_jpeg_root}/jquant1.c
    ${mupdf_jpeg_root}/jquant2.c
    ${mupdf_jpeg_root}/jutils.c
)
ADD_LIBRARY( jpeg STATIC ${mupdf_jpeg_SOURCES} )

##############
# JBIG2DEC
SET( mupdf_jbig2_root ${mupdf_root}/thirdparty/jbig2dec )

##############
# FreeType 2
SET( mupdf_ft2_root ${mupdf_root}/thirdparty/freetype/include )

##############
# OpenJPEG
SET( mupdf_openjpeg_root ${mupdf_root}/thirdparty/openjpeg/libopenjpeg )


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

ADD_EXECUTABLE( fontdump    ${mupdf_root}/scripts/fontdump.c )
FILE(GLOB FONT_BASE14_SRC   ${mupdf_root}/resources/fonts/urw/*.cff)
SET(      FONT_DROID_SRC    ${mupdf_root}/resources/fonts/droid/DroidSans.ttf ${mupdf_root}/resources/fonts/droid/DroidSansMono.ttf)
SET(      FONT_CJK_SRC      ${mupdf_root}/resources/fonts/droid/DroidSansFallback.ttc)
SET(      FONT_CJK_FULL_SRC ${mupdf_root}/resources/fonts/droid/DroidSansFallbackFull.ttc)

ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gen_font_base14.h
    COMMAND fontdump ${CMAKE_CURRENT_BINARY_DIR}/gen_font_base14.h ${FONT_BASE14_SRC}
    VERBATIM
)
ADD_CUSTOM_COMMAND(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gen_font_droid.h
    COMMAND fontdump ${CMAKE_CURRENT_BINARY_DIR}/gen_font_droid.h ${FONT_DROID_SRC}
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
INCLUDE_DIRECTORIES( ${mupdf_root}/scripts/jpeg )
INCLUDE_DIRECTORIES( ${mupdf_jpeg_root} )
# JBIG2
INCLUDE_DIRECTORIES( ${mupdf_jbig2_root} )
# FreeType2
INCLUDE_DIRECTORIES( ${mupdf_root}/scripts/freetype )
INCLUDE_DIRECTORIES( ${mupdf_ft2_root} )
# OpenJPEG
INCLUDE_DIRECTORIES( ${mupdf_root}/scripts/openjpeg )
INCLUDE_DIRECTORIES( ${mupdf_openjpeg_root} )

ADD_LIBRARY( mymupdf STATIC
  ${mupdf_fitz_SOURCES}
  ${mupdf_fitz_HEADERS}
  ${mupdf_pdf_SOURCES}
  ${mupdf_pdf_HEADERS}
  ${mupdf_gen_HEADERS}
)
