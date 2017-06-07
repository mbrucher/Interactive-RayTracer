
FILE(GLOB_RECURSE
    IRT_CORE_SRC
    *.cpp
)

FILE(GLOB_RECURSE
    IRT_CORE_HEADERS
    *.h
)

add_definitions(-DIRT_EXPORTS)
include_directories(${PROJECT_SOURCE_DIR} ${EIGEN_INCLUDE_DIRS})

add_library(IRT
    SHARED
    ${IRT_CORE_SRC} ${IRT_CORE_HEADERS}
)

set_target_properties (IRT PROPERTIES
    FOLDER Core
)
