project(practice-7.2 LANGUAGES CXX)

add_library(UValue STATIC)
target_sources(UValue
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    utils/UValue.cppm
)

add_library(api STATIC)
target_sources(api
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    api/api.ixx
    api/Serializable.cppm
    api/Serializer.cppm
)
target_link_libraries(api PUBLIC UValue)

add_library(serializers STATIC)
target_sources(serializers
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    serializers/serializers.ixx
    serializers/BinarySerializer.cppm
    serializers/JsonSerializer.cppm
    serializers/User.cppm
    serializers/XmlSerializer.cppm

)
target_link_libraries(serializers PUBLIC
    api
    UValue
)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE serializers)
