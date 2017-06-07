
FILE(GLOB_RECURSE
    IRT_TESTS_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    IRT_TESTS_HEADERS
    *.h
)

include_directories(${Boost_INCLUDE_DIR}  ${EIGEN_INCLUDE_DIRS})
add_executable(IRT_test ${IRT_TESTS_SRC} ${IRT_TEST_HEADERS})
target_link_libraries (IRT_test IRT ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(IRT IRT_test --log_level=message)

set_target_properties (IRT_test PROPERTIES
    FOLDER Tests
)
