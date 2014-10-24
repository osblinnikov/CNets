
/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../include/types.h"
/*[[[end]]] (checksum: a0c5a836da34300827b8973b4fbfaa12)*/
int main(int argc, char* argv[]){
  com_github_airutech_cnets_types_create(classObj);
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
  return 0;
}