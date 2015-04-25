

#ifndef com_github_osblinnikov_cnets_runnablesContainer_H
#define com_github_osblinnikov_cnets_runnablesContainer_H

#include "./Kernel.h"
#include "./RunnableStoppable.h"

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/types/c/include/types.h"

#undef com_github_osblinnikov_cnets_runnablesContainer_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(COM_GITHUB_OSBLINNIKOV_CNETS_RUNNABLESCONTAINER_STATIC)
  #ifdef com_github_osblinnikov_cnets_runnablesContainer_EXPORT
    #define com_github_osblinnikov_cnets_runnablesContainer_EXPORT_API __declspec(dllexport)
  #else
    #define com_github_osblinnikov_cnets_runnablesContainer_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define com_github_osblinnikov_cnets_runnablesContainer_EXPORT_API extern
#endif

struct com_github_osblinnikov_cnets_runnablesContainer;

com_github_osblinnikov_cnets_runnablesContainer_EXPORT_API
void com_github_osblinnikov_cnets_runnablesContainer_init(struct com_github_osblinnikov_cnets_runnablesContainer *that);

com_github_osblinnikov_cnets_runnablesContainer_EXPORT_API
void com_github_osblinnikov_cnets_runnablesContainer_deinit(struct com_github_osblinnikov_cnets_runnablesContainer *that);

typedef struct com_github_osblinnikov_cnets_runnablesContainer{
  
  
/*[[[end]]] (checksum: 8c192ea6145c4d5abd8b74d6a5f32d6d) (acad9c1373418ff87ede0fd9fd1e6d9a)*/
  struct com_github_osblinnikov_cnets_runnablesContainer_Kernel kernel;
  struct com_github_osblinnikov_cnets_runnablesContainer *containers;
  int containers_size;
  struct RunnableStoppable target;
  void (*setContainers)(struct com_github_osblinnikov_cnets_runnablesContainer *that, arrayObject containers);
  void (*setCore)(struct com_github_osblinnikov_cnets_runnablesContainer *that, RunnableStoppable target);
  void (*launch)(struct com_github_osblinnikov_cnets_runnablesContainer *that, BOOL lockLastElement);
  void (*stop)(struct com_github_osblinnikov_cnets_runnablesContainer *that);
}com_github_osblinnikov_cnets_runnablesContainer;

#endif /* com_github_osblinnikov_cnets_runnablesContainer_H */