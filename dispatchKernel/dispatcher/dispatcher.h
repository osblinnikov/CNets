#ifndef dispatcher_dispatchKernel_cnets_osblinnikov_github_com_H
#define dispatcher_dispatchKernel_cnets_osblinnikov_github_com_H

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/runnablesContainer/runnablesContainer.h"
#include "github.com/osblinnikov/cnets/readerWriter/readerWriter.h"
#include "github.com/osblinnikov/cnets/types/types.h"
#include "github.com/osblinnikov/cnets/vector/vector.h"

#undef dispatcher_dispatchKernel_cnets_osblinnikov_github_com_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(DISPATCHER_DISPATCHKERNEL_CNETS_OSBLINNIKOV_GITHUB_COM_STATIC)
  #ifdef dispatcher_dispatchKernel_cnets_osblinnikov_github_com_EXPORT
    #define dispatcher_dispatchKernel_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllexport)
  #else
    #define dispatcher_dispatchKernel_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define dispatcher_dispatchKernel_cnets_osblinnikov_github_com_EXPORT_API extern
#endif

struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com;

dispatcher_dispatchKernel_cnets_osblinnikov_github_com_EXPORT_API
void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_init(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that,
    RunnablesInterface _parent,
    uint32_t _threadId,
    uint32_t _numberOfKernels,
    uint32_t _startLocalId,
    reader _rids0);

dispatcher_dispatchKernel_cnets_osblinnikov_github_com_EXPORT_API
void dispatcher_dispatchKernel_cnets_osblinnikov_github_com_deinit(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that);

typedef struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com{
    RunnablesInterface parent;
  uint32_t threadId;
  uint32_t numberOfKernels;
  uint32_t startLocalId;
  uint32_t _kernelId;
  arrayObject runObjects;
  reader rids0;

  
  struct runnablesContainer_cnets_osblinnikov_github_com (*getRunnables)(struct dispatcher_dispatchKernel_cnets_osblinnikov_github_com *that);
  struct runnablesContainer_cnets_osblinnikov_github_com _runnables;
/*[[[end]]] (checksum: cdc7acd18dad226e3d20eb95088e91b0)*/

}dispatcher_dispatchKernel_cnets_osblinnikov_github_com;

#endif /* dispatcher_dispatchKernel_cnets_osblinnikov_github_com_H */