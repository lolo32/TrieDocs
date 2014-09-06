#ifndef LIBMYMINIZ_H
#define LIBMYMINIZ_H

/* désactive le support du ZIP */
//#define MINIZ_NO_ARCHIVE_APIS

#define MINIZ_NO_STDIO

#define MINIZ_NO_TIME

#define MINIZ_NO_ZLIB_COMPATIBLE_NAME

#ifndef MZ_LIBMINIZ

#if 0
// -----------------------------
// Définitions dans miniz.c à appeler depuis l'extérieur

// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
typedef unsigned long mz_ulong;

// Returns the version string of miniz.c.
const char *mz_version(void);

// Single-call compression functions mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
int mz_compress2(unsigned char *pDest, mz_ulong *pDest_len, const unsigned char *pSource, mz_ulong source_len, int level);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
int mz_uncompress(unsigned char *pDest, mz_ulong *pDest_len, const unsigned char *pSource, mz_ulong source_len);
#else

#define MINIZ_HEADER_FILE_ONLY
#include "miniz.c"

#endif

#endif

#endif // LIBMYMINIZ_H
