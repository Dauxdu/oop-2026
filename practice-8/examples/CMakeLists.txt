add_library(examples STATIC)
target_sources(examples
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    examples.ixx
    DictionaryExample.cppm
    HashSetExample.cppm
    ListExample.cppm
    QueueExample.cppm
    StackExample.cppm
)

target_link_libraries(examples PUBLIC containers)
