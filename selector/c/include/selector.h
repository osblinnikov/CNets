

#ifndef com_github_osblinnikov_cnets_selector_H
#define com_github_osblinnikov_cnets_selector_H

/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "github.com/osblinnikov/cnets/types/c/include/types.h"
#include "github.com/osblinnikov/cnets/readerWriter/c/include/readerWriter.h"
#include "github.com/osblinnikov/cnets/queue/c/include/queue.h"
#include "github.com/osblinnikov/cnets/mapBuffer/c/include/mapBuffer.h"
#include "github.com/osblinnikov/cnets/runnablesContainer/c/include/runnablesContainer.h"

#undef com_github_osblinnikov_cnets_selector_EXPORT_API
#if defined WIN32 && !defined __MINGW32__ && !defined(CYGWIN) && !defined(COM_GITHUB_OSBLINNIKOV_CNETS_SELECTOR_STATIC)
  #ifdef com_github_osblinnikov_cnets_selector_EXPORT
    #define com_github_osblinnikov_cnets_selector_EXPORT_API __declspec(dllexport)
  #else
    #define com_github_osblinnikov_cnets_selector_EXPORT_API __declspec(dllimport)
  #endif
#else
  #define com_github_osblinnikov_cnets_selector_EXPORT_API extern
#endif

struct com_github_osblinnikov_cnets_selector;

com_github_osblinnikov_cnets_selector_EXPORT_API
void com_github_osblinnikov_cnets_selector_init(struct com_github_osblinnikov_cnets_selector *that,
    reader[] _reducableReaders);

com_github_osblinnikov_cnets_selector_EXPORT_API
void com_github_osblinnikov_cnets_selector_deinit(struct com_github_osblinnikov_cnets_selector *that);

com_github_osblinnikov_cnets_selector_EXPORT_API
reader com_github_osblinnikov_cnets_selector_createReader(struct com_github_osblinnikov_cnets_selector *that, int gridId);

com_github_osblinnikov_cnets_selector_EXPORT_API
writer com_github_osblinnikov_cnets_selector_createWriter(struct com_github_osblinnikov_cnets_selector *that, int gridId);



typedef struct com_github_osblinnikov_cnets_selector{
    arrayObject reducableReaders;

  
/*[[[end]]] (checksum: 2835b78274aaf433310984e04193101f) (cf5327bc5122e80aa72c0a66351ce661) */
    linkedContainer *allContainers;
    uint32_t        *writesToContainers;
    int64_t         timeout_milisec;
    int32_t         lastReadId;
    int32_t         sumWrites;
    pthread_mutex_t switch_cv_lock;
    pthread_cond_t  switch_cv;
}com_github_osblinnikov_cnets_selector;

#endif /* com_github_osblinnikov_cnets_selector_H */