
cmake_minimum_required(VERSION 2.8)
project(dispatcher_dispatchKernel_cnets_osblinnikov_github_com C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(.)

function(addDeps buildType dstBuildType)
# [[[cog
# import cogging as c
# c.tpl(cog,templateFile,c.a(prefix=configFile))
# ]]]

include_directories(../../../../../)
add_dependencies(dispatcher_dispatchKernel_cnets_osblinnikov_github_com${buildType} runnablesContainer_cnets_osblinnikov_github_com${dstBuildType})
target_link_libraries(dispatcher_dispatchKernel_cnets_osblinnikov_github_com${buildType} runnablesContainer_cnets_osblinnikov_github_com${dstBuildType})
add_dependencies(dispatcher_dispatchKernel_cnets_osblinnikov_github_com${buildType} readerWriter_cnets_osblinnikov_github_com${dstBuildType})
target_link_libraries(dispatcher_dispatchKernel_cnets_osblinnikov_github_com${buildType} readerWriter_cnets_osblinnikov_github_com${dstBuildType})
add_dependencies(dispatcher_dispatchKernel_cnets_osblinnikov_github_com${buildType} types_cnets_osblinnikov_github_com${dstBuildType})
target_link_libraries(dispatcher_dispatchKernel_cnets_osblinnikov_github_com${buildType} types_cnets_osblinnikov_github_com${dstBuildType})
add_dependencies(dispatcher_dispatchKernel_cnets_osblinnikov_github_com${buildType} vector_cnets_osblinnikov_github_com${dstBuildType})
target_link_libraries(dispatcher_dispatchKernel_cnets_osblinnikov_github_com${buildType} vector_cnets_osblinnikov_github_com${dstBuildType})
# [[[end]]] (checksum: 07e73e2bdbbd651bfa81e2e89267dab9)
endfunction(addDeps)

file(GLOB DISPATCHER_DISPATCHKERNEL_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS "*.h")

set (DISPATCHER_DISPATCHKERNEL_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS
    src/dispatcher.c
    )
set(DISPATCHER_DISPATCHKERNEL_CNETS_OSBLINNIKOV_GITHUB_COM_TEST
    tests/dispatcherTest.c
    )

add_custom_target(dispatcher_dispatchKernel_cnets_osblinnikov_github_com)

if (NOT BUILD_STATIC_ONLY)
    add_library(dispatcher_dispatchKernel_cnets_osblinnikov_github_com_shared SHARED ${DISPATCHER_DISPATCHKERNEL_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS} ${DISPATCHER_DISPATCHKERNEL_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS})
    add_dependencies(dispatcher_dispatchKernel_cnets_osblinnikov_github_com_shared dispatcher_dispatchKernel_cnets_osblinnikov_github_com)
    target_link_libraries(dispatcher_dispatchKernel_cnets_osblinnikov_github_com_shared ${LD_FLAGS} )
    addDeps(_shared _shared)
    if(NOT WIN32)
        install(TARGETS dispatcher_dispatchKernel_cnets_osblinnikov_github_com_shared LIBRARY DESTINATION lib)
    endif()

    add_executable(dispatcher_dispatchKernel_cnets_osblinnikov_github_com_test_shared ${DISPATCHER_DISPATCHKERNEL_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(dispatcher_dispatchKernel_cnets_osblinnikov_github_com_test_shared dispatcher_dispatchKernel_cnets_osblinnikov_github_com_shared)
    target_link_libraries(dispatcher_dispatchKernel_cnets_osblinnikov_github_com_test_shared
                          ${LD_FLAGS}
                          dispatcher_dispatchKernel_cnets_osblinnikov_github_com_shared)
    addDeps(_test_shared _shared)
endif ()

if (BUILD_STATIC_ONLY OR BUILD_STATIC)
    add_library(dispatcher_dispatchKernel_cnets_osblinnikov_github_com_static STATIC ${DISPATCHER_DISPATCHKERNEL_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS} ${DISPATCHER_DISPATCHKERNEL_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS})
    add_dependencies(dispatcher_dispatchKernel_cnets_osblinnikov_github_com_static dispatcher_dispatchKernel_cnets_osblinnikov_github_com)
    addDeps(_static _static)
    if(NOT WIN32)
        install(TARGETS dispatcher_dispatchKernel_cnets_osblinnikov_github_com_static ARCHIVE DESTINATION lib)
    endif()

    add_executable(dispatcher_dispatchKernel_cnets_osblinnikov_github_com_test_static ${DISPATCHER_DISPATCHKERNEL_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(dispatcher_dispatchKernel_cnets_osblinnikov_github_com_test_static dispatcher_dispatchKernel_cnets_osblinnikov_github_com_static)
    target_link_libraries(dispatcher_dispatchKernel_cnets_osblinnikov_github_com_test_static
                            ${LD_FLAGS}
                            dispatcher_dispatchKernel_cnets_osblinnikov_github_com_static)
    addDeps(_test_static _static)
endif ()



link_directories(${LD_DIRS})
include_directories(. ${INCLUDE_DIRS})

# install includes
if(NOT WIN32)
  install(DIRECTORY / DESTINATION include/ FILES_MATCHING PATTERN "*.h")
  install(DIRECTORY / DESTINATION include/ FILES_MATCHING PATTERN "*.h")
endif()



