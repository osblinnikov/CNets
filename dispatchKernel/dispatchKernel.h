#ifndef dispatchKernel_cnets_osblinnikov_github_com_H
#define dispatchKernel_cnets_osblinnikov_github_com_H

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/selector/selector.h"
#include "github.com/osblinnikov/cnets/runnablesContainer/runnablesContainer.h"
#include "github.com/osblinnikov/cnets/mapBuffer/mapBuffer.h"
#include "github.com/osblinnikov/cnets/readerWriter/readerWriter.h"
#include "github.com/osblinnikov/cnets/queue/queue.h"
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
    runnablesContainer_cnets_osblinnikov_github_com* _parent,
    uint32_t _maxNumberOfKernels,
    uint32_t _threadId);

dispatchKernel_cnets_osblinnikov_github_com_EXPORT_API
void dispatchKernel_cnets_osblinnikov_github_com_deinit(struct dispatchKernel_cnets_osblinnikov_github_com *that);

typedef struct dispatchKernel_cnets_osblinnikov_github_com{
  runnablesContainer_cnets_osblinnikov_github_com* parent;
  uint32_t maxNumberOfKernels;
  uint32_t threadId;
  arrayObject readers;
  reader readerSelector;
  arrayObject kernels;

  
  struct runnablesContainer_cnets_osblinnikov_github_com (*getRunnables)(struct dispatchKernel_cnets_osblinnikov_github_com *that);
  struct runnablesContainer_cnets_osblinnikov_github_com _runnables;
/*[[[end]]] (checksum: 1822a587576e35687e19aabeb7300580)*/
  struct selector_cnets_osblinnikov_github_com selector;
}dispatchKernel_cnets_osblinnikov_github_com;

#endif /* dispatchKernel_cnets_osblinnikov_github_com_H */