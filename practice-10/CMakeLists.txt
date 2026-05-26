project("practice-10" LANGUAGES CXX)

find_package(SFML COMPONENTS Graphics Audio CONFIG REQUIRED)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
    src/main.cpp
    PRIVATE FILE_SET CXX_MODULES FILES
    lib/Assets.cppm
    lib/GameLogic.cppm
    lib/Renderer.cppm
    lib/TicTacToe.cppm
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    SFML::Audio
    SFML::Graphics
)

add_custom_target(${PROJECT_NAME}_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/assets
    ${CMAKE_CURRENT_BINARY_DIR}/assets
)

add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_assets)
