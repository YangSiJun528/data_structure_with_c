# Add all .c files in the directory to SRC_FILES
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_executable(data_structure_with_c_tests ${SRC_FILES})