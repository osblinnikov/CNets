from helper import *
#           Environment
Import( 'env' )

def add_dependencies(env):
  '''[[[cog
  import cogging as c
  c.tpl(cog,templateFile,c.a(prefix=configFile))
  ]]]'''

  AddDependency(env,'types_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/types')
  AddDependency(env,'readerWriter_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/readerWriter')
  AddDependency(env,'queue_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/queue')
  '''[[[end]]] (checksum: 37d856e3ef2f35e10842006d63160470)'''
  AddPthreads(env)
  # AddNetwork(env) 

c = {}
c['PROG_NAME'] = 'mapBuffer_cnets_osblinnikov_github_com'
# c['sourceFiles'] = ['mapBuffer.c']
c['testFiles'] = ['mapBufferTest.c']
# c['runFiles'] = ['main.c']
# c['defines'] = []
c['inclDeps'] = add_dependencies
DefaultLibraryConfig(env, c)