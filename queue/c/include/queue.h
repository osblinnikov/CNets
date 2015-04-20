

#ifndef com_github_osblinnikov_cnets_queue_H
#define com_github_osblinnikov_cnets_queue_H

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/types/c/include/types.h"

#undef com_github_osblinnikov_cnets_queue_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(COM_GITHUB_OSBLINNIKOV_CNETS_QUEUE_STATIC)
  #ifdef com_github_osblinnikov_cnets_queue_EXPORT
    #define com_github_osblinnikov_cnets_queue_EXPORT_API __declspec(dllexport)
  #else
    #define com_github_osblinnikov_cnets_queue_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define com_github_osblinnikov_cnets_queue_EXPORT_API extern
#endif

struct com_github_osblinnikov_cnets_queue;

com_github_osblinnikov_cnets_queue_EXPORT_API
void com_github_osblinnikov_cnets_queue_initialize(struct com_github_osblinnikov_cnets_queue *that);

com_github_osblinnikov_cnets_queue_EXPORT_API
void com_github_osblinnikov_cnets_queue_deinitialize(struct com_github_osblinnikov_cnets_queue *that);

com_github_osblinnikov_cnets_queue_EXPORT_API
void com_github_osblinnikov_cnets_queue_onKernels(struct com_github_osblinnikov_cnets_queue *that);

#undef com_github_osblinnikov_cnets_queue_onCreateMacro
#define com_github_osblinnikov_cnets_queue_onCreateMacro(_NAME_) /**/

#define com_github_osblinnikov_cnets_queue_create(_NAME_,_capacity)\
    com_github_osblinnikov_cnets_queue _NAME_;\
    _NAME_.capacity = _capacity;\
    com_github_osblinnikov_cnets_queue_onCreateMacro(_NAME_)\
    arrayObject_create(_NAME_##_data_, uint32_t, _capacity)\
    _NAME_.data = _NAME_##_data_;\
    com_github_osblinnikov_cnets_queue_initialize(&_NAME_);\
    com_github_osblinnikov_cnets_queue_onKernels(&_NAME_);

typedef struct com_github_osblinnikov_cnets_queue{
    int32_t capacity;arrayObject data;uint32_t maxIndex;uint32_t head;uint32_t tail;

  
  void (*run)(void *that);
/*[[[end]]] (checksum: 44e86ef956d6845c54a3e28106fe74ec) (9943437232b3695222991abeee961a0d)*/
  BOOL (*isEmpty)(struct com_github_osblinnikov_cnets_queue *that);
  BOOL (*isFull)(struct com_github_osblinnikov_cnets_queue *that);
  BOOL (*dequeue)(struct com_github_osblinnikov_cnets_queue *that,uint32_t *obj);
  BOOL (*enqueue)(struct com_github_osblinnikov_cnets_queue *that,uint32_t obj);
  uint32_t (*length)(struct com_github_osblinnikov_cnets_queue *that);
  void (*clear)(struct com_github_osblinnikov_cnets_queue *that);
}com_github_osblinnikov_cnets_queue;


#define com_github_osblinnikov_cnets_queue_createGrid(_NAME_,_count,_capacity)\
  com_github_osblinnikov_cnets_queue* _NAME_ = (com_github_osblinnikov_cnets_queue*)salloca(sizeof(com_github_osblinnikov_cnets_queue)*_count);\
  arrayObject_create(_NAME_##_data_, uint32_t, _count*_capacity)\
  int _NAME_##i;\
  for(_NAME_##i=0;_NAME_##i<_count;_NAME_##i++){\
    _NAME_[_NAME_##i].capacity = _capacity;\
    _NAME_[_NAME_##i].data.array = (void*)&((uint32_t*)_NAME_##_data_.array)[_capacity * _NAME_##i];\
    _NAME_[_NAME_##i].data.length = _capacity;\
    _NAME_[_NAME_##i].data.itemSize = sizeof(uint32_t);\
    com_github_osblinnikov_cnets_queue_initialize(&_NAME_[_NAME_##i]);\
    com_github_osblinnikov_cnets_queue_onKernels(&_NAME_[_NAME_##i]);\
  }


#endif /* com_github_osblinnikov_cnets_queue_H */