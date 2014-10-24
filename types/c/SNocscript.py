
from helper import *
#           Environment
Import( 'env', 'args' )

def add_dependencies(env, args):
  '''[[[cog
  import cogging as c
  c.tpl(cog,templateFile,c.a(prefix=configFile))
  ]]]'''

  '''[[[end]]] (checksum: 68b329da9893e34099c7d8ad5cb9c940)'''
  AddPthreads(env, args)
  # AddNetwork(args)

c = {}
c['PROG_NAME'] = 'com_github_airutech_cnets_types'
c['sourceFiles'] = ['types.c','timeUtils.c']
c['testFiles'] = ['typesTest.c']
c['runFiles'] = ['main.c']
c['defines'] = []
c['inclDepsDynamic'] = add_dependencies
c['inclDepsStatic'] = add_dependencies
DefaultLibraryConfig(c, env, args)