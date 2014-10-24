
from helper import *
#           Environment
Import( 'env', 'args' )

def add_dependencies(env, args):
  '''[[[cog
  import cogging as c
  c.tpl(cog,templateFile,c.a(prefix=configFile))
  ]]]'''

  AddDependency(args,'com_github_airutech_cnets_types',join(args['PROJECTS_ROOT_PATH'],'src/github.com/airutech/cnets/types/c'))
  AddDependency(args,'com_github_airutech_cnets_readerWriter',join(args['PROJECTS_ROOT_PATH'],'src/github.com/airutech/cnets/readerWriter/c'))
  AddDependency(args,'com_github_airutech_cnets_queue',join(args['PROJECTS_ROOT_PATH'],'src/github.com/airutech/cnets/queue/c'))
  AddDependency(args,'com_github_airutech_cnets_mapBuffer',join(args['PROJECTS_ROOT_PATH'],'src/github.com/airutech/cnets/mapBuffer/c'))
  AddDependency(args,'com_github_airutech_cnets_runnablesContainer',join(args['PROJECTS_ROOT_PATH'],'src/github.com/airutech/cnets/runnablesContainer/c'))
  '''[[[end]]] (checksum: 512eb8bcfea6d0e55d8e44d7fc61b2ea)'''
  # AddPthreads(env, args)
  # AddNetwork(args) 

c = {}
c['PROG_NAME'] = 'com_github_airutech_cnets_selector'
c['sourceFiles'] = ['selector.c']
c['testFiles'] = ['selectorTest.c']
c['runFiles'] = ['main.c']
c['defines'] = []
c['inclDepsDynamic'] = add_dependencies
c['inclDepsStatic'] = add_dependencies
DefaultLibraryConfig(c, env, args)