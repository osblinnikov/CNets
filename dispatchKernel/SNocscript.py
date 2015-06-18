from helper import *
#           Environment
Import( 'env' )

def add_dependencies(env):
  '''[[[cog
  import cogging as c
  c.tpl(cog,templateFile,c.a(prefix=configFile))
  ]]]'''

  AddDependency(env,'dispatcher_dispatchKernel_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/dispatchKernel/dispatcher')
  AddDependency(env,'runnablesContainer_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/runnablesContainer')
  AddDependency(env,'dispatchBuffer_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/dispatchBuffer')
  AddDependency(env,'readerWriter_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/readerWriter')
  AddDependency(env,'types_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/types')
  AddDependency(env,'vector_cnets_osblinnikov_github_com','github.com/osblinnikov/cnets/vector')
  '''[[[end]]] (checksum: 34cb0ed9878f0f7eeb2ffc9fd01982ab)'''
  AddPthreads(env)
  # AddNetwork(env) 

c = {}
c['PROG_NAME'] = 'dispatchKernel_cnets_osblinnikov_github_com'
# c['sourceFiles'] = ['dispatchKernel.c']
c['testFiles'] = ['dispatchKernelTest.c']
# c['runFiles'] = ['main.c']
# c['defines'] = []
c['inclDeps'] = add_dependencies
DefaultLibraryConfig(env, c)