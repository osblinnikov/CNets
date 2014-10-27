

#ifndef com_github_airutech_cnets_selector_H
#define com_github_airutech_cnets_selector_H

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/airutech/cnets/types/c/include/types.h"
#include "github.com/airutech/cnets/readerWriter/c/include/readerWriter.h"
#include "github.com/airutech/cnets/queue/c/include/queue.h"
#include "github.com/airutech/cnets/mapBuffer/c/include/mapBuffer.h"
#include "github.com/airutech/cnets/runnablesContainer/c/include/runnablesContainer.h"

#undef com_github_airutech_cnets_selector_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(com_github_airutech_cnets_selector_STATIC)
  #ifdef com_github_airutech_cnets_selector_EXPORT
    #define com_github_airutech_cnets_selector_EXPORT_API __declspec(dllexport)
  #else
    #define com_github_airutech_cnets_selector_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define com_github_airutech_cnets_selector_EXPORT_API extern
#endif

struct com_github_airutech_cnets_selector;

com_github_airutech_cnets_selector_EXPORT_API
reader com_github_airutech_cnets_selector_getReader(struct com_github_airutech_cnets_selector *that, void* container, int grid_id);

com_github_airutech_cnets_selector_EXPORT_API
writer com_github_airutech_cnets_selector_getWriter(struct com_github_airutech_cnets_selector *that, void* container, int grid_id);

com_github_airutech_cnets_selector_EXPORT_API
void com_github_airutech_cnets_selector_initialize(struct com_github_airutech_cnets_selector *that);

com_github_airutech_cnets_selector_EXPORT_API
void com_github_airutech_cnets_selector_deinitialize(struct com_github_airutech_cnets_selector *that);

com_github_airutech_cnets_selector_EXPORT_API
void com_github_airutech_cnets_selector_onKernels(struct com_github_airutech_cnets_selector *that);

#undef com_github_airutech_cnets_selector_onCreateMacro
#define com_github_airutech_cnets_selector_onCreateMacro(_NAME_) /**/


typedef struct com_github_airutech_cnets_selector_container{
  int bufferId;
}com_github_airutech_cnets_selector_container;
#define com_github_airutech_cnets_selector_createReader(_NAME_,_that,_grid_id,_bufferId)\
  com_github_airutech_cnets_selector_container _NAME_##_container;\
  _NAME_##_container.bufferId = _bufferId;\
  reader _NAME_ = com_github_airutech_cnets_selector_getReader(_that,(void*)&_NAME_##_container,_grid_id);

#define com_github_airutech_cnets_selector_createWriter(_NAME_,_that,_grid_id,_bufferId)\
  com_github_airutech_cnets_selector_container _NAME_##_container;\
  _NAME_##_container.bufferId = _bufferId;\
  writer _NAME_ = com_github_airutech_cnets_selector_getWriter(_that,(void*)&_NAME_##_container,_grid_id);

#define com_github_airutech_cnets_selector_create(_NAME_,_reducableReaders)\
    com_github_airutech_cnets_selector _NAME_;\
    _NAME_.reducableReaders = _reducableReaders;\
    com_github_airutech_cnets_selector_onCreateMacro(_NAME_)\
    com_github_airutech_cnets_selector_initialize(&_NAME_);\
    com_github_airutech_cnets_selector_onKernels(&_NAME_);

typedef struct com_github_airutech_cnets_selector{
    arrayObject reducableReaders;

  
/*[[[end]]] (checksum: 286e3f59d9166659d7a061caf7f664dc) */
    linkedContainer *allContainers;
    unsigned        *writesToContainers;
    unsigned        timeout_milisec;
    int             lastReadId;
    int             sumWrites;
    pthread_mutex_t switch_cv_lock;
    pthread_cond_t  switch_cv;
}com_github_airutech_cnets_selector;

#undef com_github_airutech_cnets_selector_onCreateMacro
#define com_github_airutech_cnets_selector_onCreateMacro(_NAME_)\
    /* _allContainers_ */\
    linkedContainer _NAME_##_allContainers_[_NAME_.reducableReaders.length]; \
    _NAME_.allContainers = _NAME_##_allContainers_;\
    /* _writesToContainers_ */\
    unsigned _NAME_##_writesToContainers_[_NAME_.reducableReaders.length]; \
    _NAME_.writesToContainers = _NAME_##_writesToContainers_;

#endif /* com_github_airutech_cnets_selector_H */