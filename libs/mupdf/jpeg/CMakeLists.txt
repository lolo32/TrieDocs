##############
# JPEG library from IJG
SET( mupdf_jpeg_ROOT "$ENV{mupdf_ROOT}/thirdparty/jpeg" )
SET(mupdf_jpeg_SOURCES
    "${mupdf_jpeg_ROOT}/jaricom.c"
    "${mupdf_jpeg_ROOT}/jcomapi.c"
    "${mupdf_jpeg_ROOT}/jdapimin.c"
    "${mupdf_jpeg_ROOT}/jdapistd.c"
    "${mupdf_jpeg_ROOT}/jdarith.c"
    "${mupdf_jpeg_ROOT}/jdatadst.c"
    "${mupdf_jpeg_ROOT}/jdatasrc.c"
    "${mupdf_jpeg_ROOT}/jdcoefct.c"
    "${mupdf_jpeg_ROOT}/jdcolor.c"
    "${mupdf_jpeg_ROOT}/jddctmgr.c"
    "${mupdf_jpeg_ROOT}/jdhuff.c"
    "${mupdf_jpeg_ROOT}/jdinput.c"
    "${mupdf_jpeg_ROOT}/jdmainct.c"
    "${mupdf_jpeg_ROOT}/jdmarker.c"
    "${mupdf_jpeg_ROOT}/jdmaster.c"
    "${mupdf_jpeg_ROOT}/jdmerge.c"
    "${mupdf_jpeg_ROOT}/jdpostct.c"
    "${mupdf_jpeg_ROOT}/jdsample.c"
    "${mupdf_jpeg_ROOT}/jdtrans.c"
    "${mupdf_jpeg_ROOT}/jerror.c"
    "${mupdf_jpeg_ROOT}/jfdctflt.c"
    "${mupdf_jpeg_ROOT}/jfdctfst.c"
    "${mupdf_jpeg_ROOT}/jfdctint.c"
    "${mupdf_jpeg_ROOT}/jidctflt.c"
    "${mupdf_jpeg_ROOT}/jidctfst.c"
    "${mupdf_jpeg_ROOT}/jidctint.c"
    "${mupdf_jpeg_ROOT}/jmemmgr.c"
    "${mupdf_jpeg_ROOT}/jquant1.c"
    "${mupdf_jpeg_ROOT}/jquant2.c"
    "${mupdf_jpeg_ROOT}/jutils.c"
)
ADD_LIBRARY( jpeg STATIC ${mupdf_jpeg_SOURCES} )
SET_TARGET_PROPERTIES(jpeg
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
)

INCLUDE_DIRECTORIES( "$ENV{mupdf_ROOT}/scripts/jpeg" )

ADD_DEFINITIONS( -Dmain=xxxmain )
