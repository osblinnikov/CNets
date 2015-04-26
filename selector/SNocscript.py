from helper import *
#           Environment
Import( 'env' )

def add_dependencies(env):
  '''[[[cog
  import cogging as c
  c.tpl(cog,templateFile,c.a(prefix=configFile))
  ]]]'''

  AddDependency(env,'mapBuffer_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/mapBuffer')
  AddDependency(env,'readerWriter_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/readerWriter')
  AddDependency(env,'queue_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/queue')
  AddDependency(env,'runnablesContainer_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/runnablesContainer')
  AddDependency(env,'types_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/types')
  '''[[[end]]] (checksum: fcc8e8ea2a34f6a86238b04cdc2437ef)'''
  AddPthreads(env)
  # AddNetwork(env) 

c = {}
c['PROG_NAME'] = 'selector_cnets_osblinnikov_github_com'
# c['sourceFiles'] = ['selector.c']
c['testFiles'] = ['selectorTest.c']
# c['runFiles'] = ['main.c']
# c['defines'] = []
c['inclDeps'] = add_dependencies
DefaultLibraryConfig(env, c)