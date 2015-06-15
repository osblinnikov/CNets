#ifndef exports_readerWriter_cnets_osblinnikov_github_com_EXPORT_API
#define exports_readerWriter_cnets_osblinnikov_github_com_EXPORT_API

#include "github.com/osblinnikov/cnets/types/types.h"
#include "github.com/osblinnikov/cnets/vector/vector.h"

#undef readerWriter_cnets_osblinnikov_github_com_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(READERWRITER_CNETS_OSBLINNIKOV_GITHUB_COM_STATIC)
  #ifdef readerWriter_cnets_osblinnikov_github_com_EXPORT
    #define readerWriter_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllexport)
  #else
    #define readerWriter_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define readerWriter_cnets_osblinnikov_github_com_EXPORT_API extern
#endif

#endif /*exports_readerWriter_cnets_osblinnikov_github_com_EXPORT_API*/
