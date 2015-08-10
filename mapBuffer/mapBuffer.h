

#ifndef mapBuffer_cnets_osblinnikov_github_com_H
#define mapBuffer_cnets_osblinnikov_github_com_H

#include <pthread.h>

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/readerWriter/readerWriter.h"
#include "github.com/osblinnikov/cnets/queue/queue.h"
#include "github.com/osblinnikov/cnets/types/types.h"

#undef mapBuffer_cnets_osblinnikov_github_com_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(MAPBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_STATIC)
  #ifdef mapBuffer_cnets_osblinnikov_github_com_EXPORT
    #define mapBuffer_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllexport)
  #else
    #define mapBuffer_cnets_osblinnikov_github_com_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define mapBuffer_cnets_osblinnikov_github_com_EXPORT_API extern
#endif

struct mapBuffer_cnets_osblinnikov_github_com;

mapBuffer_cnets_osblinnikov_github_com_EXPORT_API
void mapBuffer_cnets_osblinnikov_github_com_init(struct mapBuffer_cnets_osblinnikov_github_com *that,
    arrayObject _buffers,
    int64_t _timeout_milisec,
    int32_t _readers_grid_size);

mapBuffer_cnets_osblinnikov_github_com_EXPORT_API
void mapBuffer_cnets_osblinnikov_github_com_deinit(struct mapBuffer_cnets_osblinnikov_github_com *that);

mapBuffer_cnets_osblinnikov_github_com_EXPORT_API
reader mapBuffer_cnets_osblinnikov_github_com_createReader(struct mapBuffer_cnets_osblinnikov_github_com *that, int gridId);

mapBuffer_cnets_osblinnikov_github_com_EXPORT_API
writer mapBuffer_cnets_osblinnikov_github_com_createWriter(struct mapBuffer_cnets_osblinnikov_github_com *that, int gridId);

typedef struct mapBuffer_cnets_osblinnikov_github_com{
  void *_readerIds_, *_writerIds_;
  void (*readerIdsDestructor)(void*);
  void (*writerIdsDestructor)(void*);
  arrayObject buffers;
  int64_t timeout_milisec;
  int32_t readers_grid_size;

  
/*[[[end]]] (checksum: dd6eb6a85e572f12e19ede34b179b0c9)*/
  int                                        uniqueId;
  unsigned                                  *buffers_grid_ids;/*required for storing ids of writers*/
  int                                       *buffers_to_read;
  pthread_spinlock_t                        *buffers_to_read_lock;
  queue_cnets_osblinnikov_github_com         free_buffers;/*only one queue actually*/
  queue_cnets_osblinnikov_github_com        *grid;
  pthread_spinlock_t                        *grid_mutex, free_buffers_queue_mutex;
  unsigned                                  *isEnabled;

  pthread_mutex_t     switch_cv_ow_mutex;
  pthread_mutex_t     switch_cv_mutex;
  pthread_cond_t      switch_cv;
  pthread_mutex_t     free_buffers_cv_mutex;
  pthread_cond_t      free_buffers_cv;
  volatile linkedContainer     *selectorContainers;
}mapBuffer_cnets_osblinnikov_github_com;

#endif /* mapBuffer_cnets_osblinnikov_github_com_H */
