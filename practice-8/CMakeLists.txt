project(practice-8 LANGUAGES CXX)

add_library(interfaces STATIC)
target_sources(interfaces
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    interfaces/interfaces.ixx
    interfaces/IEnumerator.cppm
    interfaces/IEnumerable.cppm
    interfaces/ICollection.cppm
)

add_library(containers STATIC)
target_sources(containers
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    containers/containers.ixx
    containers/Dictionary.cppm
    containers/HashSet.cppm
    containers/List.cppm
    containers/Queue.cppm
    containers/Stack.cppm
)
target_link_libraries(containers PUBLIC interfaces)

add_library(examples STATIC)
target_sources(examples
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    examples/examples.ixx
    examples/DictionaryExample.cppm
    examples/HashSetExample.cppm
    examples/ListExample.cppm
    examples/QueueExample.cppm
    examples/StackExample.cppm
)
target_link_libraries(examples PUBLIC containers)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE examples)
