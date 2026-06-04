project(lab-5 LANGUAGES CXX)

add_library(${PROJECT_NAME}_lib STATIC)
target_sources(${PROJECT_NAME}_lib
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    lib/TextAnalyzer.ixx
    lib/IDataSource.cppm
    lib/FileDataSource.cppm
    lib/TextNormalizer.cppm
    lib/WordAnalyzer.cppm
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    inx
    console
    ${PROJECT_NAME}_lib
)
