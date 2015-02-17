##############
# FreeType 2
SET( mupdf_ft2_ROOT "$ENV{mupdf_ROOT}/thirdparty/freetype" )
SET( mupdf_ft2_SOURCES
    "${mupdf_ft2_ROOT}/src/base/ftbase.c"
    "${mupdf_ft2_ROOT}/src/base/ftbbox.c"
    "${mupdf_ft2_ROOT}/src/base/ftbitmap.c"
    "${mupdf_ft2_ROOT}/src/base/ftdebug.c"
    "${mupdf_ft2_ROOT}/src/base/ftgasp.c"
    "${mupdf_ft2_ROOT}/src/base/ftglyph.c"
    "${mupdf_ft2_ROOT}/src/base/ftinit.c"
    "${mupdf_ft2_ROOT}/src/base/ftstroke.c"
    "${mupdf_ft2_ROOT}/src/base/ftsynth.c"
    "${mupdf_ft2_ROOT}/src/base/ftsystem.c"
    "${mupdf_ft2_ROOT}/src/base/fttype1.c"
    "${mupdf_ft2_ROOT}/src/base/ftxf86.c"
    "${mupdf_ft2_ROOT}/src/cff/cff.c"
    "${mupdf_ft2_ROOT}/src/psaux/psaux.c"
    "${mupdf_ft2_ROOT}/src/pshinter/pshinter.c"
    "${mupdf_ft2_ROOT}/src/psnames/psnames.c"
    "${mupdf_ft2_ROOT}/src/raster/raster.c"
    "${mupdf_ft2_ROOT}/src/sfnt/sfnt.c"
    "${mupdf_ft2_ROOT}/src/smooth/smooth.c"
    "${mupdf_ft2_ROOT}/src/truetype/truetype.c"
    "${mupdf_ft2_ROOT}/src/type1/type1.c"
    "${mupdf_ft2_ROOT}/src/cid/type1cid.c"
)
ADD_LIBRARY( freetype STATIC ${mupdf_ft2_SOURCES} )
SET_TARGET_PROPERTIES(freetype
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
)

ADD_DEFINITIONS( -DFT2_BUILD_LIBRARY                     )
ADD_DEFINITIONS( -DDARWIN_NO_CARBON                      )
ADD_DEFINITIONS( -DFT_CONFIG_MODULES_H="slimftmodules.h" )
ADD_DEFINITIONS( -DFT_CONFIG_OPTIONS_H="slimftoptions.h" )

INCLUDE_DIRECTORIES( "$ENV{mupdf_ROOT}/scripts/freetype"                )
INCLUDE_DIRECTORIES( "$ENV{mupdf_ROOT}/thirdparty/freetype/include"     )
