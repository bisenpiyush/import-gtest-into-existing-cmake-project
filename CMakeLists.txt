cmake_minimum_required (VERSION 3.2.2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

project (HelloWorld)

message("########################gtest download and build as external project##################")
#--- This approach has been suggested by Gtest itself--
set(GOOGLETEXT_DOWNLOAD_DIR ${CMAKE_SOURCE_DIR}/Packages)
# Download and unpack googletest at configure time
configure_file(${GOOGLETEXT_DOWNLOAD_DIR}/CMakeLists.txt.in ${GOOGLETEXT_DOWNLOAD_DIR}/googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}"
    .
    RESULT_VARIABLE result
    #-D "CMAKE_MAKE_PROGRAM:FILE=${CMAKE_MAKE_PROGRAM}"
    WORKING_DIRECTORY "${GOOGLETEXT_DOWNLOAD_DIR}/googletest-download"
)
#    if(result)
#     message(FATAL_ERROR "CMake step for googletest failed: ${result}")
#    endif()
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY "${GOOGLETEXT_DOWNLOAD_DIR}/googletest-download"
)
#    if(result)
#        message(FATAL_ERROR "Build step for googletest failed: ${result}")
#    endif()
# Prevent GoogleTest from overriding our compiler/linker options
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory("${GOOGLETEXT_DOWNLOAD_DIR}/googletest-src"
                 "${GOOGLETEXT_DOWNLOAD_DIR}/googletest-build"
                EXCLUDE_FROM_ALL)
message("############################################")
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE PMHEADERS ${CMAKE_SOURCE_DIR}/include/*.h)

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/x86)
message("###############Qt part###################")
#Please change the Qt as per your machine location
set(QT_VERSION_REQ 5.15.2)
SET(PATH "~/Qt/5.15.2/gcc_64/lib/cmake")
find_package(Qt5Core ${QT_VERSION_REQ} REQUIRED PATHS ${PATH} )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
QT5_WRAP_CPP(MOC_HEADERS ${PMHEADERS})

add_executable(${PROJECT_NAME} ${SOURCES} ${MOC_HEADERS} HelloWorld.cpp)

#add_executable(HelloWorld HelloWorld.cpp)
add_library(HelloWorldLib OBJECT ${SOURCES} ${MOC_HEADERS})

############################# Add test cpp here ###################
file(GLOB_RECURSE TESTSOURCES ${CMAKE_SOURCE_DIR}/UnitTest/*.cpp)
add_executable(UnitTestExe ${TESTSOURCES} $<TARGET_OBJECTS:HelloWorldLib> )
############################################################
target_link_libraries(${PROJECT_NAME}
    Qt5::Core)

target_link_libraries(HelloWorldLib
    Qt5::Core)

target_link_libraries(UnitTestExe
    Qt5::Core
    gtest_main
    gmock_main)

add_test(NAME unit_test COMMAND UnitTestExe)
 
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_BINARY_DIR})
install(TARGETS UnitTestExe RUNTIME DESTINATION ${CMAKE_BINARY_DIR})
