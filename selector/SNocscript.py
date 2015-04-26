
from helper import *
#           Environment
Import( 'env' )

def add_dependencies(env):
  '''[[[cog
  import cogging as c
  c.tpl(cog,templateFile,c.a(prefix=configFile))
  ]]]'''

  AddDependency(env,'com_github_osblinnikov_cnets_types','github.com/osblinnikov/cnets/types')
  AddDependency(env,'com_github_osblinnikov_cnets_readerWriter','github.com/osblinnikov/cnets/readerWriter')
  AddDependency(env,'com_github_osblinnikov_cnets_queue','github.com/osblinnikov/cnets/queue')
  AddDependency(env,'com_github_osblinnikov_cnets_mapBuffer','github.com/osblinnikov/cnets/mapBuffer')
  AddDependency(env,'com_github_osblinnikov_cnets_runnablesContainer','github.com/osblinnikov/cnets/runnablesContainer')
  '''[[[end]]] (f8df05a95babf1d6c46ff46603042819) (512eb8bcfea6d0e55d8e44d7fc61b2ea)'''
  AddPthreads(env)
  # AddNetwork(env) 

c = {}
c['PROG_NAME'] = 'com_github_osblinnikov_cnets_selector'
c['sourceFiles'] = ['selector.c']
c['testFiles'] = ['selectorTest.c']
c['runFiles'] = ['main.c']
c['defines'] = []
c['inclDeps'] = add_dependencies
DefaultLibraryConfig(env, c)