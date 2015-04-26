#include "../statsCollectorStatic.h"

#include <stdio.h>

short wrSet = 0;
struct writer w;
int localId = 0;
uint64_t statsInterval = 0;

pthread_rwlock_t    writerRwMutex = PTHREAD_RWLOCK_INITIALIZER;
pthread_mutex_t     localIdMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_rwlock_t    statsIntervalRwMutex = PTHREAD_RWLOCK_INITIALIZER;

void statsCollectorStatic_setWriter(writer wIn){
  pthread_rwlock_wrlock(&writerRwMutex);
  if(wrSet == 0) {
    w = wIn;
    wrSet = 1;
  }else{
    printf("WARN: statsCollectorStatic_setWriter: writer already set\n");
  }
  pthread_rwlock_unlock(&writerRwMutex);
}

struct writer statsCollectorStatic_getWriter(){
  struct writer res;
  res.params.target = 0;
  pthread_rwlock_rdlock(&writerRwMutex);
  if(wrSet){
    res = w;
  }
  pthread_rwlock_unlock(&writerRwMutex);
  return res;
}


void statsCollectorStatic_setStatsInterval(uint64_t i){
  pthread_rwlock_wrlock(&statsIntervalRwMutex);
  statsInterval = i;
  pthread_rwlock_unlock(&statsIntervalRwMutex);
}


uint64_t statsCollectorStatic_getStatsInterval() {
  pthread_rwlock_rdlock(&statsIntervalRwMutex);
  uint64_t res = statsInterval;
  pthread_rwlock_unlock(&statsIntervalRwMutex);
  return res;
}


int statsCollectorStatic_getNextLocalId(){
  pthread_mutex_lock(&localIdMutex);
  int res = localId++;
  pthread_mutex_unlock(&localIdMutex);
  return res;
}