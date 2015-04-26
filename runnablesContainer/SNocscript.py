from helper import *
#           Environment
Import( 'env' )

def add_dependencies(env):
  '''[[[cog
  import cogging as c
  c.tpl(cog,templateFile,c.a(prefix=configFile))
  ]]]'''

  AddDependency(env,'types_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/types')
  '''[[[end]]] (checksum: e8208f4ef21ca5bbecb9c806b80170a9)'''
  AddPthreads(env)
  # AddNetwork(env) 

c = {}
c['PROG_NAME'] = 'runnablesContainer_cnets_osblinnikov_github_com'
# c['sourceFiles'] = ['runnablesContainer.c']
c['testFiles'] = ['runnablesContainerTest.c']
# c['runFiles'] = ['main.c']
# c['defines'] = []
c['inclDeps'] = add_dependencies
DefaultLibraryConfig(env, c)