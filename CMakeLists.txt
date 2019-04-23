cmake_minimum_required(VERSION 3.7) # first version with add_compile_options()
project(MFRC522)

message (STATUS "CMake version: ${CMAKE_VERSION}")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# then Compiler/IDE differences:

set(CPPCHECK_ARG_TEMPLATE   "--template=gcc")
# Useful compile flags and extra warnings
add_compile_options(-fstack-protector -Wall -Wextra -Wpedantic -Wno-long-long -Wswitch-enum -Wshadow -Winline)
if (CMAKE_COMPILER_IS_GNUCXX)
    # GCC flags
    if (MFRC522_USE_GCOV AND CMAKE_COMPILER_IS_GNUCXX)
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
            message (STATUS "Using GCov instrumentation")
        else ()
            message (WARNING "GCov instrumentation works best in Debug mode")
        endif ()
        add_compile_options (-coverage) # NOTE would be usefull but not working with current google test and gcc 4.8 -fkeep-inline-functions
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage")
    endif ()
endif (CMAKE_COMPILER_IS_GNUCXX)

# and then common variables
set(CPPLINT_ARG_VERBOSE "--verbose=3")
set(CPPLINT_ARG_LINELENGTH "--linelength=120")

# Print CXX compiler information
message (STATUS "CMAKE_CXX_COMPILER '${CMAKE_CXX_COMPILER}' '${CMAKE_CXX_COMPILER_ID}' '${CMAKE_CXX_COMPILER_VERSION}'")

# Print CXX FLAGS
message (STATUS "CMAKE_CXX_FLAGS                '${CMAKE_CXX_FLAGS}'")
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    message (STATUS "CMAKE_CXX_FLAGS_DEBUG          '${CMAKE_CXX_FLAGS_DEBUG}'")
elseif (CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
    message (STATUS "CMAKE_CXX_FLAGS_RELWITHDEBINFO '${CMAKE_CXX_FLAGS_RELWITHDEBINFO}'")
elseif (CMAKE_BUILD_TYPE STREQUAL MinSizeRel)
    message (STATUS "CMAKE_CXX_FLAGS_MINSIZEREL     '${CMAKE_CXX_FLAGS_MINSIZEREL}'")
else ()
    message (STATUS "CMAKE_CXX_FLAGS_RELEASE        '${CMAKE_CXX_FLAGS_RELEASE}'")
endif ()


## Build the C++ Wrapper ##

# adding a new file require explicittly modifing the CMakeLists.txt
# so that CMake knows that it should rebuild the project (it is best practice)

# list of sources files of the library
set(MFRC522_SRC
    ${PROJECT_SOURCE_DIR}/src/MFRC522Extended.cpp
    ${PROJECT_SOURCE_DIR}/src/MFRC522.cpp
    ${PROJECT_SOURCE_DIR}/src/SPI.cpp
    ${PROJECT_SOURCE_DIR}/src/Serial.cpp
)

source_group(src FILES ${MFRC522_SRC})

# list of header files of the library
set(MFRC522_INC
    ${PROJECT_SOURCE_DIR}/src/MFRC522.h
    ${PROJECT_SOURCE_DIR}/src/MFRC522Extended.h
    ${PROJECT_SOURCE_DIR}/src/require_cpp11.h
)
source_group(include FILES ${MFRC522_INC})

# list of test files of the library
# set(MFRC522_TESTS
#  test/MFRC522_test.cpp
# )
# source_group(tests FILES ${MFRC522_TESTS})

# list of example files of the library
# set(MFRC522_AUTH_READ_WRITE
#   examples/auth_read_write/auth_read_write.cpp
# )
# source_group(auth_read_write FILES ${MFRC522_AUTH_READ_WRITE})

set(MFRC522_FIRMWARE_CHECK
${PROJECT_SOURCE_DIR}/examples/firmware_check/firmware_check.cpp
)
source_group(firmware_check FILES ${MFRC522_FIRMWARE_CHECK})



# list of script files of the library
set(MFRC522_SCRIPT
  build.sh
)
source_group(scripts FILES ${MFRC522_SCRIPT})

# All includes are relative to the "include" directory
include_directories("${PROJECT_SOURCE_DIR}/include")

# add sources 
add_library(mfrc522 ${MFRC522_SRC} ${MFRC522_INC} ${MFRC522_SCRIPT})

if (UNIX AND NOT APPLE)
    target_link_libraries(mfrc522 wiringPi)
endif(UNIX AND NOT APPLE)


option(MFRC522_RUN_CPPCHECK "Run cppcheck C++ static analysis tool." ON)
if (MFRC522_RUN_CPPCHECK)
    find_program(CPPCHECK_EXECUTABLE NAMES cppcheck)
    if (CPPCHECK_EXECUTABLE)
        # add a cppcheck target to the "all" target
        add_custom_target(MFRC522_cppcheck
         ALL
         COMMAND ${CPPCHECK_EXECUTABLE} -j 8 cppcheck --enable=style --quiet ${CPPCHECK_ARG_TEMPLATE} ${PROJECT_SOURCE_DIR}/src
        )
        execute_process(COMMAND "${CPPCHECK_EXECUTABLE}" --version OUTPUT_VARIABLE CPPCHECK_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
        message(STATUS "Found Cppcheck: ${CPPCHECK_EXECUTABLE} ${CPPCHECK_VERSION}")
    else (CPPCHECK_EXECUTABLE)
        message(STATUS "Could NOT find cppcheck")
    endif (CPPCHECK_EXECUTABLE)
else (MFRC522_RUN_CPPCHECK)
    message(STATUS "MFRC522_RUN_CPPCHECK OFF")
endif (MFRC522_RUN_CPPCHECK)


option(MFRC522_BUILD_EXAMPLES "Build examples." OFF)
if (MFRC522_BUILD_EXAMPLES)
    # add the basic example executable

    add_executable(MFRC522_firmware_check ${MFRC522_FIRMWARE_CHECK})
    target_link_libraries(MFRC522_firmware_check mfrc522 )
    target_include_directories(MFRC522_firmware_check PUBLIC ${PROJECT_SOURCE_DIR}/src)

    # Link target with pthread and dl for linux
    # if (UNIX)
    #     target_link_libraries(MFRC522_example1 pthread)
    #     if (NOT APPLE)
    #         target_link_libraries(MFRC522_example1 dl)
    #     endif ()
    # elseif (MSYS OR MINGW)
    #     target_link_libraries(MFRC522_example1 ssp)
    # endif ()
else (MFRC522_BUILD_EXAMPLES)
    message(STATUS "MFRC522_BUILD_EXAMPLES OFF")
endif (MFRC522_BUILD_EXAMPLES)
