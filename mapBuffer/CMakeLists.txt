
cmake_minimum_required(VERSION 2.8)
project(mapBuffer_cnets_osblinnikov_github_com C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(.)

function(addDeps buildType dstBuildType)
# [[[cog
# import cogging as c
# c.tpl(cog,templateFile,c.a(prefix=configFile))
# ]]]

  include_directories(../../../../)
  add_dependencies(mapBuffer_cnets_osblinnikov_github_com${buildType} queue_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(mapBuffer_cnets_osblinnikov_github_com${buildType} queue_cnets_osblinnikov_github_com${dstBuildType})
  add_dependencies(mapBuffer_cnets_osblinnikov_github_com${buildType} types_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(mapBuffer_cnets_osblinnikov_github_com${buildType} types_cnets_osblinnikov_github_com${dstBuildType})
  add_dependencies(mapBuffer_cnets_osblinnikov_github_com${buildType} readerWriter_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(mapBuffer_cnets_osblinnikov_github_com${buildType} readerWriter_cnets_osblinnikov_github_com${dstBuildType})
  add_dependencies(mapBuffer_cnets_osblinnikov_github_com${buildType} vector_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(mapBuffer_cnets_osblinnikov_github_com${buildType} vector_cnets_osblinnikov_github_com${dstBuildType})

# install includes
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/mapBuffer FILES_MATCHING PATTERN "*.h" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/mapBuffer FILES_MATCHING PATTERN "*.hpp" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
# [[[end]]] (checksum: eca427c9a9981d16d91f99fd68607cf4)

target_link_libraries(mapBuffer_cnets_osblinnikov_github_com${buildType} pthread)

endfunction(addDeps)

file(GLOB MAPBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS "*.h")

set (MAPBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS
    src/mapBuffer.c
    )
set(MAPBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_TEST
    tests/mapBufferTest.c
    )

add_custom_target(mapBuffer_cnets_osblinnikov_github_com)

if (NOT BUILD_STATIC_ONLY)
    add_library(mapBuffer_cnets_osblinnikov_github_com_shared SHARED ${MAPBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS} ${MAPBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS})
    add_dependencies(mapBuffer_cnets_osblinnikov_github_com_shared mapBuffer_cnets_osblinnikov_github_com)
    target_link_libraries(mapBuffer_cnets_osblinnikov_github_com_shared ${LD_FLAGS} )
    addDeps(_shared _shared)
    if(NOT WIN32)
        install(TARGETS mapBuffer_cnets_osblinnikov_github_com_shared LIBRARY DESTINATION lib)
    endif()

    add_executable(mapBuffer_cnets_osblinnikov_github_com_test_shared ${MAPBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(mapBuffer_cnets_osblinnikov_github_com_test_shared mapBuffer_cnets_osblinnikov_github_com_shared)
    target_link_libraries(mapBuffer_cnets_osblinnikov_github_com_test_shared
                          ${LD_FLAGS}
                          mapBuffer_cnets_osblinnikov_github_com_shared)
    addDeps(_test_shared _shared)
endif ()

if (BUILD_STATIC_ONLY OR BUILD_STATIC)
    add_library(mapBuffer_cnets_osblinnikov_github_com_static STATIC ${MAPBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS} ${MAPBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS})
    add_dependencies(mapBuffer_cnets_osblinnikov_github_com_static mapBuffer_cnets_osblinnikov_github_com)
    addDeps(_static _static)
    if(NOT WIN32)
        install(TARGETS mapBuffer_cnets_osblinnikov_github_com_static ARCHIVE DESTINATION lib)
    endif()

    add_executable(mapBuffer_cnets_osblinnikov_github_com_test_static ${MAPBUFFER_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(mapBuffer_cnets_osblinnikov_github_com_test_static mapBuffer_cnets_osblinnikov_github_com_static)
    target_link_libraries(mapBuffer_cnets_osblinnikov_github_com_test_static
                            ${LD_FLAGS}
                            mapBuffer_cnets_osblinnikov_github_com_static)
    addDeps(_test_static _static)
endif ()



link_directories(${LD_DIRS})
include_directories(. ${INCLUDE_DIRS})



