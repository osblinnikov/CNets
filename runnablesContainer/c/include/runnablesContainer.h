

#ifndef com_github_airutech_cnets_runnablesContainer_H
#define com_github_airutech_cnets_runnablesContainer_H

#include "./Kernel.h"
#include "./RunnableStoppable.h"

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/airutech/cnets/types/c/include/types.h"

#undef com_github_airutech_cnets_runnablesContainer_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(com_github_airutech_cnets_runnablesContainer_STATIC)
  #ifdef com_github_airutech_cnets_runnablesContainer_EXPORT
    #define com_github_airutech_cnets_runnablesContainer_EXPORT_API __declspec(dllexport)
  #else
    #define com_github_airutech_cnets_runnablesContainer_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define com_github_airutech_cnets_runnablesContainer_EXPORT_API extern
#endif

struct com_github_airutech_cnets_runnablesContainer;

com_github_airutech_cnets_runnablesContainer_EXPORT_API
void com_github_airutech_cnets_runnablesContainer_initialize(struct com_github_airutech_cnets_runnablesContainer *that);

com_github_airutech_cnets_runnablesContainer_EXPORT_API
void com_github_airutech_cnets_runnablesContainer_deinitialize(struct com_github_airutech_cnets_runnablesContainer *that);

com_github_airutech_cnets_runnablesContainer_EXPORT_API
void com_github_airutech_cnets_runnablesContainer_onKernels(struct com_github_airutech_cnets_runnablesContainer *that);

#undef com_github_airutech_cnets_runnablesContainer_onCreateMacro
#define com_github_airutech_cnets_runnablesContainer_onCreateMacro(_NAME_) /**/

#define com_github_airutech_cnets_runnablesContainer_create(_NAME_)\
    com_github_airutech_cnets_runnablesContainer _NAME_;\
    com_github_airutech_cnets_runnablesContainer_onCreateMacro(_NAME_)\
    com_github_airutech_cnets_runnablesContainer_initialize(&_NAME_);\
    com_github_airutech_cnets_runnablesContainer_onKernels(&_NAME_);

typedef struct com_github_airutech_cnets_runnablesContainer{
  
  
  void (*run)(void *that);
/*[[[end]]] (checksum: 0de4fc6614973ceb52a3ee7dcbe72cf9)*/
  struct com_github_airutech_cnets_runnablesContainer_Kernel kernel;
  struct com_github_airutech_cnets_runnablesContainer *containers;
  int containers_size;
  struct RunnableStoppable target;
  void (*setContainers)(struct com_github_airutech_cnets_runnablesContainer *that, arrayObject containers);
  void (*setCore)(struct com_github_airutech_cnets_runnablesContainer *that, RunnableStoppable target);
  void (*launch)(struct com_github_airutech_cnets_runnablesContainer *that, BOOL lockLastElement);
  void (*stop)(struct com_github_airutech_cnets_runnablesContainer *that);
}com_github_airutech_cnets_runnablesContainer;



#undef com_github_airutech_cnets_runnablesContainer_onCreateMacro
#define com_github_airutech_cnets_runnablesContainer_onCreateMacro(_NAME_) /**/

#endif /* com_github_airutech_cnets_runnablesContainer_H */