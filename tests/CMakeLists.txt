find_package(GTest REQUIRED)

file(GLOB_RECURSE _testfiles ${CMAKE_CURRENT_LIST_DIR}/*Test.cpp CONFIGURE_DEPEND)

add_executable(cpl_test ${_testfiles})
target_link_libraries(cpl_test PRIVATE CPL::cpl GTest::GTest GTest::Main)
enable_testing()

foreach(_testfile ${_testfiles})
    get_filename_component(_testname ${_testfile} NAME_WE)
    string(REPLACE "Test" "" _suite_name ${_testname})
    add_test(
        NAME CPL_TEST_${_suite_name}
        COMMAND cpl_test --gtest_filter=${_suite_name}.*
    )
endforeach()

unset(_testfiles)
