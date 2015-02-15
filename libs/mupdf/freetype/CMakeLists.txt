##############
# FreeType 2
SET( mupdf_ft2_root ${mupdf_root}/thirdparty/freetype )
SET( mupdf_ft2_SOURCES
    ${mupdf_ft2_root}/src/base/ftbase.c
    ${mupdf_ft2_root}/src/base/ftbbox.c
    ${mupdf_ft2_root}/src/base/ftbitmap.c
    ${mupdf_ft2_root}/src/base/ftdebug.c
    ${mupdf_ft2_root}/src/base/ftgasp.c
    ${mupdf_ft2_root}/src/base/ftglyph.c
    ${mupdf_ft2_root}/src/base/ftinit.c
    ${mupdf_ft2_root}/src/base/ftstroke.c
    ${mupdf_ft2_root}/src/base/ftsynth.c
    ${mupdf_ft2_root}/src/base/ftsystem.c
    ${mupdf_ft2_root}/src/base/fttype1.c
    ${mupdf_ft2_root}/src/base/ftxf86.c
    ${mupdf_ft2_root}/src/cff/cff.c
    ${mupdf_ft2_root}/src/psaux/psaux.c
    ${mupdf_ft2_root}/src/pshinter/pshinter.c
    ${mupdf_ft2_root}/src/psnames/psnames.c
    ${mupdf_ft2_root}/src/raster/raster.c
    ${mupdf_ft2_root}/src/sfnt/sfnt.c
    ${mupdf_ft2_root}/src/smooth/smooth.c
    ${mupdf_ft2_root}/src/truetype/truetype.c
    ${mupdf_ft2_root}/src/type1/type1.c
    ${mupdf_ft2_root}/src/cid/type1cid.c
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

INCLUDE_DIRECTORIES( ${mupdf_root}/scripts/freetype                )
INCLUDE_DIRECTORIES( ${mupdf_root}/thirdparty/freetype/include     )
