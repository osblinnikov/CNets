

#ifndef com_github_osblinnikov_cnets_readerWriter_H
#define com_github_osblinnikov_cnets_readerWriter_H

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/types/c/include/types.h"

#undef com_github_osblinnikov_cnets_readerWriter_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(COM_GITHUB_OSBLINNIKOV_CNETS_READERWRITER_STATIC)
  #ifdef com_github_osblinnikov_cnets_readerWriter_EXPORT
    #define com_github_osblinnikov_cnets_readerWriter_EXPORT_API __declspec(dllexport)
  #else
    #define com_github_osblinnikov_cnets_readerWriter_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define com_github_osblinnikov_cnets_readerWriter_EXPORT_API extern
#endif

struct com_github_osblinnikov_cnets_readerWriter;

com_github_osblinnikov_cnets_readerWriter_EXPORT_API
void com_github_osblinnikov_cnets_readerWriter_initialize(struct com_github_osblinnikov_cnets_readerWriter *that);

com_github_osblinnikov_cnets_readerWriter_EXPORT_API
void com_github_osblinnikov_cnets_readerWriter_deinitialize(struct com_github_osblinnikov_cnets_readerWriter *that);

com_github_osblinnikov_cnets_readerWriter_EXPORT_API
void com_github_osblinnikov_cnets_readerWriter_onKernels(struct com_github_osblinnikov_cnets_readerWriter *that);

#undef com_github_osblinnikov_cnets_readerWriter_onCreateMacro
#define com_github_osblinnikov_cnets_readerWriter_onCreateMacro(_NAME_) /**/

#define com_github_osblinnikov_cnets_readerWriter_create(_NAME_)\
    com_github_osblinnikov_cnets_readerWriter _NAME_;\
    com_github_osblinnikov_cnets_readerWriter_onCreateMacro(_NAME_)\
    com_github_osblinnikov_cnets_readerWriter_initialize(&_NAME_);\
    com_github_osblinnikov_cnets_readerWriter_onKernels(&_NAME_);

typedef struct com_github_osblinnikov_cnets_readerWriter{
  
  
  void (*run)(void *that);
/*[[[end]]] (checksum: 21683ff426d73c9a089df61043ff88b6) (2e9094ef91abfbf76fe7ccfd8e9e189c)*/

}com_github_osblinnikov_cnets_readerWriter;

#include "./writer.h"
#include "./statsCollectorStatic.h"
#include "./reader.h"

#endif /* com_github_osblinnikov_cnets_readerWriter_H */