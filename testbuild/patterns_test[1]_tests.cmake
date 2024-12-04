add_test([=[HelloTest.BasicAssertions]=]  /home/felipetrost/projects/personal/remote-rgb-lights/testbuild/patterns_test [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY /home/felipetrost/projects/personal/remote-rgb-lights/testbuild SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  patterns_test_TESTS HelloTest.BasicAssertions)
