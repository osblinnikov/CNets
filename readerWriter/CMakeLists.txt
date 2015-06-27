
cmake_minimum_required(VERSION 2.8)
project(readerWriter_cnets_osblinnikov_github_com C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(.)

function(addDeps buildType dstBuildType)
# [[[cog
# import cogging as c
# c.tpl(cog,templateFile,c.a(prefix=configFile))
# ]]]

  include_directories(../../../../)
  add_dependencies(readerWriter_cnets_osblinnikov_github_com${buildType} vector_cnets_osblinnikov_github_com${dstBuildType})
  target_link_libraries(readerWriter_cnets_osblinnikov_github_com${buildType} vector_cnets_osblinnikov_github_com${dstBuildType})

# install includes
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/readerWriter FILES_MATCHING PATTERN "*.h" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/readerWriter FILES_MATCHING PATTERN "*.hpp" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
# [[[end]]] (checksum: 96d2231fe19865df3f276a6bf83a0d53)
endfunction(addDeps)

file(GLOB READERWRITER_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS "*.h")

set (READERWRITER_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS
    src/readerWriter.c
    src/statsCollectorStatic.c
    )
set(READERWRITER_CNETS_OSBLINNIKOV_GITHUB_COM_TEST
    tests/readerWriterTest.c
    )

add_custom_target(readerWriter_cnets_osblinnikov_github_com)

if (NOT BUILD_STATIC_ONLY)
    add_library(readerWriter_cnets_osblinnikov_github_com_shared SHARED ${READERWRITER_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS} ${READERWRITER_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS})
    add_dependencies(readerWriter_cnets_osblinnikov_github_com_shared readerWriter_cnets_osblinnikov_github_com)
    target_link_libraries(readerWriter_cnets_osblinnikov_github_com_shared ${LD_FLAGS} )
    addDeps(_shared _shared)
    if(NOT WIN32)
        install(TARGETS readerWriter_cnets_osblinnikov_github_com_shared LIBRARY DESTINATION lib)
    endif()

    add_executable(readerWriter_cnets_osblinnikov_github_com_test_shared ${READERWRITER_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(readerWriter_cnets_osblinnikov_github_com_test_shared readerWriter_cnets_osblinnikov_github_com_shared)
    target_link_libraries(readerWriter_cnets_osblinnikov_github_com_test_shared
                          ${LD_FLAGS}
                          readerWriter_cnets_osblinnikov_github_com_shared)
    addDeps(_test_shared _shared)
endif ()

if (BUILD_STATIC_ONLY OR BUILD_STATIC)
    add_library(readerWriter_cnets_osblinnikov_github_com_static STATIC ${READERWRITER_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS} ${READERWRITER_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS})
    add_dependencies(readerWriter_cnets_osblinnikov_github_com_static readerWriter_cnets_osblinnikov_github_com)
    addDeps(_static _static)
    if(NOT WIN32)
        install(TARGETS readerWriter_cnets_osblinnikov_github_com_static ARCHIVE DESTINATION lib)
    endif()

    add_executable(readerWriter_cnets_osblinnikov_github_com_test_static ${READERWRITER_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(readerWriter_cnets_osblinnikov_github_com_test_static readerWriter_cnets_osblinnikov_github_com_static)
    target_link_libraries(readerWriter_cnets_osblinnikov_github_com_test_static
                            ${LD_FLAGS}
                            readerWriter_cnets_osblinnikov_github_com_static)
    addDeps(_test_static _static)
endif ()



link_directories(${LD_DIRS})
include_directories(. ${INCLUDE_DIRS})


