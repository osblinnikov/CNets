
from helper import *
#           Environment
Import( 'env')

def add_dependencies(env):
  '''[[[cog
  import cogging as c
  c.tpl(cog,templateFile,c.a(prefix=configFile))
  ]]]'''

  AddDependency(env,'com_github_osblinnikov_cnets_types','github.com/osblinnikov/cnets/types')
  AddDependency(env,'com_github_osblinnikov_cnets_readerWriter','github.com/osblinnikov/cnets/readerWriter')
  AddDependency(env,'com_github_osblinnikov_cnets_queue','github.com/osblinnikov/cnets/queue')
  '''[[[end]]] (10043826d96a2528f442a5f4aad04124) (10043826d96a2528f442a5f4aad04124)'''
  AddPthreads(env)
  # AddNetwork(env) 

c = {}
c['PROG_NAME'] = 'com_github_osblinnikov_cnets_mapBuffer'
c['sourceFiles'] = ['mapBuffer.c']
c['testFiles'] = ['mapBufferTest.c']
c['runFiles'] = ['main.c']
c['inclDeps'] = add_dependencies
DefaultLibraryConfig(env, c)