

#ifndef com_github_osblinnikov_cnets_mapBuffer_H
#define com_github_osblinnikov_cnets_mapBuffer_H

#include <pthread.h>

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/types/types.h"
#include "github.com/osblinnikov/cnets/readerWriter/readerWriter.h"
#include "github.com/osblinnikov/cnets/queue/queue.h"

#undef com_github_osblinnikov_cnets_mapBuffer_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(COM_GITHUB_OSBLINNIKOV_CNETS_MAPBUFFER_STATIC)
  #ifdef com_github_osblinnikov_cnets_mapBuffer_EXPORT
    #define com_github_osblinnikov_cnets_mapBuffer_EXPORT_API __declspec(dllexport)
  #else
    #define com_github_osblinnikov_cnets_mapBuffer_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define com_github_osblinnikov_cnets_mapBuffer_EXPORT_API extern
#endif

struct com_github_osblinnikov_cnets_mapBuffer;

com_github_osblinnikov_cnets_mapBuffer_EXPORT_API
void com_github_osblinnikov_cnets_mapBuffer_init(struct com_github_osblinnikov_cnets_mapBuffer *that,
    arrayObject _buffers,
    int64_t _timeout_milisec,
    int32_t _readers_grid_size);

com_github_osblinnikov_cnets_mapBuffer_EXPORT_API
void com_github_osblinnikov_cnets_mapBuffer_deinit(struct com_github_osblinnikov_cnets_mapBuffer *that);

com_github_osblinnikov_cnets_mapBuffer_EXPORT_API
reader com_github_osblinnikov_cnets_mapBuffer_createReader(struct com_github_osblinnikov_cnets_mapBuffer *that, int gridId);

com_github_osblinnikov_cnets_mapBuffer_EXPORT_API
writer com_github_osblinnikov_cnets_mapBuffer_createWriter(struct com_github_osblinnikov_cnets_mapBuffer *that, int gridId);



typedef struct com_github_osblinnikov_cnets_mapBuffer{
    arrayObject buffers;
  int64_t timeout_milisec;
  int32_t readers_grid_size;

  
/*[[[end]]] (checksum: a8c312edae6a942d73ed2dad010488eb) (eec6ce3f684ccd63bb8e663efc616e6d)*/
  int                                       uniqueId;
  unsigned                                  *buffers_grid_ids;/*required for storing ids of writers*/
  int                                       *buffers_to_read;
  pthread_spinlock_t                        *buffers_to_read_lock;
  com_github_osblinnikov_cnets_queue           free_buffers;/*only one queue actually*/
  com_github_osblinnikov_cnets_queue           *grid;
  pthread_spinlock_t                        *grid_mutex;  

  pthread_mutex_t     switch_cv_ow_mutex;
  pthread_mutex_t     switch_cv_mutex;
  pthread_cond_t      switch_cv;
  pthread_mutex_t     free_buffers_cv_ow_mutex;
  pthread_mutex_t     free_buffers_cv_mutex;
  pthread_cond_t      free_buffers_cv;
  pthread_rwlock_t    rwLock;
  linkedContainer     *selectorContainers;
}com_github_osblinnikov_cnets_mapBuffer;

#endif /* com_github_osblinnikov_cnets_mapBuffer_H */