# Add the test executable
add_executable(test_TaskManager test_main.cpp)
target_include_directories(
test_TaskManager  PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/_deps/googletest-src/googletest/include/gtest
${CMAKE_CURRENT_SOURCE_DIR}/_deps/googletest-src/googletest/include/gtest/include
)
target_compile_definitions(test_TaskManager PRIVATE GTEST_HAS_REGEX=1 GTEST_HAS_POSIX_RE=0)
# Link the test executable with Google Test and the main project executable or libraries if needed
target_link_libraries(test_TaskManager PRIVATE gtest gtest_main ${CMAKE_THREAD_LIBS_INIT} TaskManager_lib)

# Add the test
add_test(NAME TestMain COMMAND test_TaskManager)
