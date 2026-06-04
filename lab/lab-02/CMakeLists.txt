project(lab-2 LANGUAGES CXX)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    src/main.cpp
    PRIVATE FILE_SET CXX_MODULES
    TYPE CXX_MODULES
    FILES
    utils/vector.cppm
)

target_link_libraries("${PROJECT_NAME}"
    PRIVATE
    inx
    console
)

