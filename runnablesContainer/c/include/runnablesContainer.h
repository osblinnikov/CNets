

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
void com_github_osblinnikov_cnets_runnablesContainer_initialize(struct com_github_osblinnikov_cnets_runnablesContainer *that);

com_github_osblinnikov_cnets_runnablesContainer_EXPORT_API
void com_github_osblinnikov_cnets_runnablesContainer_deinitialize(struct com_github_osblinnikov_cnets_runnablesContainer *that);

com_github_osblinnikov_cnets_runnablesContainer_EXPORT_API
void com_github_osblinnikov_cnets_runnablesContainer_onKernels(struct com_github_osblinnikov_cnets_runnablesContainer *that);

#undef com_github_osblinnikov_cnets_runnablesContainer_onCreateMacro
#define com_github_osblinnikov_cnets_runnablesContainer_onCreateMacro(_NAME_) /**/

#define com_github_osblinnikov_cnets_runnablesContainer_create(_NAME_)\
    com_github_osblinnikov_cnets_runnablesContainer _NAME_;\
    com_github_osblinnikov_cnets_runnablesContainer_onCreateMacro(_NAME_)\
    com_github_osblinnikov_cnets_runnablesContainer_initialize(&_NAME_);\
    com_github_osblinnikov_cnets_runnablesContainer_onKernels(&_NAME_);

typedef struct com_github_osblinnikov_cnets_runnablesContainer{
  
  
  void (*run)(void *that);
/*[[[end]]] (checksum: 1a39a905456e4d34e632534c683a2492) (acad9c1373418ff87ede0fd9fd1e6d9a)*/
  struct com_github_osblinnikov_cnets_runnablesContainer_Kernel kernel;
  struct com_github_osblinnikov_cnets_runnablesContainer *containers;
  int containers_size;
  struct RunnableStoppable target;
  void (*setContainers)(struct com_github_osblinnikov_cnets_runnablesContainer *that, arrayObject containers);
  void (*setCore)(struct com_github_osblinnikov_cnets_runnablesContainer *that, RunnableStoppable target);
  void (*launch)(struct com_github_osblinnikov_cnets_runnablesContainer *that, BOOL lockLastElement);
  void (*stop)(struct com_github_osblinnikov_cnets_runnablesContainer *that);
}com_github_osblinnikov_cnets_runnablesContainer;



#undef com_github_osblinnikov_cnets_runnablesContainer_onCreateMacro
#define com_github_osblinnikov_cnets_runnablesContainer_onCreateMacro(_NAME_) /**/

#endif /* com_github_osblinnikov_cnets_runnablesContainer_H */