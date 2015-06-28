/*[[[cog
import cogging as c
c.tpl(cog,templateFile,c.a(prefix=configFile))
]]]*/

#include "../topology.h"
/*[[[end]]] (checksum: 735e28961f7ca3f1ecbe223fdb9ff041)*/
int main(int argc, char* argv[]){
  topology_replicator_cnets_osblinnikov_github_com classObj;
  topology_replicator_cnets_osblinnikov_github_com_init(&classObj,arrayObjectNULL(),0,0,arrayObjectNULL());
    runnablesContainer_cnets_osblinnikov_github_com runnables = classObj.getRunnables(&classObj);
    runnables.launch(&runnables,FALSE);
    runnables.stop(&runnables);
    topology_replicator_cnets_osblinnikov_github_com_deinit(&classObj);
  return 0;
}