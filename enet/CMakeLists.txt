
cmake_minimum_required(VERSION 2.8)
project(enet_cnets_osblinnikov_github_com C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")


include(CheckFunctionExists)
include(CheckStructHasMember)
include(CheckTypeSize)
check_function_exists("fcntl" HAS_FCNTL)
check_function_exists("poll" HAS_POLL)
check_function_exists("getaddrinfo" HAS_GETADDRINFO)
check_function_exists("getnameinfo" HAS_GETNAMEINFO)
check_function_exists("gethostbyname_r" HAS_GETHOSTBYNAME_R)
check_function_exists("gethostbyaddr_r" HAS_GETHOSTBYADDR_R)
check_function_exists("inet_pton" HAS_INET_PTON)
check_function_exists("inet_ntop" HAS_INET_NTOP)
check_struct_has_member("struct msghdr" "msg_flags" "sys/types.h;sys/socket.h" HAS_MSGHDR_FLAGS)
set(CMAKE_EXTRA_INCLUDE_FILES "sys/types.h" "sys/socket.h")
check_type_size("socklen_t" HAS_SOCKLEN_T BUILTIN_TYPES_ONLY)
unset(CMAKE_EXTRA_INCLUDE_FILES)

if(HAS_FCNTL)
    add_definitions(-DHAS_FCNTL=1)
endif()
if(HAS_POLL)
    add_definitions(-DHAS_POLL=1)
endif()
if(HAS_GETNAMEINFO)
    add_definitions(-DHAS_GETNAMEINFO=1)
endif()
if(HAS_GETADDRINFO)
    add_definitions(-DHAS_GETADDRINFO=1)
endif()
if(HAS_GETHOSTBYNAME_R)
    add_definitions(-DHAS_GETHOSTBYNAME_R=1)
endif()
if(HAS_GETHOSTBYADDR_R)
    add_definitions(-DHAS_GETHOSTBYADDR_R=1)
endif()
if(HAS_INET_PTON)
    add_definitions(-DHAS_INET_PTON=1)
endif()
if(HAS_INET_NTOP)
    add_definitions(-DHAS_INET_NTOP=1)
endif()
if(HAS_MSGHDR_FLAGS)
    add_definitions(-DHAS_MSGHDR_FLAGS=1)
endif()
if(HAS_SOCKLEN_T)
    add_definitions(-DHAS_SOCKLEN_T=1)
endif()

include_directories(.)

function(addDeps buildType dstBuildType)
# [[[cog
# import cogging as c
# c.tpl(cog,templateFile,c.a(prefix=configFile))
# ]]]

  include_directories(../../../../)

# install includes
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/enet FILES_MATCHING PATTERN "*.h" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
install(DIRECTORY . DESTINATION include/github.com/osblinnikov/cnets/enet FILES_MATCHING PATTERN "*.hpp" PATTERN "tests" EXCLUDE PATTERN "src" EXCLUDE PATTERN "Release" EXCLUDE  PATTERN "Debug" EXCLUDE PATTERN ".s*" EXCLUDE )
# [[[end]]] (checksum: 110891f28138521c58f02ab823314500)
endfunction(addDeps)

file(GLOB ENET_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS "*.h")

set (ENET_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS
        src/callbacks.c
        src/compress.c
        src/host.c
        src/list.c
        src/packet.c
        src/peer.c
        src/protocol.c
        src/enet.c
        src/win32.c
    )
set(ENET_CNETS_OSBLINNIKOV_GITHUB_COM_TEST
    tests/enetTest.c
    )

add_custom_target(enet_cnets_osblinnikov_github_com)

if (NOT BUILD_STATIC_ONLY)
    add_library(enet_cnets_osblinnikov_github_com_shared SHARED ${ENET_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS} ${ENET_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS})
    add_dependencies(enet_cnets_osblinnikov_github_com_shared enet_cnets_osblinnikov_github_com)
    target_link_libraries(enet_cnets_osblinnikov_github_com_shared ${LD_FLAGS} )
    addDeps(_shared _shared)
    if(NOT WIN32)
        install(TARGETS enet_cnets_osblinnikov_github_com_shared LIBRARY DESTINATION lib)
    endif()

    add_executable(enet_cnets_osblinnikov_github_com_test_shared ${ENET_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(enet_cnets_osblinnikov_github_com_test_shared enet_cnets_osblinnikov_github_com_shared)
    target_link_libraries(enet_cnets_osblinnikov_github_com_test_shared
                          ${LD_FLAGS}
                          enet_cnets_osblinnikov_github_com_shared)
    addDeps(_test_shared _shared)
endif ()

if (BUILD_STATIC_ONLY OR BUILD_STATIC)
    add_library(enet_cnets_osblinnikov_github_com_static STATIC ${ENET_CNETS_OSBLINNIKOV_GITHUB_COM_HDRS} ${ENET_CNETS_OSBLINNIKOV_GITHUB_COM_SRCS})
    add_dependencies(enet_cnets_osblinnikov_github_com_static enet_cnets_osblinnikov_github_com)
    addDeps(_static _static)
    if(NOT WIN32)
        install(TARGETS enet_cnets_osblinnikov_github_com_static ARCHIVE DESTINATION lib)
    endif()

    add_executable(enet_cnets_osblinnikov_github_com_test_static ${ENET_CNETS_OSBLINNIKOV_GITHUB_COM_TEST})
    add_dependencies(enet_cnets_osblinnikov_github_com_test_static enet_cnets_osblinnikov_github_com_static)
    target_link_libraries(enet_cnets_osblinnikov_github_com_test_static
                            ${LD_FLAGS}
                            enet_cnets_osblinnikov_github_com_static)
    addDeps(_test_static _static)
endif ()



link_directories(${LD_DIRS})
include_directories(. ${INCLUDE_DIRS})




