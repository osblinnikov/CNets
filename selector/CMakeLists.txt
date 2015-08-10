
cmake_minimum_required(VERSION 2.8)
project(selector_cnets_osblinnikov_github_com C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(.)

function(addDeps buildType dstBuildType)
# [[[cog
# import cogging as c
# c.tpl(cog,templateFile,c.a(prefix=configFile))
# ]]]

  include_directories(../../../../)
  add_dependencies(selector_cnets_osblinnikov_github_com${buildType} mapBuffer_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(selector_cnets_osblinnikov_github_com${buildType} mapBuffer_cnets_osblinnikov_github_com${dstBuildType})
  add_dependencies(selector_cnets_osblinnikov_github_com${buildType} readerWriter_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(selector_cnets_osblinnikov_github_com${buildType} readerWriter_cnets_osblinnikov_github_com${dstBuildType})
  add_dependencies(selector_cnets_osblinnikov_github_com${buildType} queue_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(selector_cnets_osblinnikov_github_com${buildType} queue_cnets_osblinnikov_github_com${dstBuildType})
  add_dependencies(selector_cnets_osblinnikov_github_com${buildType} runnablesContainer_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(selector_cnets_osblinnikov_github_com${buildType} runnablesContainer_cnets_osblinnikov_github_com${dstBuildType})
  add_dependencies(selector_cnets_osblinnikov_github_com${buildType} types_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(selector_cnets_osblinnikov_github_com${buildType} types_cnets_osblinnikov_github_com${dstBuildType})

# install includes
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/selector FILES_MATCHING PATTERN "*.h" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/selector FILES_MATCHING PATTERN "*.hpp" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
# [[[end]]] (checksum: 8c00d2b9f4c10c44459817166c3ff7c1)

target_link_libraries(selector_cnets_osblinnikov_github_com${buildType} pthread)

endfunction(addDeps)

file(GLOB SELECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS "*.h")

set (SELECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS
    src/selector.c
    )
set(SELECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_TEST
    tests/selectorTest.c
    )

add_custom_target(selector_cnets_osblinnikov_github_com)

if (NOT BUILD_STATIC_ONLY)
    add_library(selector_cnets_osblinnikov_github_com_shared SHARED ${SELECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS} ${SELECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS})
    add_dependencies(selector_cnets_osblinnikov_github_com_shared selector_cnets_osblinnikov_github_com)
    target_link_libraries(selector_cnets_osblinnikov_github_com_shared ${LD_FLAGS} )
    addDeps(_shared _shared)
    if(NOT WIN32)
        install(TARGETS selector_cnets_osblinnikov_github_com_shared LIBRARY DESTINATION lib)
    endif()

    add_executable(selector_cnets_osblinnikov_github_com_test_shared ${SELECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(selector_cnets_osblinnikov_github_com_test_shared selector_cnets_osblinnikov_github_com_shared)
    target_link_libraries(selector_cnets_osblinnikov_github_com_test_shared
                          ${LD_FLAGS}
                          selector_cnets_osblinnikov_github_com_shared)
    addDeps(_test_shared _shared)
endif ()

if (BUILD_STATIC_ONLY OR BUILD_STATIC)
    add_library(selector_cnets_osblinnikov_github_com_static STATIC ${SELECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS} ${SELECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS})
    add_dependencies(selector_cnets_osblinnikov_github_com_static selector_cnets_osblinnikov_github_com)
    addDeps(_static _static)
    if(NOT WIN32)
        install(TARGETS selector_cnets_osblinnikov_github_com_static ARCHIVE DESTINATION lib)
    endif()

    add_executable(selector_cnets_osblinnikov_github_com_test_static ${SELECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(selector_cnets_osblinnikov_github_com_test_static selector_cnets_osblinnikov_github_com_static)
    target_link_libraries(selector_cnets_osblinnikov_github_com_test_static
                            ${LD_FLAGS}
                            selector_cnets_osblinnikov_github_com_static)
    addDeps(_test_static _static)
endif ()



link_directories(${LD_DIRS})
include_directories(. ${INCLUDE_DIRS})


