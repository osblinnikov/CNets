
cmake_minimum_required(VERSION 2.8)
project(runnablesContainer_cnets_osblinnikov_github_com C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(.)

function(addDeps buildType dstBuildType)
# [[[cog
# import cogging as c
# c.tpl(cog,templateFile,c.a(prefix=configFile))
# ]]]

include_directories(../../../../)
add_dependencies(runnablesContainer_cnets_osblinnikov_github_com${buildType} types_cnets_osblinnikov_github_com${dstBuildType})
target_link_libraries(runnablesContainer_cnets_osblinnikov_github_com${buildType} types_cnets_osblinnikov_github_com${dstBuildType})
# [[[end]]] (checksum: e4100bf4dc9ab19b417198bc227a4927)
endfunction(addDeps)

file(GLOB RUNNABLESCONTAINER_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS "*.h")

set (RUNNABLESCONTAINER_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS
    src/runnablesContainer.c
    )
set(RUNNABLESCONTAINER_CNETS_OSBLINNIKOV_GITHUB_COM_TEST
    tests/runnablesContainerTest.c
    )

add_custom_target(runnablesContainer_cnets_osblinnikov_github_com)

if (NOT BUILD_STATIC_ONLY)
    add_library(runnablesContainer_cnets_osblinnikov_github_com_shared SHARED ${RUNNABLESCONTAINER_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS} ${RUNNABLESCONTAINER_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS})
    add_dependencies(runnablesContainer_cnets_osblinnikov_github_com_shared runnablesContainer_cnets_osblinnikov_github_com)
    target_link_libraries(runnablesContainer_cnets_osblinnikov_github_com_shared ${LD_FLAGS} )
    addDeps(_shared _shared)
    if(NOT WIN32)
        install(TARGETS runnablesContainer_cnets_osblinnikov_github_com_shared LIBRARY DESTINATION lib)
    endif()

    add_executable(runnablesContainer_cnets_osblinnikov_github_com_test_shared ${RUNNABLESCONTAINER_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(runnablesContainer_cnets_osblinnikov_github_com_test_shared runnablesContainer_cnets_osblinnikov_github_com_shared)
    target_link_libraries(runnablesContainer_cnets_osblinnikov_github_com_test_shared
                          ${LD_FLAGS}
                          runnablesContainer_cnets_osblinnikov_github_com_shared)
    addDeps(_test_shared _shared)
endif ()

if (BUILD_STATIC_ONLY OR BUILD_STATIC)
    add_library(runnablesContainer_cnets_osblinnikov_github_com_static STATIC ${RUNNABLESCONTAINER_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS} ${RUNNABLESCONTAINER_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS})
    add_dependencies(runnablesContainer_cnets_osblinnikov_github_com_static runnablesContainer_cnets_osblinnikov_github_com)
    addDeps(_static _static)
    if(NOT WIN32)
        install(TARGETS runnablesContainer_cnets_osblinnikov_github_com_static ARCHIVE DESTINATION lib)
    endif()

    add_executable(runnablesContainer_cnets_osblinnikov_github_com_test_static ${RUNNABLESCONTAINER_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(runnablesContainer_cnets_osblinnikov_github_com_test_static runnablesContainer_cnets_osblinnikov_github_com_static)
    target_link_libraries(runnablesContainer_cnets_osblinnikov_github_com_test_static
                            ${LD_FLAGS}
                            runnablesContainer_cnets_osblinnikov_github_com_static)
    addDeps(_test_static _static)
endif ()



link_directories(${LD_DIRS})
include_directories(. ${INCLUDE_DIRS})

# install includes
if(NOT WIN32)
  install(DIRECTORY / DESTINATION include/ FILES_MATCHING PATTERN "*.h")
  install(DIRECTORY / DESTINATION include/ FILES_MATCHING PATTERN "*.h")
endif()



