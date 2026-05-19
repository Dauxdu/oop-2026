project("practice-8" LANGUAGES CXX)

add_library(interface STATIC)
target_sources(interface
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    interfaces/interface.ixx
    interfaces/ICollection.cppm
    interfaces/IEnumerable.cppm
    interfaces/IEnumerator.cppm
)

add_library(collections STATIC)
target_sources(collections
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    collections/collections.ixx
    collections/Dictionary.cppm
    collections/HashSet.cppm
    collections/List.cppm
    collections/Queue.cppm
    collections/Stack.cppm
)
target_link_libraries(collections PUBLIC interface)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    collections
)
