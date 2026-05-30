project(practice-9 LANGUAGES CXX)

find_package(httplib CONFIG REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE httplib::httplib)
