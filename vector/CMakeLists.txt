
cmake_minimum_required(VERSION 2.8)
project(vector_cnets_osblinnikov_github_com C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(.)

function(addDeps buildType dstBuildType)
# [[[cog
# import cogging as c
# c.tpl(cog,templateFile,c.a(prefix=configFile))
# ]]]

  include_directories(../../../../)

# install includes
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/vector FILES_MATCHING PATTERN "*.h" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/vector FILES_MATCHING PATTERN "*.hpp" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
# [[[end]]] (checksum: 63ab1d629613df8b74cd83ce0eb40351)
endfunction(addDeps)

file(GLOB VECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS "*.h")

set (VECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS
    src/vector.c
    )
set(VECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_TEST
    tests/vectorTest.c
    )

add_custom_target(vector_cnets_osblinnikov_github_com)

if (NOT BUILD_STATIC_ONLY)
    add_library(vector_cnets_osblinnikov_github_com_shared SHARED ${VECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS} ${VECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS})
    add_dependencies(vector_cnets_osblinnikov_github_com_shared vector_cnets_osblinnikov_github_com)
    target_link_libraries(vector_cnets_osblinnikov_github_com_shared ${LD_FLAGS} )
    addDeps(_shared _shared)
    if(NOT WIN32)
        install(TARGETS vector_cnets_osblinnikov_github_com_shared LIBRARY DESTINATION lib)
    endif()

    add_executable(vector_cnets_osblinnikov_github_com_test_shared ${VECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(vector_cnets_osblinnikov_github_com_test_shared vector_cnets_osblinnikov_github_com_shared)
    target_link_libraries(vector_cnets_osblinnikov_github_com_test_shared
                          ${LD_FLAGS}
                          vector_cnets_osblinnikov_github_com_shared)
    addDeps(_test_shared _shared)
endif ()

if (BUILD_STATIC_ONLY OR BUILD_STATIC)
    add_library(vector_cnets_osblinnikov_github_com_static STATIC ${VECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS} ${VECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS})
    add_dependencies(vector_cnets_osblinnikov_github_com_static vector_cnets_osblinnikov_github_com)
    addDeps(_static _static)
    if(NOT WIN32)
        install(TARGETS vector_cnets_osblinnikov_github_com_static ARCHIVE DESTINATION lib)
    endif()

    add_executable(vector_cnets_osblinnikov_github_com_test_static ${VECTOR_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(vector_cnets_osblinnikov_github_com_test_static vector_cnets_osblinnikov_github_com_static)
    target_link_libraries(vector_cnets_osblinnikov_github_com_test_static
                            ${LD_FLAGS}
                            vector_cnets_osblinnikov_github_com_static)
    addDeps(_test_static _static)
endif ()



link_directories(${LD_DIRS})
include_directories(. ${INCLUDE_DIRS})

