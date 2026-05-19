add_library(interfaces STATIC)
target_sources(interfaces
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    interfaces.ixx
    IEnumerator.cppm
    IEnumerable.cppm
    ICollection.cppm
)