add_library(api STATIC)
target_sources(api
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    api.ixx
    serializable.cppm
    serializer.cppm
)
target_link_libraries(api PUBLIC universal_value)