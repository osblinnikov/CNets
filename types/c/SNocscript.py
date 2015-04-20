
from helper import *
#           Environment
Import( 'env' )

def add_dependencies(env):
  '''[[[cog
  import cogging as c
  c.tpl(cog,templateFile,c.a(prefix=configFile))
  ]]]'''

  '''[[[end]]] (checksum: 68b329da9893e34099c7d8ad5cb9c940) (68b329da9893e34099c7d8ad5cb9c940)'''
  AddPthreads(env)
  # AddNetwork(env)

c = {}
c['PROG_NAME'] = 'com_github_osblinnikov_cnets_types'
c['sourceFiles'] = ['types.c','timeUtils.c']
c['testFiles'] = ['typesTest.c']
c['runFiles'] = ['main.c']
c['defines'] = []
c['inclDeps'] = add_dependencies
DefaultLibraryConfig(env,c)