

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
void com_github_osblinnikov_cnets_readerWriter_init(struct com_github_osblinnikov_cnets_readerWriter *that);

com_github_osblinnikov_cnets_readerWriter_EXPORT_API
void com_github_osblinnikov_cnets_readerWriter_deinit(struct com_github_osblinnikov_cnets_readerWriter *that);

typedef struct com_github_osblinnikov_cnets_readerWriter{
  
  
/*[[[end]]] (checksum: 42e8e6abb9603470d3c32fc387a4ae7e) (2e9094ef91abfbf76fe7ccfd8e9e189c)*/

}com_github_osblinnikov_cnets_readerWriter;

#include "./writer.h"
#include "./statsCollectorStatic.h"
#include "./reader.h"

#endif /* com_github_osblinnikov_cnets_readerWriter_H */