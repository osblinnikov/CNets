

#ifndef readerWriter_cnets_osblinnikov_github_com_H
#define readerWriter_cnets_osblinnikov_github_com_H

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/types/types.h"

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

struct readerWriter_cnets_osblinnikov_github_com;

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
void readerWriter_cnets_osblinnikov_github_com_init(struct readerWriter_cnets_osblinnikov_github_com *that);

readerWriter_cnets_osblinnikov_github_com_EXPORT_API
void readerWriter_cnets_osblinnikov_github_com_deinit(struct readerWriter_cnets_osblinnikov_github_com *that);

typedef struct readerWriter_cnets_osblinnikov_github_com{
  
  
/*[[[end]]] (checksum: 08f36cd5e8ab14740eea75b872aa7327)*/

}readerWriter_cnets_osblinnikov_github_com;

#include "./writer.h"
#include "./statsCollectorStatic.h"
#include "./reader.h"

#endif /* readerWriter_cnets_osblinnikov_github_com_H */