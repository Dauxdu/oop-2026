add_library(implementations STATIC)
target_sources(implementations
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    implementations.ixx
    json_serializer.cppm
    xml_serializer.cppm
    binary_serializer.cppm
    user.cppm
)
target_link_libraries(implementations PUBLIC api)