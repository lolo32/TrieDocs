##############
# OpenJPEG
SET( mupdf_openjpeg_root ${mupdf_root}/thirdparty/openjpeg/libopenjpeg )
SET( mupdf_openjpeg_SOURCES
    ${mupdf_openjpeg_root}/bio.c
    ${mupdf_openjpeg_root}/cidx_manager.c
    ${mupdf_openjpeg_root}/cio.c
    ${mupdf_openjpeg_root}/dwt.c
    ${mupdf_openjpeg_root}/event.c
    ${mupdf_openjpeg_root}/function_list.c
    ${mupdf_openjpeg_root}/image.c
    ${mupdf_openjpeg_root}/invert.c
    ${mupdf_openjpeg_root}/j2k.c
    ${mupdf_openjpeg_root}/jp2.c
    ${mupdf_openjpeg_root}/mct.c
    ${mupdf_openjpeg_root}/mqc.c
    ${mupdf_openjpeg_root}/openjpeg.c
    ${mupdf_openjpeg_root}/opj_clock.c
    ${mupdf_openjpeg_root}/phix_manager.c
    ${mupdf_openjpeg_root}/pi.c
    ${mupdf_openjpeg_root}/ppix_manager.c
    ${mupdf_openjpeg_root}/raw.c
    ${mupdf_openjpeg_root}/t1.c
    ${mupdf_openjpeg_root}/t2.c
    ${mupdf_openjpeg_root}/tcd.c
    ${mupdf_openjpeg_root}/tgt.c
    ${mupdf_openjpeg_root}/thix_manager.c
    ${mupdf_openjpeg_root}/tpix_manager.c
)
ADD_LIBRARY( openjpeg STATIC ${mupdf_openjpeg_SOURCES} )
SET_TARGET_PROPERTIES(openjpeg
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
)

INCLUDE_DIRECTORIES( ${mupdf_root}/scripts/openjpeg )
INCLUDE_DIRECTORIES( ${mupdf_openjpeg_root}         )

ADD_DEFINITIONS( -DOPJ_STATIC        )
ADD_DEFINITIONS( -DOPJ_HAVE_STDINT_H )
