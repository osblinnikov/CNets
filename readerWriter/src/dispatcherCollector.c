#include "../dispatcherCollector.h"

#include <stdio.h>

static short wrSet = 0;
static struct writer w;
static int localId = 0;

static pthread_mutex_t     localIdMutex = PTHREAD_MUTEX_INITIALIZER;

void dispatcherCollector_setWriter(writer wIn){
  if(wrSet == 0) {
    w = wIn;
    wrSet = 1;
  }else{
    printf("WARN: dispatcherCollector_setWriter: writer already set\n");
  }
}

struct writer dispatcherCollector_getWriter(){
  struct writer res;
  if(wrSet){
    res = w;
  }else{
    res.params.target = 0;
  }
  return res;
}

int dispatcherCollector_getNextLocalId(){
  pthread_mutex_lock(&localIdMutex);
  int res = localId++;
  pthread_mutex_unlock(&localIdMutex);
  return res;
}
