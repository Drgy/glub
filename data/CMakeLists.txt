cmake_minimum_required(VERSION 3.15)

project(#[[name]] VERSION #[[version]] DESCRIPTION "#[[description]]" LANGUAGES CXX)

find_package(Git)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    message(STATUS "Updating git submodules...")

    set(SUBMODULES #[[libPaths]])
    set(REPOSITORIES #[[libRepos]])

    foreach(UPD_SUB IN LISTS SUBMODULES)
        message(STATUS "Updating ${UPD_SUB}...")

        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive --remote -- ${UPD_SUB} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} RESULT_VARIABLE GIT_SUBMOD_RESULT)

        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            list(FIND SUBMODULES ${UPD_SUB} SUB_INDEX)
            list(GET REPOSITORIES ${SUB_INDEX} SUB_URL)

            execute_process(COMMAND ${GIT_EXECUTABLE} submodule add ${SUB_URL} ${UPD_SUB} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive -- ${UPD_SUB} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR} RESULT_VARIABLE GIT_SUBMOD_RESULT)

            if(NOT GIT_SUBMOD_RESULT EQUAL "0")
                message(WARNING "Unable to update submodule ${UPD_SUB}")
            endif()
        endif()

    endforeach()
else()
    message(WARNING "Unable to update git submodules, please update them manually.")
endif()
#[[usedLibs]]
#[[libMacros]]
#[[setup]]
if(EXISTS ${PROJECT_SOURCE_DIR}/res)
    message(STATUS "Copying resources...")
    file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
endif()

message(STATUS "Setting up build options...")
set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE SRC_FILES "./src/*.h" "./src/*.cpp")
add_executable(#[[name]] #[[execFiles]])

if(UNIX)
    add_compile_options(-g -O0 -fprofile-arcs -ftest-coverage)
    target_compile_options(#[[name]] PUBLIC -Wall -Wextra -pedantic -lX11 -lGL#[[compileOptions]])
else()
    message(FATAL_ERROR "Detected platform is not supported!")
endif()

message(STATUS "Linking...")
find_package(OpenGL REQUIRED)
target_link_libraries(#[[name]] OpenGL::GL)
#[[linkLibs]]