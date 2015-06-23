

#ifndef types_cnets_osblinnikov_github_com_H
#define types_cnets_osblinnikov_github_com_H

#include <stdio.h>
#include <errno.h>

#ifdef WIN32
/*TO MAKE VC HAPPY, (need to include it before windows.h*/
    #include <winsock2.h>
#endif

#if defined(WIN32) && !defined(CYGWIN)
    #ifndef WINDOWS_HEADER_H_
    #define WINDOWS_HEADER_H_
        #include <windows.h>
        #include <windef.h>
    #endif
#else
  #ifndef BOOL
    typedef unsigned char           BOOL;
  #endif
#endif

#ifndef FALSE
  #define FALSE       0
#endif

#ifndef TRUE
  #define TRUE        1
#endif

#if defined(WIN32) && !defined(CYGWIN)&& !defined(__MINGW32__)
    #include "./vc/stdint.h"
    #include "./vc/inttypes.h"
#else
    #include <inttypes.h>
#endif

#if defined(WIN32) && !defined(CYGWIN)&& !defined(__MINGW32__)
    #include <malloc.h>
    #define salloca _malloca
#else
    #include <alloca.h>
    #define salloca alloca
#endif



/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/


#undef types_cnets_osblinnikov_github_com_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(TYPES_CNETS_OSBLINNIKOV_GITHUB_COM_STATIC)
  #ifdef types_cnets_osblinnikov_github_com_EXPORT
    #define types_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllexport)
  #else
    #define types_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define types_cnets_osblinnikov_github_com_EXPORT_API extern
#endif

struct types_cnets_osblinnikov_github_com;

types_cnets_osblinnikov_github_com_EXPORT_API
void types_cnets_osblinnikov_github_com_init(struct types_cnets_osblinnikov_github_com *that);

types_cnets_osblinnikov_github_com_EXPORT_API
void types_cnets_osblinnikov_github_com_deinit(struct types_cnets_osblinnikov_github_com *that);

typedef struct types_cnets_osblinnikov_github_com{
  
  
/*[[[end]]] (checksum: 561141b78b2e1b85cabe92c4c6cf71b9)*/

}types_cnets_osblinnikov_github_com;

#include "./binary.h"
#include "./arrayObject.h"
#include "./bufferReadData.h"
#include "./bufferKernelParams.h"
#include "./timeUtils.h"
#include "./statsLocalProtocol.h"
#include "./serializator.h"

#endif /* types_cnets_osblinnikov_github_com_H */
