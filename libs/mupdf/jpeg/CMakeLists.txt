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

INCLUDE_DIRECTORIES( ${mupdf_root}/scripts/jpeg                    )

ADD_DEFINITIONS( -Dmain=xxxmain )
