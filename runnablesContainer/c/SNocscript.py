
from helper import *
#           Environment
Import( 'env', 'args' )

def add_dependencies(env, args):
  '''[[[cog
  import cogging as c
  c.tpl(cog,templateFile,c.a(prefix=configFile))
  ]]]'''

  AddDependency(args,'com_github_airutech_cnets_types',join(args['PROJECTS_ROOT_PATH'],'src/github.com/airutech/cnets/types/c'))
  '''[[[end]]] (checksum: fadfcc0286d5ede2436d06ea30ca4283)'''
  AddPthreads(env, args)
  # AddNetwork(args) 

c = {}
c['PROG_NAME'] = 'com_github_airutech_cnets_runnablesContainer'
c['sourceFiles'] = ['runnablesContainer.c','Kernel.c']
c['testFiles'] = ['runnablesContainerTest.c']
c['runFiles'] = ['main.c']
c['defines'] = []
c['inclDepsDynamic'] = add_dependencies
c['inclDepsStatic'] = add_dependencies
DefaultLibraryConfig(c, env, args)