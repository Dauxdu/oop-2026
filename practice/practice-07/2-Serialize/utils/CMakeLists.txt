add_library(universal_value STATIC)
target_sources(universal_value
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    universal_value.cppm
)