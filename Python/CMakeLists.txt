
find_package(pybind11 REQUIRED)

FILE(GLOB_RECURSE
  PYTHON_MODULE_IRT_SRC
  *.cpp
)

FILE(GLOB_RECURSE
  PYTHON_MODULE_IRT_HEADERS
  *.h
)

include_directories(${PROJECT_SOURCE_DIR} ${Boost_INCLUDE_DIR} ${NUMPY_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIRS})

pybind11_add_module(PythonIRT MODULE ${PYTHON_MODULE_IRT_SRC} ${PYTHON_MODULE_IRT_HEADERS})
target_link_libraries(PythonIRT PRIVATE IRT)

INSTALL(FILES __init__.py
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/site-packages/IRT
    )
INSTALL(TARGETS PythonIRT
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/site-packages/IRT
    )

set_target_properties (PythonIRT PROPERTIES
    FOLDER Python
)
