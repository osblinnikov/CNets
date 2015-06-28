
cmake_minimum_required(VERSION 2.8)
project(topology_replicator_cnets_osblinnikov_github_com C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(.)

function(addDeps buildType dstBuildType)
# [[[cog
# import cogging as c
# c.tpl(cog,templateFile,c.a(prefix=configFile))
# ]]]

  include_directories(../../../../../)
  add_dependencies(topology_replicator_cnets_osblinnikov_github_com${buildType} dispatchKernel_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(topology_replicator_cnets_osblinnikov_github_com${buildType} dispatchKernel_cnets_osblinnikov_github_com${dstBuildType})
  add_dependencies(topology_replicator_cnets_osblinnikov_github_com${buildType} selector_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(topology_replicator_cnets_osblinnikov_github_com${buildType} selector_cnets_osblinnikov_github_com${dstBuildType})
  add_dependencies(topology_replicator_cnets_osblinnikov_github_com${buildType} runnablesContainer_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(topology_replicator_cnets_osblinnikov_github_com${buildType} runnablesContainer_cnets_osblinnikov_github_com${dstBuildType})
  add_dependencies(topology_replicator_cnets_osblinnikov_github_com${buildType} mapBuffer_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(topology_replicator_cnets_osblinnikov_github_com${buildType} mapBuffer_cnets_osblinnikov_github_com${dstBuildType})
  add_dependencies(topology_replicator_cnets_osblinnikov_github_com${buildType} readerWriter_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(topology_replicator_cnets_osblinnikov_github_com${buildType} readerWriter_cnets_osblinnikov_github_com${dstBuildType})
  add_dependencies(topology_replicator_cnets_osblinnikov_github_com${buildType} queue_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(topology_replicator_cnets_osblinnikov_github_com${buildType} queue_cnets_osblinnikov_github_com${dstBuildType})
  add_dependencies(topology_replicator_cnets_osblinnikov_github_com${buildType} types_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(topology_replicator_cnets_osblinnikov_github_com${buildType} types_cnets_osblinnikov_github_com${dstBuildType})
  add_dependencies(topology_replicator_cnets_osblinnikov_github_com${buildType} vector_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(topology_replicator_cnets_osblinnikov_github_com${buildType} vector_cnets_osblinnikov_github_com${dstBuildType})

# install includes
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/replicator/topology FILES_MATCHING PATTERN "*.h" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/replicator/topology FILES_MATCHING PATTERN "*.hpp" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
# [[[end]]] (checksum: 97e645d539487ac1c348f4dcb8ed1d0e)
endfunction(addDeps)

file(GLOB TOPOLOGY_REPLICATOR_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS "*.h")

set (TOPOLOGY_REPLICATOR_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS
    src/topology.c
    )
set(TOPOLOGY_REPLICATOR_CNETS_OSBLINNIKOV_GITHUB_COM_TEST
    tests/topologyTest.c
    )

add_custom_target(topology_replicator_cnets_osblinnikov_github_com)

if (NOT BUILD_STATIC_ONLY)
    add_library(topology_replicator_cnets_osblinnikov_github_com_shared SHARED ${TOPOLOGY_REPLICATOR_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS} ${TOPOLOGY_REPLICATOR_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS})
    add_dependencies(topology_replicator_cnets_osblinnikov_github_com_shared topology_replicator_cnets_osblinnikov_github_com)
    target_link_libraries(topology_replicator_cnets_osblinnikov_github_com_shared ${LD_FLAGS} )
    addDeps(_shared _shared)
    if(NOT WIN32)
        install(TARGETS topology_replicator_cnets_osblinnikov_github_com_shared LIBRARY DESTINATION lib)
    endif()

    add_executable(topology_replicator_cnets_osblinnikov_github_com_test_shared ${TOPOLOGY_REPLICATOR_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(topology_replicator_cnets_osblinnikov_github_com_test_shared topology_replicator_cnets_osblinnikov_github_com_shared)
    target_link_libraries(topology_replicator_cnets_osblinnikov_github_com_test_shared
                          ${LD_FLAGS}
                          topology_replicator_cnets_osblinnikov_github_com_shared)
    addDeps(_test_shared _shared)
endif ()

if (BUILD_STATIC_ONLY OR BUILD_STATIC)
    add_library(topology_replicator_cnets_osblinnikov_github_com_static STATIC ${TOPOLOGY_REPLICATOR_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS} ${TOPOLOGY_REPLICATOR_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS})
    add_dependencies(topology_replicator_cnets_osblinnikov_github_com_static topology_replicator_cnets_osblinnikov_github_com)
    addDeps(_static _static)
    if(NOT WIN32)
        install(TARGETS topology_replicator_cnets_osblinnikov_github_com_static ARCHIVE DESTINATION lib)
    endif()

    add_executable(topology_replicator_cnets_osblinnikov_github_com_test_static ${TOPOLOGY_REPLICATOR_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(topology_replicator_cnets_osblinnikov_github_com_test_static topology_replicator_cnets_osblinnikov_github_com_static)
    target_link_libraries(topology_replicator_cnets_osblinnikov_github_com_test_static
                            ${LD_FLAGS}
                            topology_replicator_cnets_osblinnikov_github_com_static)
    addDeps(_test_static _static)
endif ()



link_directories(${LD_DIRS})
include_directories(. ${INCLUDE_DIRS})



