#ifndef dispatchKernel_cnets_osblinnikov_github_com_H
#define dispatchKernel_cnets_osblinnikov_github_com_H

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/dispatchKernel/dispatcher/dispatcher.h"
#include "github.com/osblinnikov/cnets/runnablesContainer/runnablesContainer.h"
#include "github.com/osblinnikov/cnets/dispatchBuffer/dispatchBuffer.h"
#include "github.com/osblinnikov/cnets/readerWriter/readerWriter.h"
#include "github.com/osblinnikov/cnets/types/types.h"
#include "github.com/osblinnikov/cnets/vector/vector.h"

#undef dispatchKernel_cnets_osblinnikov_github_com_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(DISPATCHKERNEL_CNETS_OSBLINNIKOV_GITHUB_COM_STATIC)
  #ifdef dispatchKernel_cnets_osblinnikov_github_com_EXPORT
    #define dispatchKernel_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllexport)
  #else
    #define dispatchKernel_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define dispatchKernel_cnets_osblinnikov_github_com_EXPORT_API extern
#endif

struct dispatchKernel_cnets_osblinnikov_github_com;

dispatchKernel_cnets_osblinnikov_github_com_EXPORT_API
void dispatchKernel_cnets_osblinnikov_github_com_init(struct dispatchKernel_cnets_osblinnikov_github_com *that,
    RunnablesInterface _parent,
    uint32_t _threads,
    int64_t _timeout);

dispatchKernel_cnets_osblinnikov_github_com_EXPORT_API
void dispatchKernel_cnets_osblinnikov_github_com_deinit(struct dispatchKernel_cnets_osblinnikov_github_com *that);

typedef struct dispatchKernel_cnets_osblinnikov_github_com{
    RunnablesInterface parent;
  uint32_t threads;
  int64_t timeout;
  uint32_t startLocalId;
  uint32_t numberOfKernels;
  arrayObject buffersArr;

  dispatcher_dispatchKernel_cnets_osblinnikov_github_com* kernel0;
  dispatchBuffer_cnets_osblinnikov_github_com ids;
  
runnablesContainer_cnets_osblinnikov_github_com* arrContainers;
  
  struct runnablesContainer_cnets_osblinnikov_github_com (*getRunnables)(struct dispatchKernel_cnets_osblinnikov_github_com *that);
  struct runnablesContainer_cnets_osblinnikov_github_com _runnables;
/*[[[end]]] (checksum: 73a28dd649a6982f4c7616c00613e3aa)*/
  struct dispatchBuffer_cnets_osblinnikov_github_com dispatcher;
}dispatchKernel_cnets_osblinnikov_github_com;

#endif /* dispatchKernel_cnets_osblinnikov_github_com_H */
