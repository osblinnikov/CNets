#include "../dispatcherCollector.h"

#include <stdio.h>

static short initialized = 0;
static struct vector_cnets_osblinnikov_github_com vec;
static unsigned localId = 0, startLocalId = 0;

void dispatcherCollector_deinit(){
  if(initialized){
    for(size_t i = 0; i<vector_cnets_osblinnikov_github_com_total(&vec); i++){
      free(vec.items[i]);
    }
    vector_cnets_osblinnikov_github_com_deinit(&vec);
    initialized = 0;
    localId = 0;
    startLocalId = 0;
  }
}

void dispatcherCollector_init(){
  if(!initialized){
    initialized = 1;
    vector_cnets_osblinnikov_github_com_init(&vec);
    writer* w = (writer*)malloc(sizeof(writer));
    *w = writer;
    w->params.target = NULL;
    vector_cnets_osblinnikov_github_com_add(&vec, (void*)w);
  }
}

void dispatcherCollector_addWriter(writer wIn){
  if(!initialized){
    fprintf(stderr, "ERROR: dispatcherCollector_addWriter: dispatcherCollector was not initialized yet for some reason!\n");
    dispatcherCollector_init();
  }else{
    writer* w = (writer*)vector_cnets_osblinnikov_github_com_get(&vec, vector_cnets_osblinnikov_github_com_total(&vec) - 1);
    *w = wIn;/*set writer for the previously created kernels*/

    writer* w1 = (writer*)malloc(sizeof(writer));
    *w1 = writer;
    w1->params.target = NULL;
    vector_cnets_osblinnikov_github_com_add(&vec, w1);
  }
}

struct writer *dispatcherCollector_getWriter(){
  if(!initialized){
    dispatcherCollector_init();
  }
  return (writer*)vector_cnets_osblinnikov_github_com_get(&vec, vector_cnets_osblinnikov_github_com_total(&vec) - 1);
}

void dispatcherCollector_tagAsStartLocalId(){
  startLocalId = localId;
}

unsigned dispatcherCollector_getStartLocalId(){
  return startLocalId;
}

unsigned dispatcherCollector_getLocalId(){
  if(localId > 0){
    return localId - 1;
  }else{
    return 0;
  }
}

unsigned dispatcherCollector_getNextLocalId(){
  return localId++;
}
