project(practice-07.1 LANGUAGES CXX)

add_library(counters STATIC)
target_sources(counters
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    lib/counters.ixx
    lib/ICounter.cppm
    lib/BoundedCounter.cppm
    lib/CyclicCounter.cppm
    lib/StepCounter.cppm
)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE counters)
