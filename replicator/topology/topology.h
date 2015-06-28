#ifndef topology_replicator_cnets_osblinnikov_github_com_H
#define topology_replicator_cnets_osblinnikov_github_com_H

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/dispatchKernel/dispatchKernel.h"
#include "github.com/osblinnikov/cnets/selector/selector.h"
#include "github.com/osblinnikov/cnets/runnablesContainer/runnablesContainer.h"
#include "github.com/osblinnikov/cnets/mapBuffer/mapBuffer.h"
#include "github.com/osblinnikov/cnets/readerWriter/readerWriter.h"
#include "github.com/osblinnikov/cnets/queue/queue.h"
#include "github.com/osblinnikov/cnets/types/types.h"
#include "github.com/osblinnikov/cnets/vector/vector.h"

#undef topology_replicator_cnets_osblinnikov_github_com_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(TOPOLOGY_REPLICATOR_CNETS_OSBLINNIKOV_GITHUB_COM_STATIC)
  #ifdef topology_replicator_cnets_osblinnikov_github_com_EXPORT
    #define topology_replicator_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllexport)
  #else
    #define topology_replicator_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define topology_replicator_cnets_osblinnikov_github_com_EXPORT_API extern
#endif

struct topology_replicator_cnets_osblinnikov_github_com;

topology_replicator_cnets_osblinnikov_github_com_EXPORT_API
void topology_replicator_cnets_osblinnikov_github_com_init(struct topology_replicator_cnets_osblinnikov_github_com *that,
    runnablesContainer_cnets_osblinnikov_github_com* _parent,
    uint32_t _maxNumberOfKernelsPerThread,
    uint32_t _countOfThreads,
    char* _bindTo);

topology_replicator_cnets_osblinnikov_github_com_EXPORT_API
void topology_replicator_cnets_osblinnikov_github_com_deinit(struct topology_replicator_cnets_osblinnikov_github_com *that);

typedef struct topology_replicator_cnets_osblinnikov_github_com{
  runnablesContainer_cnets_osblinnikov_github_com* parent;
  uint32_t maxNumberOfKernelsPerThread;
  uint32_t countOfThreads;
  char* bindTo;

  dispatchKernel_cnets_osblinnikov_github_com* kernel0;
  
runnablesContainer_cnets_osblinnikov_github_com* arrContainers;
  
  struct runnablesContainer_cnets_osblinnikov_github_com (*getRunnables)(struct topology_replicator_cnets_osblinnikov_github_com *that);
  struct runnablesContainer_cnets_osblinnikov_github_com _runnables;
/*[[[end]]] (checksum: a8ab7011c6758ccc577dde6f57b7cbc3)*/

}topology_replicator_cnets_osblinnikov_github_com;

#endif /* topology_replicator_cnets_osblinnikov_github_com_H */