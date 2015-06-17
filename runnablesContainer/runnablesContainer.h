

#ifndef runnablesContainer_cnets_osblinnikov_github_com_H
#define runnablesContainer_cnets_osblinnikov_github_com_H

#include "./Kernel.h"
#include "./RunnableStoppable.h"

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/types/types.h"

#undef runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(RUNNABLESCONTAINER_CNETS_OSBLINNIKOV_GITHUB_COM_STATIC)
  #ifdef runnablesContainer_cnets_osblinnikov_github_com_EXPORT
    #define runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllexport)
  #else
    #define runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API extern
#endif

struct runnablesContainer_cnets_osblinnikov_github_com;

runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API
void runnablesContainer_cnets_osblinnikov_github_com_init(struct runnablesContainer_cnets_osblinnikov_github_com *that);

runnablesContainer_cnets_osblinnikov_github_com_EXPORT_API
void runnablesContainer_cnets_osblinnikov_github_com_deinit(struct runnablesContainer_cnets_osblinnikov_github_com *that);

typedef struct runnablesContainer_cnets_osblinnikov_github_com{
  
  
/*[[[end]]] (checksum: 1674936ae9b5e42d789658026bda0da2)*/
  struct runnablesContainer_cnets_osblinnikov_github_com_Kernel kernel;
  struct runnablesContainer_cnets_osblinnikov_github_com *containers;
  int containers_size;
  struct RunnableStoppable target;
  void (*setContainers)(struct runnablesContainer_cnets_osblinnikov_github_com *that, arrayObject containers);
  void (*setCore)(struct runnablesContainer_cnets_osblinnikov_github_com *that, RunnableStoppable target, unsigned id, short dedicatedThread);
  void (*launch)(struct runnablesContainer_cnets_osblinnikov_github_com *that, BOOL lockLastElement);
  void (*stop)(struct runnablesContainer_cnets_osblinnikov_github_com *that);
}runnablesContainer_cnets_osblinnikov_github_com;

#endif /* runnablesContainer_cnets_osblinnikov_github_com_H */
