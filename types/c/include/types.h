

#ifndef com_github_airutech_cnets_types_H
#define com_github_airutech_cnets_types_H

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

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/


#undef com_github_airutech_cnets_types_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(com_github_airutech_cnets_types_STATIC)
  #ifdef com_github_airutech_cnets_types_EXPORT
    #define com_github_airutech_cnets_types_EXPORT_API __declspec(dllexport)
  #else
    #define com_github_airutech_cnets_types_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define com_github_airutech_cnets_types_EXPORT_API extern
#endif

struct com_github_airutech_cnets_types;

com_github_airutech_cnets_types_EXPORT_API
void com_github_airutech_cnets_types_initialize(struct com_github_airutech_cnets_types *that);

com_github_airutech_cnets_types_EXPORT_API
void com_github_airutech_cnets_types_deinitialize(struct com_github_airutech_cnets_types *that);

com_github_airutech_cnets_types_EXPORT_API
void com_github_airutech_cnets_types_onKernels(struct com_github_airutech_cnets_types *that);

#undef com_github_airutech_cnets_types_onCreateMacro
#define com_github_airutech_cnets_types_onCreateMacro(_NAME_) /**/

#define com_github_airutech_cnets_types_create(_NAME_)\
    com_github_airutech_cnets_types _NAME_;\
    com_github_airutech_cnets_types_onCreateMacro(_NAME_)\
    com_github_airutech_cnets_types_initialize(&_NAME_);\
    com_github_airutech_cnets_types_onKernels(&_NAME_);

typedef struct com_github_airutech_cnets_types{
  
  
  void (*run)(void *that);
/*[[[end]]] (checksum: c432b8bb5cd1a9186fbceab080fe8872) */

}com_github_airutech_cnets_types;

#include "./binary.h"
#include "./arrayObject.h"
#include "./bufferReadData.h"
#include "./bufferKernelParams.h"
#include "./timeUtils.h"

#endif /* com_github_airutech_cnets_types_H */