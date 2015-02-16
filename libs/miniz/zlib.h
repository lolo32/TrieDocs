#ifndef __ZLIB_H_
#define __ZLIB_H_

#define MINIZ_HEADER_FILE_ONLY

#include "miniz.c"

#ifndef z_streamp
    #define z_streamp mz_streamp
#endif

#endif //__ZLIB_H_
