cmake_minimum_required(VERSION 3.2)
project(SimpleJSON)

include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")
OPTION(ENABLE_TESTS "Build tests." OFF)

set(SimpleJSON_INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/include
	CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

	add_subdirectory(lib/gtest)

	enable_testing()

	add_executable(test1 tests/test.cpp)
	target_link_libraries(test1 gtest gtest_main)
	add_test(test1 test1)

	add_executable(factory tests/factory.cpp)
	target_link_libraries(factory gtest gtest_main)
	add_test(factory factory)

	add_executable(parser tests/parser.cpp)
	target_link_libraries(parser gtest gtest_main)
	add_test(parser parser)

	add_executable(serializable tests/serializable.cpp)
	target_link_libraries(serializable gtest gtest_main)
	add_test(serializable serializable)

	add_executable(types tests/types.cpp)
	target_link_libraries(types gtest gtest_main)
	add_test(types types)

	add_executable(value tests/value.cpp)
	target_link_libraries(value gtest gtest_main)
	add_test(value value)

	add_executable(perf tests/perf.cpp)
	target_link_libraries(perf gtest gtest_main)
	add_test(perf perf)

