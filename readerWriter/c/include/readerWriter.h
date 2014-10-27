

#ifndef com_github_airutech_cnets_readerWriter_H
#define com_github_airutech_cnets_readerWriter_H

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/airutech/cnets/types/c/include/types.h"

#undef com_github_airutech_cnets_readerWriter_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(com_github_airutech_cnets_readerWriter_STATIC)
  #ifdef com_github_airutech_cnets_readerWriter_EXPORT
    #define com_github_airutech_cnets_readerWriter_EXPORT_API __declspec(dllexport)
  #else
    #define com_github_airutech_cnets_readerWriter_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define com_github_airutech_cnets_readerWriter_EXPORT_API extern
#endif

struct com_github_airutech_cnets_readerWriter;

com_github_airutech_cnets_readerWriter_EXPORT_API
void com_github_airutech_cnets_readerWriter_initialize(struct com_github_airutech_cnets_readerWriter *that);

com_github_airutech_cnets_readerWriter_EXPORT_API
void com_github_airutech_cnets_readerWriter_deinitialize(struct com_github_airutech_cnets_readerWriter *that);

com_github_airutech_cnets_readerWriter_EXPORT_API
void com_github_airutech_cnets_readerWriter_onKernels(struct com_github_airutech_cnets_readerWriter *that);

#undef com_github_airutech_cnets_readerWriter_onCreateMacro
#define com_github_airutech_cnets_readerWriter_onCreateMacro(_NAME_) /**/

#define com_github_airutech_cnets_readerWriter_create(_NAME_)\
    com_github_airutech_cnets_readerWriter _NAME_;\
    com_github_airutech_cnets_readerWriter_onCreateMacro(_NAME_)\
    com_github_airutech_cnets_readerWriter_initialize(&_NAME_);\
    com_github_airutech_cnets_readerWriter_onKernels(&_NAME_);

typedef struct com_github_airutech_cnets_readerWriter{
  
  
  void (*run)(void *that);
/*[[[end]]] (checksum: d06279c7b167311eed502120810b2c58)*/

}com_github_airutech_cnets_readerWriter;

#include "./reader.h"
#include "./writer.h"

#endif /* com_github_airutech_cnets_readerWriter_H */