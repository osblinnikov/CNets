/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../dispatcher.h"
/*[[[end]]] (checksum: caa2a76cb5aa91fe62347dc47efa1b0b)*/
int main(int argc, char* argv[]){
  dispatcher_dispatchKernel_cnets_osblinnikov_github_com classObj;
  dispatcher_dispatchKernel_cnets_osblinnikov_github_com_init(&classObj,arrayObjectNULL(),0,arrayObjectNULL());
    runnablesContainer_cnets_osblinnikov_github_com runnables = classObj.getRunnables(&classObj);
    runnables.launch(&runnables,FALSE);
    runnables.stop(&runnables);
    dispatcher_dispatchKernel_cnets_osblinnikov_github_com_deinit(&classObj);
  return 0;
}