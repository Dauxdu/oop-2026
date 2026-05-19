add_library(containers STATIC)
target_sources(containers
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    containers.ixx
    Dictionary.cppm
    HashSet.cppm
    List.cppm
    Queue.cppm
    Stack.cppm
)

target_link_libraries(containers PUBLIC enumerators)
