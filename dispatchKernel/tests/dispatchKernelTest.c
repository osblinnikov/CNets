/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../dispatchKernel.h"
/*[[[end]]] (checksum: 9802c1912c224094e97f11a61b27f6d3)*/
int main(int argc, char* argv[]){
  dispatchKernel_cnets_osblinnikov_github_com classObj;
  dispatchKernel_cnets_osblinnikov_github_com_init(&classObj,arrayObjectNULL(),0,0);
    runnablesContainer_cnets_osblinnikov_github_com runnables = classObj.getRunnables(&classObj);
    runnables.launch(&runnables,FALSE);
    runnables.stop(&runnables);
    dispatchKernel_cnets_osblinnikov_github_com_deinit(&classObj);
  return 0;
}