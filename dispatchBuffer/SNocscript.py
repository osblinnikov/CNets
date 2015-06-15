from helper import *
#           Environment
Import( 'env' )

def add_dependencies(env):
  '''[[[cog
  import cogging as c
  c.tpl(cog,templateFile,c.a(prefix=configFile))
  ]]]'''

  AddDependency(env,'readerWriter_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/readerWriter')
  AddDependency(env,'types_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/types')
  AddDependency(env,'vector_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/vector')
  '''[[[end]]] (checksum: ada1515415dbb26d393cbc8a50b93acf)'''
  AddPthreads(env)
  # AddNetwork(env) 

c = {}
c['PROG_NAME'] = 'dispatchBuffer_cnets_osblinnikov_github_com'
# c['sourceFiles'] = ['dispatchBuffer.c']
c['testFiles'] = ['dispatchBufferTest.c']
# c['runFiles'] = ['main.c']
# c['defines'] = []
c['inclDeps'] = add_dependencies
DefaultLibraryConfig(env, c)