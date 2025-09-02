cmake_minimum_required(VERSION 3.16)

project(consha C)

add_compile_options(-Wall -Wextra -Werror)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.c)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} readline)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
