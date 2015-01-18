#ifndef LIBMYMINIZ_H
#define LIBMYMINIZ_H

/* désactive le support du ZIP */
//#define MINIZ_NO_ARCHIVE_APIS

#define MINIZ_NO_STDIO

#define MINIZ_NO_TIME

#define MINIZ_NO_ZLIB_COMPATIBLE_NAME

#ifndef MZ_LIBMINIZ

#define MINIZ_HEADER_FILE_ONLY
#include "../../3party/miniz-r63/miniz.c"

#endif

#endif // LIBMYMINIZ_H
