add_library(enumerators STATIC)
target_sources(enumerators
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    enumerators.ixx
    DictionaryEnumerator.cppm
    StackEnumerator.cppm
    ListEnumerator.cppm
)

target_link_libraries(enumerators PUBLIC interfaces)
