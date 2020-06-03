add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")

set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)


macro(package_add_test_with_libraries TESTNAME FILES LIBRARIES)
    add_executable(${TESTNAME} ${FILES})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main ${LIBRARIES})
    gtest_discover_tests(${TESTNAME}
            WORKING_DIRECTORY ${TEST_WORKING_DIRECTORY}
            )

    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()


package_add_test_with_libraries(test_array_iterator test_array_iterator.cpp mbl)
package_add_test_with_libraries(test_array_pointer_iterator test_array_pointer_iterator.cpp mbl)
package_add_test_with_libraries(test_list_iterator test_list_iterator.cpp mbl)

package_add_test_with_libraries(test_cli test_cli.cpp mbl)
package_add_test_with_libraries(test_rcw test_rcw.cpp mbl)
