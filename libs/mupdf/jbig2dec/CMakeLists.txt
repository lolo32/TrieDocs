##############
# JBIG2DEC
SET( mupdf_jbig2_root ${mupdf_root}/thirdparty/jbig2dec )
SET( mupdf_jbig2_SOURCES
    ${mupdf_jbig2_root}/jbig2.c
    ${mupdf_jbig2_root}/jbig2_arith.c
    ${mupdf_jbig2_root}/jbig2_arith_iaid.c
    ${mupdf_jbig2_root}/jbig2_arith_int.c
    ${mupdf_jbig2_root}/jbig2_generic.c
    ${mupdf_jbig2_root}/jbig2_halftone.c
    ${mupdf_jbig2_root}/jbig2_huffman.c
    ${mupdf_jbig2_root}/jbig2_image.c
    ${mupdf_jbig2_root}/jbig2_metadata.c
    ${mupdf_jbig2_root}/jbig2_mmr.c
    ${mupdf_jbig2_root}/jbig2_page.c
    ${mupdf_jbig2_root}/jbig2_refinement.c
    ${mupdf_jbig2_root}/jbig2_segment.c
    ${mupdf_jbig2_root}/jbig2_symbol_dict.c
    ${mupdf_jbig2_root}/jbig2_text.c
    ${mupdf_jbig2_root}/os_types.h
)

# Patch the sources, adding int64_t and uint64_t
FILE( READ ${mupdf_jbig2_root}/os_types.h _orig )
STRING( FIND "${_orig}" "uint64_t;" _position )
IF( ${_position} LESS 1 )
    STRING( REPLACE "typedef signed int     int32_t" "typedef signed int     int32_t;\n   typedef unsigned long long uint64_t;\n   typedef signed long long int64_t" _patch "${_orig}" )
    FILE( WRITE ${mupdf_jbig2_root}/os_types.h "${_patch}")
ENDIF()

ADD_LIBRARY( jbig2dec STATIC ${mupdf_jbig2_SOURCES} )

ADD_DEFINITIONS( -DHAVE_STDINT_H )
