
cmake_minimum_required(VERSION 2.8)
project(types_cnets_osblinnikov_github_com C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include_directories(.)

function(addDeps buildType dstBuildType)
# [[[cog
# import cogging as c
# c.tpl(cog,templateFile,c.a(prefix=configFile))
# ]]]

  include_directories(../../../../)

# install includes
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/types FILES_MATCHING PATTERN "*.h" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/types FILES_MATCHING PATTERN "*.hpp" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
# [[[end]]] (checksum: cf856658d798f322fc7a324c27c4e236)
endfunction(addDeps)

file(GLOB TYPES_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS "vc/*.h" "*.h")

set (TYPES_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS
    src/types.c
    src/timeUtils.c
    )
set(TYPES_CNETS_OSBLINNIKOV_GITHUB_COM_TEST
    tests/typesTest.c
    )

add_custom_target(types_cnets_osblinnikov_github_com)

if (NOT BUILD_STATIC_ONLY)
    add_library(types_cnets_osblinnikov_github_com_shared SHARED ${TYPES_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS} ${TYPES_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS})
    add_dependencies(types_cnets_osblinnikov_github_com_shared types_cnets_osblinnikov_github_com)
    target_link_libraries(types_cnets_osblinnikov_github_com_shared ${LD_FLAGS} )
    addDeps(_shared _shared)
    if(NOT WIN32)
        install(TARGETS types_cnets_osblinnikov_github_com_shared LIBRARY DESTINATION lib)
    endif()

    add_executable(types_cnets_osblinnikov_github_com_test_shared ${TYPES_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(types_cnets_osblinnikov_github_com_test_shared types_cnets_osblinnikov_github_com_shared)
    target_link_libraries(types_cnets_osblinnikov_github_com_test_shared
                          ${LD_FLAGS}
                          types_cnets_osblinnikov_github_com_shared)
    addDeps(_test_shared _shared)
endif ()

if (BUILD_STATIC_ONLY OR BUILD_STATIC)
    add_library(types_cnets_osblinnikov_github_com_static STATIC ${TYPES_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS} ${TYPES_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS})
    add_dependencies(types_cnets_osblinnikov_github_com_static types_cnets_osblinnikov_github_com)
    addDeps(_static _static)
    if(NOT WIN32)
        install(TARGETS types_cnets_osblinnikov_github_com_static ARCHIVE DESTINATION lib)
    endif()

    add_executable(types_cnets_osblinnikov_github_com_test_static ${TYPES_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(types_cnets_osblinnikov_github_com_test_static types_cnets_osblinnikov_github_com_static)
    target_link_libraries(types_cnets_osblinnikov_github_com_test_static
                            ${LD_FLAGS}
                            types_cnets_osblinnikov_github_com_static)
    addDeps(_test_static _static)
endif ()



link_directories(${LD_DIRS})
include_directories(. ${INCLUDE_DIRS})

