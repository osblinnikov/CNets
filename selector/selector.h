

#ifndef selector_cnets_osblinnikov_github_com_H
#define selector_cnets_osblinnikov_github_com_H

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/mapBuffer/mapBuffer.h"
#include "github.com/osblinnikov/cnets/queue/queue.h"
#include "github.com/osblinnikov/cnets/runnablesContainer/runnablesContainer.h"
#include "github.com/osblinnikov/cnets/types/types.h"
#include "github.com/osblinnikov/cnets/readerWriter/readerWriter.h"
#include "github.com/osblinnikov/cnets/vector/vector.h"

#undef selector_cnets_osblinnikov_github_com_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(SELECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_STATIC)
  #ifdef selector_cnets_osblinnikov_github_com_EXPORT
    #define selector_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllexport)
  #else
    #define selector_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define selector_cnets_osblinnikov_github_com_EXPORT_API extern
#endif

struct selector_cnets_osblinnikov_github_com;

selector_cnets_osblinnikov_github_com_EXPORT_API
void selector_cnets_osblinnikov_github_com_init(struct selector_cnets_osblinnikov_github_com *that,
    arrayObject _reducableReaders);

selector_cnets_osblinnikov_github_com_EXPORT_API
void selector_cnets_osblinnikov_github_com_deinit(struct selector_cnets_osblinnikov_github_com *that);

selector_cnets_osblinnikov_github_com_EXPORT_API
reader selector_cnets_osblinnikov_github_com_createReader(struct selector_cnets_osblinnikov_github_com *that, int gridId);

selector_cnets_osblinnikov_github_com_EXPORT_API
writer selector_cnets_osblinnikov_github_com_createWriter(struct selector_cnets_osblinnikov_github_com *that, int gridId);

typedef struct selector_cnets_osblinnikov_github_com{
  void *_readerIds_, *_writerIds_;
  void (*readerIdsDestructor)(void*);
  void (*writerIdsDestructor)(void*);
  arrayObject reducableReaders;

  
/*[[[end]]] (checksum: 98114602d917a85c94da07a597364bcb)*/
    linkedContainer *allContainers;
    uint32_t        *writesToContainers;
    int64_t         timeout_milisec;
    int32_t         lastReadId;
    int32_t         sumWrites;
    pthread_mutex_t switch_cv_lock;
    pthread_cond_t  switch_cv;
    volatile linkedContainer     *selectorContainers;
    volatile short  isEnabled;
}selector_cnets_osblinnikov_github_com;

#endif /* selector_cnets_osblinnikov_github_com_H */
