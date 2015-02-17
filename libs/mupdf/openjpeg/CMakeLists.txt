##############
# OpenJPEG
SET( mupdf_openjpeg_ROOT "$ENV{mupdf_ROOT}/thirdparty/openjpeg/libopenjpeg" )
SET( mupdf_openjpeg_SOURCES
    "${mupdf_openjpeg_ROOT}/bio.c"
    "${mupdf_openjpeg_ROOT}/cidx_manager.c"
    "${mupdf_openjpeg_ROOT}/cio.c"
    "${mupdf_openjpeg_ROOT}/dwt.c"
    "${mupdf_openjpeg_ROOT}/event.c"
    "${mupdf_openjpeg_ROOT}/function_list.c"
    "${mupdf_openjpeg_ROOT}/image.c"
    "${mupdf_openjpeg_ROOT}/invert.c"
    "${mupdf_openjpeg_ROOT}/j2k.c"
    "${mupdf_openjpeg_ROOT}/jp2.c"
    "${mupdf_openjpeg_ROOT}/mct.c"
    "${mupdf_openjpeg_ROOT}/mqc.c"
    "${mupdf_openjpeg_ROOT}/openjpeg.c"
    "${mupdf_openjpeg_ROOT}/opj_clock.c"
    "${mupdf_openjpeg_ROOT}/phix_manager.c"
    "${mupdf_openjpeg_ROOT}/pi.c"
    "${mupdf_openjpeg_ROOT}/ppix_manager.c"
    "${mupdf_openjpeg_ROOT}/raw.c"
    "${mupdf_openjpeg_ROOT}/t1.c"
    "${mupdf_openjpeg_ROOT}/t2.c"
    "${mupdf_openjpeg_ROOT}/tcd.c"
    "${mupdf_openjpeg_ROOT}/tgt.c"
    "${mupdf_openjpeg_ROOT}/thix_manager.c"
    "${mupdf_openjpeg_ROOT}/tpix_manager.c"
)
ADD_LIBRARY( openjpeg STATIC ${mupdf_openjpeg_SOURCES} )
SET_TARGET_PROPERTIES(openjpeg
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
)

INCLUDE_DIRECTORIES( "$ENV{mupdf_ROOT}/scripts/openjpeg" )
INCLUDE_DIRECTORIES( "${mupdf_openjpeg_ROOT}"            )

ADD_DEFINITIONS( -DOPJ_STATIC        )
ADD_DEFINITIONS( -DOPJ_HAVE_STDINT_H )
