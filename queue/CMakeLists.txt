
cmake_minimum_required(VERSION 2.8)
project(queue_cnets_osblinnikov_github_com C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(.)

function(addDeps buildType dstBuildType)
# [[[cog
# import cogging as c
# c.tpl(cog,templateFile,c.a(prefix=configFile))
# ]]]

  include_directories(../../../../)
  add_dependencies(queue_cnets_osblinnikov_github_com${buildType} types_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(queue_cnets_osblinnikov_github_com${buildType} types_cnets_osblinnikov_github_com${dstBuildType})

# install includes
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/queue FILES_MATCHING PATTERN "*.h" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/queue FILES_MATCHING PATTERN "*.hpp" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
# [[[end]]] (checksum: 80752e22ee21e318d7d09641cfb5ef0f)
endfunction(addDeps)

file(GLOB QUEUE_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS "*.h")

set (QUEUE_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS
    src/queue.c
    )
set(QUEUE_CNETS_OSBLINNIKOV_GITHUB_COM_TEST
    tests/queueTest.c
    )

add_custom_target(queue_cnets_osblinnikov_github_com)

if (NOT BUILD_STATIC_ONLY)
    add_library(queue_cnets_osblinnikov_github_com_shared SHARED ${QUEUE_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS} ${QUEUE_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS})
    add_dependencies(queue_cnets_osblinnikov_github_com_shared queue_cnets_osblinnikov_github_com)
    target_link_libraries(queue_cnets_osblinnikov_github_com_shared ${LD_FLAGS} )
    addDeps(_shared _shared)
    if(NOT WIN32)
        install(TARGETS queue_cnets_osblinnikov_github_com_shared LIBRARY DESTINATION lib)
    endif()

    add_executable(queue_cnets_osblinnikov_github_com_test_shared ${QUEUE_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(queue_cnets_osblinnikov_github_com_test_shared queue_cnets_osblinnikov_github_com_shared)
    target_link_libraries(queue_cnets_osblinnikov_github_com_test_shared
                          ${LD_FLAGS}
                          queue_cnets_osblinnikov_github_com_shared)
    addDeps(_test_shared _shared)
endif ()

if (BUILD_STATIC_ONLY OR BUILD_STATIC)
    add_library(queue_cnets_osblinnikov_github_com_static STATIC ${QUEUE_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS} ${QUEUE_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS})
    add_dependencies(queue_cnets_osblinnikov_github_com_static queue_cnets_osblinnikov_github_com)
    addDeps(_static _static)
    if(NOT WIN32)
        install(TARGETS queue_cnets_osblinnikov_github_com_static ARCHIVE DESTINATION lib)
    endif()

    add_executable(queue_cnets_osblinnikov_github_com_test_static ${QUEUE_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(queue_cnets_osblinnikov_github_com_test_static queue_cnets_osblinnikov_github_com_static)
    target_link_libraries(queue_cnets_osblinnikov_github_com_test_static
                            ${LD_FLAGS}
                            queue_cnets_osblinnikov_github_com_static)
    addDeps(_test_static _static)
endif ()



link_directories(${LD_DIRS})
include_directories(. ${INCLUDE_DIRS})


