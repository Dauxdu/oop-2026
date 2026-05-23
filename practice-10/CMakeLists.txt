project("practice-9" LANGUAGES CXX)

set(SFML_COMPONENTS "Graphics")
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  list(APPEND SFML_COMPONENTS "Main")
endif()

find_package("SFML" COMPONENTS ${SFML_COMPONENTS} CONFIG REQUIRED)

add_custom_target(copy_assets
  COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
  ${CMAKE_CURRENT_SOURCE_DIR}/assets
  ${CMAKE_CURRENT_BINARY_DIR}/assets
)

add_executable(${PROJECT_NAME})
add_dependencies(${PROJECT_NAME} copy_assets)
target_link_libraries(${PROJECT_NAME} PRIVATE "SFML::Graphics")
target_sources(${PROJECT_NAME}
  PRIVATE
  "main.cpp"
  "spiral.cpp"
  PRIVATE FILE_SET "modules" TYPE CXX_MODULES FILES
  "api.cppm"
  "spiral.cppm"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE TRUE)
  target_link_libraries(${PROJECT_NAME} PRIVATE "SFML::Main")
endif()
