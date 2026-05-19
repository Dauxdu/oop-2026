add_library(simple_usages STATIC)
target_sources(simple_usages
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    simple_usages.ixx
    DictionaryUsages.cppm
)

target_link_libraries(simple_usages PUBLIC containers)