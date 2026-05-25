project("practice-10" LANGUAGES CXX)

find_package(SFML COMPONENTS Graphics Audio CONFIG REQUIRED)

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SFML::Audio
    SFML::Graphics
)

target_sources(${PROJECT_NAME}
    PRIVATE
    main.cpp
    PRIVATE FILE_SET CXX_MODULES FILES
    api.cppm
    tictactoe.cppm
)

add_custom_target(${PROJECT_NAME}_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}/assets
    COMMENT "Copying assets to build directory..."
)
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_assets)
