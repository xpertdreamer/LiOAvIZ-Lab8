add_library(Queue STATIC
        queue.h
)

set_target_properties(Queue PROPERTIES
        LINKER_LANGUAGE CXX
)

target_include_directories(Queue PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)