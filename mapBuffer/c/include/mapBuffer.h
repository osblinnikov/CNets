

#ifndef com_github_airutech_cnets_mapBuffer_H
#define com_github_airutech_cnets_mapBuffer_H

#include <pthread.h>

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/airutech/cnets/types/c/include/types.h"
#include "github.com/airutech/cnets/readerWriter/c/include/readerWriter.h"
#include "github.com/airutech/cnets/queue/c/include/queue.h"

#undef com_github_airutech_cnets_mapBuffer_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(com_github_airutech_cnets_mapBuffer_STATIC)
  #ifdef com_github_airutech_cnets_mapBuffer_EXPORT
    #define com_github_airutech_cnets_mapBuffer_EXPORT_API __declspec(dllexport)
  #else
    #define com_github_airutech_cnets_mapBuffer_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define com_github_airutech_cnets_mapBuffer_EXPORT_API extern
#endif

struct com_github_airutech_cnets_mapBuffer;

com_github_airutech_cnets_mapBuffer_EXPORT_API
reader com_github_airutech_cnets_mapBuffer_getReader(struct com_github_airutech_cnets_mapBuffer *that, void* container, int gridId);

com_github_airutech_cnets_mapBuffer_EXPORT_API
writer com_github_airutech_cnets_mapBuffer_getWriter(struct com_github_airutech_cnets_mapBuffer *that, void* container, int gridId);

com_github_airutech_cnets_mapBuffer_EXPORT_API
void com_github_airutech_cnets_mapBuffer_initialize(struct com_github_airutech_cnets_mapBuffer *that);

com_github_airutech_cnets_mapBuffer_EXPORT_API
void com_github_airutech_cnets_mapBuffer_deinitialize(struct com_github_airutech_cnets_mapBuffer *that);

com_github_airutech_cnets_mapBuffer_EXPORT_API
void com_github_airutech_cnets_mapBuffer_onKernels(struct com_github_airutech_cnets_mapBuffer *that);

#undef com_github_airutech_cnets_mapBuffer_onCreateMacro
#define com_github_airutech_cnets_mapBuffer_onCreateMacro(_NAME_) /**/


#define com_github_airutech_cnets_mapBuffer_createReader(_NAME_,_that,_gridId)\
  reader _NAME_ = com_github_airutech_cnets_mapBuffer_getReader(_that,NULL,_gridId);

#define com_github_airutech_cnets_mapBuffer_createWriter(_NAME_,_that,_gridId)\
  writer _NAME_ = com_github_airutech_cnets_mapBuffer_getWriter(_that,NULL,_gridId);

#define com_github_airutech_cnets_mapBuffer_create(_NAME_,_buffers,_timeout_milisec,_readers_grid_size)\
    com_github_airutech_cnets_mapBuffer _NAME_;\
    _NAME_.buffers = _buffers;\
    _NAME_.timeout_milisec = _timeout_milisec;\
    _NAME_.readers_grid_size = _readers_grid_size;\
    com_github_airutech_cnets_mapBuffer_onCreateMacro(_NAME_)\
    com_github_airutech_cnets_mapBuffer_initialize(&_NAME_);\
    com_github_airutech_cnets_mapBuffer_onKernels(&_NAME_);

typedef struct com_github_airutech_cnets_mapBuffer{
    arrayObject buffers;int64_t timeout_milisec;int32_t readers_grid_size;

  
/*[[[end]]] (checksum: ed075c1740359aaeae56144742361bcc)*/
  int                                       uniqueId;
  unsigned                                  *buffers_grid_ids;/*required for storing ids of writers*/
  int                                       *buffers_to_read;
  pthread_spinlock_t                        *buffers_to_read_lock;
  com_github_airutech_cnets_queue           free_buffers;/*only one queue actually*/
  com_github_airutech_cnets_queue           *grid;
  pthread_spinlock_t                        *grid_mutex;  

  pthread_mutex_t     switch_cv_ow_mutex;
  pthread_mutex_t     switch_cv_mutex;
  pthread_cond_t      switch_cv;
  pthread_mutex_t     free_buffers_cv_ow_mutex;
  pthread_mutex_t     free_buffers_cv_mutex;
  pthread_cond_t      free_buffers_cv;
  pthread_rwlock_t    rwLock;
  linkedContainer     *selectorContainers;
}com_github_airutech_cnets_mapBuffer;

/*USER DEFINED INITIALIZATION: Initialization of arrays dependent on buffers.length, and readers_grid_size*/
#undef com_github_airutech_cnets_mapBuffer_onCreateMacro
#define com_github_airutech_cnets_mapBuffer_onCreateMacro(_NAME_)\
    /* _buffers_grid_ids_ */\
    unsigned _NAME_##_buffers_grid_ids_[_NAME_.buffers.length]; \
    _NAME_.buffers_grid_ids = _NAME_##_buffers_grid_ids_; \
    /* _buffers_to_read_ */\
    int _NAME_##_buffers_to_read_[_NAME_.buffers.length]; \
    _NAME_.buffers_to_read = _NAME_##_buffers_to_read_; \
    /* _buffers_to_read_lock_ */\
    pthread_spinlock_t _NAME_##_buffers_to_read_lock_[_NAME_.buffers.length]; \
    _NAME_.buffers_to_read_lock = _NAME_##_buffers_to_read_lock_; \
    /* _grid_ */\
    com_github_airutech_cnets_queue_createGrid(_NAME_##_grid_, _NAME_.readers_grid_size, _NAME_.buffers.length)\
    _NAME_.grid = _NAME_##_grid_; \
    /* _grid_mutex_ */\
    pthread_spinlock_t _NAME_##_grid_mutex_[_NAME_.readers_grid_size]; \
    _NAME_.grid_mutex = _NAME_##_grid_mutex_;\
    /* _free_buffers_ */\
    com_github_airutech_cnets_queue_create(_NAME_##_free_buffers_,_NAME_.buffers.length)\
    _NAME_.free_buffers = _NAME_##_free_buffers_;


#endif /* com_github_airutech_cnets_mapBuffer_H */