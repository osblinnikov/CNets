

#ifndef com_github_osblinnikov_cnets_types_H
#define com_github_osblinnikov_cnets_types_H

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


#undef com_github_osblinnikov_cnets_types_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(COM_GITHUB_OSBLINNIKOV_CNETS_TYPES_STATIC)
  #ifdef com_github_osblinnikov_cnets_types_EXPORT
    #define com_github_osblinnikov_cnets_types_EXPORT_API __declspec(dllexport)
  #else
    #define com_github_osblinnikov_cnets_types_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define com_github_osblinnikov_cnets_types_EXPORT_API extern
#endif

struct com_github_osblinnikov_cnets_types;

com_github_osblinnikov_cnets_types_EXPORT_API
void com_github_osblinnikov_cnets_types_init(struct com_github_osblinnikov_cnets_types *that);

com_github_osblinnikov_cnets_types_EXPORT_API
void com_github_osblinnikov_cnets_types_deinit(struct com_github_osblinnikov_cnets_types *that);

typedef struct com_github_osblinnikov_cnets_types{
  
  
/*[[[end]]] (checksum: 6d553314bc383a5b21d70b73caad7b07) (e8f3f714af13c7223c1b4836de7907f6) */

}com_github_osblinnikov_cnets_types;

#include "./binary.h"
#include "./arrayObject.h"
#include "./bufferReadData.h"
#include "./bufferKernelParams.h"
#include "./timeUtils.h"
#include "./statsLocalProtocol.h"

#endif /* com_github_osblinnikov_cnets_types_H */