project(oop-2026-labs LANGUAGES CXX)

add_library(console)
target_sources(console
    PUBLIC
    FILE_SET CXX_MODULES
    FILES
    utils/console.cppm
)

include(FetchContent)
fetchcontent_declare(cpp_utils
    GIT_REPOSITORY https://github.com/Dauxdu/cpp-utils-collections.git
    GIT_TAG main
    EXCLUDE_FROM_ALL
)
fetchcontent_makeavailable(cpp_utils)


find_package(GTest QUIET)
if(NOT GTEST_FOUND)
    include(FetchContent)
    fetchcontent_declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
        EXCLUDE_FROM_ALL
    )
    fetchcontent_makeavailable(googletest)
endif()
enable_testing()

find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    file(GLOB LAB_DIRS "${CMAKE_SOURCE_DIR}/lab-*")

    set(DOXYGEN_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/docs")
    set(DOXYGEN_RECURSIVE YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_EXCLUDE_PATTERNS "*/test/*")
    set(DOXYGEN_FILE_PATTERNS "*.cpp" "*.cppm")

    doxygen_add_docs(docs ${LAB_DIRS})
endif()

add_subdirectory("lab-1")
add_subdirectory("lab-2")
add_subdirectory("lab-3")
add_subdirectory("lab-4")
add_subdirectory("lab-5")
