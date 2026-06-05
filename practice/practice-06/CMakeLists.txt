project(practice-6 LANGUAGES CXX)

add_library(${PROJECT_NAME}_lib STATIC)
target_sources(${PROJECT_NAME}_lib
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    lib/Formatter.cppm
    lib/String.cppm
    lib/StringBuilder.cppm
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)
