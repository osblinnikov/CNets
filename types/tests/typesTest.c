
/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../types.h"
/*[[[end]]] (checksum: 438fa6bd312d31006a24014a265f6a96)*/

#include <string.h>

//typedef struct toSerialize{
//  int i,j,k;
//  arrayObject arr;
//  char* string;
//}toSerialize;

//int serializeNext(struct serializator_types_cnets_osblinnikov_github_com *that, arrayObject to){
//  return 0;
//}

//int deserializeNext(struct serializator_types_cnets_osblinnikov_github_com *that, arrayObject from){
//  return 0;
//}

//int serializator_test(){
//  printf("-- CNets: SerializatorTest ---\n");
//  toSerialize from, to;
//  from.string = (char*)"test";
//  from.arr = arrayObject_init_dynamic(4, 4);
//  serializator_types_cnets_osblinnikov_github_com serializator;
//  serializator_types_cnets_osblinnikov_github_com_init(&serializator,serializeNext,(void*)&from);

//  serializator_types_cnets_osblinnikov_github_com deserializator;
//  serializator_types_cnets_osblinnikov_github_com_init(&deserializator,deserializeNext,(void*)&to);

//  arrayObject transport = arrayObject_init_dynamic(sizeof(int),10);

//  serializator.next(&serializator, transport);

//  deserializator.next(&deserializator, transport);

//  if(to.i != from.i
//     || to.j != from.j
//     || to.k != from.k
//     || to.arr.length != from.arr.length
//     || to.arr.itemSize != from.arr.itemSize
//     || strlen(to.string) != strlen(from.string)){
//    fprintf(stderr,"something was not serializaed/deserialized correctly\n");
//    return -1;
//  }

//  arrayObject_free_dynamic(from.arr);
//  arrayObject_free_dynamic(transport);

//  printf("-- CNets: SerializatorTest OK ---\n");
//  return 0;
//}

int main(int argc, char* argv[]){
  // types_cnets_osblinnikov_github_com_create(classObj);
  printf("-- CNets: Time Utils Tests: Test Delay ---\n");
  int i;
  uint64_t lastTime = curTimeMilisec();
  for(i=0; i<2; i++){
    taskDelay(1000000000L);
    uint64_t curtime = curTimeMilisec();
    uint32_t curtime_sec = (uint32_t)(curtime/(uint64_t)1000L);
    printf("%d %d\n",curtime_sec, (uint32_t)(curtime - lastTime));
    lastTime = curtime;
  }
  printf("-- CNets: Time Utils Tests Ending---\n");
//  if(serializator_test()!=0){
//    return -1;
//  }
  return 0;
}
