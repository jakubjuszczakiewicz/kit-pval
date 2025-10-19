# Copyright (c) 2025 Jakub Juszczakiewicz
# All rights reserved.

cmake_minimum_required(VERSION 3.20)
project(kit-pval C)

set(WITH_TESTS TRUE CACHE BOOL true)

set(SOURCE_FILES_PVAL
  src/main.c
)

set(SOURCE_FILES_LIB
  src/version.c
  src/int128acc.c
  src/printer.c
)

include (TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
 add_definitions(-DBIG_ENDIAN)
else()
 add_definitions(-DLITTLE_ENDIAN)
endif()

if(MINGW)
add_definitions(-DUSE_WINAPI)
add_definitions(-DIS_MINGW)
elseif(WIN32)
add_definitions(-DUSE_WINAPI)
endif()

check_type_size("unsigned __int128" U128S)
if(U128S EQUAL 16)
 add_definitions(-DHAVE_INT128)
endif()

add_library(kitpval STATIC ${SOURCE_FILES_LIB})

add_executable(${PROJECT_NAME} ${SOURCE_FILES_PVAL})
target_link_libraries(${PROJECT_NAME} "kitpval")
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

if (${WITH_TESTS})
  include(CTest)
  add_subdirectory(tests)
endif()
