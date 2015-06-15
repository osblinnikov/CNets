
cmake_minimum_required(VERSION 2.8)
project(dispatchBuffer_cnets_osblinnikov_github_com C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(.)

function(addDeps buildType dstBuildType)
# [[[cog
# import cogging as c
# c.tpl(cog,templateFile,c.a(prefix=configFile))
# ]]]

include_directories(../../../../)
add_dependencies(dispatchBuffer_cnets_osblinnikov_github_com${buildType} readerWriter_cnets_osblinnikov_github_com${dstBuildType})
target_link_libraries(dispatchBuffer_cnets_osblinnikov_github_com${buildType} readerWriter_cnets_osblinnikov_github_com${dstBuildType})
add_dependencies(dispatchBuffer_cnets_osblinnikov_github_com${buildType} types_cnets_osblinnikov_github_com${dstBuildType})
target_link_libraries(dispatchBuffer_cnets_osblinnikov_github_com${buildType} types_cnets_osblinnikov_github_com${dstBuildType})
add_dependencies(dispatchBuffer_cnets_osblinnikov_github_com${buildType} vector_cnets_osblinnikov_github_com${dstBuildType})
target_link_libraries(dispatchBuffer_cnets_osblinnikov_github_com${buildType} vector_cnets_osblinnikov_github_com${dstBuildType})
# [[[end]]] (checksum: c1d560ced3c8c4c6513c268188677a89)
endfunction(addDeps)

file(GLOB DISPATCHBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS "*.h")

set (DISPATCHBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS
    src/dispatchBuffer.c
    )
set(DISPATCHBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_TEST
    tests/dispatchBufferTest.c
    )

add_custom_target(dispatchBuffer_cnets_osblinnikov_github_com)

if (NOT BUILD_STATIC_ONLY)
    add_library(dispatchBuffer_cnets_osblinnikov_github_com_shared SHARED ${DISPATCHBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS} ${DISPATCHBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS})
    add_dependencies(dispatchBuffer_cnets_osblinnikov_github_com_shared dispatchBuffer_cnets_osblinnikov_github_com)
    target_link_libraries(dispatchBuffer_cnets_osblinnikov_github_com_shared ${LD_FLAGS} )
    addDeps(_shared _shared)
    if(NOT WIN32)
        install(TARGETS dispatchBuffer_cnets_osblinnikov_github_com_shared LIBRARY DESTINATION lib)
    endif()

    add_executable(dispatchBuffer_cnets_osblinnikov_github_com_test_shared ${DISPATCHBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(dispatchBuffer_cnets_osblinnikov_github_com_test_shared dispatchBuffer_cnets_osblinnikov_github_com_shared)
    target_link_libraries(dispatchBuffer_cnets_osblinnikov_github_com_test_shared
                          ${LD_FLAGS}
                          dispatchBuffer_cnets_osblinnikov_github_com_shared)
    addDeps(_test_shared _shared)
endif ()

if (BUILD_STATIC_ONLY OR BUILD_STATIC)
    add_library(dispatchBuffer_cnets_osblinnikov_github_com_static STATIC ${DISPATCHBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS} ${DISPATCHBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS})
    add_dependencies(dispatchBuffer_cnets_osblinnikov_github_com_static dispatchBuffer_cnets_osblinnikov_github_com)
    addDeps(_static _static)
    if(NOT WIN32)
        install(TARGETS dispatchBuffer_cnets_osblinnikov_github_com_static ARCHIVE DESTINATION lib)
    endif()

    add_executable(dispatchBuffer_cnets_osblinnikov_github_com_test_static ${DISPATCHBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(dispatchBuffer_cnets_osblinnikov_github_com_test_static dispatchBuffer_cnets_osblinnikov_github_com_static)
    target_link_libraries(dispatchBuffer_cnets_osblinnikov_github_com_test_static
                            ${LD_FLAGS}
                            dispatchBuffer_cnets_osblinnikov_github_com_static)
    addDeps(_test_static _static)
endif ()



link_directories(${LD_DIRS})
include_directories(. ${INCLUDE_DIRS})

# install includes
if(NOT WIN32)
  install(DIRECTORY / DESTINATION include/ FILES_MATCHING PATTERN "*.h")
  install(DIRECTORY / DESTINATION include/ FILES_MATCHING PATTERN "*.h")
endif()



