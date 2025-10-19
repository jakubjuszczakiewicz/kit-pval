# Copyright (c) 2025 Jakub Juszczakiewicz
# All rights reserved.

enable_testing()

add_executable(version "test_version.c")
target_link_libraries(version "kitpval")
add_test(NAME "version" COMMAND "version")

add_executable(int128acc "test_int128acc.c" "xprint.c")
target_link_libraries(int128acc "kitpval")
add_test(NAME "int128acc" COMMAND "int128acc")

add_executable(printer "test_printer.c")
target_link_libraries(printer "kitpval")
add_test(NAME "printer" COMMAND "printer")
