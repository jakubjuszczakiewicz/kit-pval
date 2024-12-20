cmake_minimum_required(VERSION 3.1...3.5)
project(kit-pval C)

set(SOURCE_FILES
  src/main.c
  src/version.c
  src/int128acc.c
)

include (TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if(IS_BIG_ENDIAN)
 add_definitions(-DBIG_ENDIAN)
else()
 add_definitions(-DLITTLE_ENDIAN)
endif()

check_type_size("unsigned __int128" U128S)
if(U128S EQUAL 16)
 add_definitions(-DHAVE_INT128)
endif()

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
