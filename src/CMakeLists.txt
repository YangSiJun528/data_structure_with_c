# Add all .c files in the directory to SRC_FILES
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

# Define a library target with the source files
add_library(data_structure_with_c_lib ${SRC_FILES})

# Define the executable target
add_executable(data_structure_with_c_src ${SRC_FILES})
