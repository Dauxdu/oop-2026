project(practice-8 LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    examples
)
