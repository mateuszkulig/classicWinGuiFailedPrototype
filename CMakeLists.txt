cmake_minimum_required(VERSION 3.15)

project(classicWG VERSION 0.1)

# path to src folder with .c files and inc folder with .h files
set(PATH_SRC ${PROJECT_SOURCE_DIR}/src)
set(PATH_INC ${PROJECT_SOURCE_DIR}/inc)

# EXEC list with all of sources to add by "add_executable" 
list(APPEND EXEC ${PATH_SRC}/main.c)
list(APPEND EXEC ${PATH_SRC}/root.c)

# add sdl
include_directories("${PROJECT_SOURCE_DIR}/SDL")
add_subdirectory(SDL)

# add all executables from EXEC list
add_executable(classicWG ${EXEC})


# copy sdl dll file into build folder; it does not do it by default
# taken from https://github.com/libsdl-org/SDL/issues/6399
add_custom_command(TARGET classicWG POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:SDL2::SDL2>" "$<TARGET_FILE_DIR:classicWG>" VERBATIM)


# copy resources folder to build dir
# taken from https://stackoverflow.com/questions/3702115/creating-a-directory-in-cmake
add_custom_command(TARGET classicWG POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    ${CMAKE_SOURCE_DIR}/res ${CMAKE_BINARY_DIR}/res)

# link sdl
target_link_libraries(classicWG SDL2)

# includes
target_include_directories(classicWG PUBLIC ${PATH_INC}/)