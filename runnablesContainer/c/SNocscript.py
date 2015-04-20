
from helper import *
#           Environment
Import( 'env' )

def add_dependencies(env):
  '''[[[cog
  import cogging as c
  c.tpl(cog,templateFile,c.a(prefix=configFile))
  ]]]'''

  AddDependency(env,'com_github_osblinnikov_cnets_types','github.com/osblinnikov/cnets/types/c')
  '''[[[end]]] (checksum: 30bde1195b17873988c98dec85e34f78) (fadfcc0286d5ede2436d06ea30ca4283)'''
  AddPthreads(env)
  # AddNetwork(env) 

c = {}
c['PROG_NAME'] = 'com_github_osblinnikov_cnets_runnablesContainer'
c['sourceFiles'] = ['runnablesContainer.c','Kernel.c']
c['testFiles'] = ['runnablesContainerTest.c']
c['runFiles'] = ['main.c']
c['defines'] = []
c['inclDeps'] = add_dependencies
DefaultLibraryConfig(env, c)