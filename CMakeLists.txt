cmake_minimum_required(VERSION 3.9)

message("#### variables ####")

# https://stackoverflow.com/questions/9298278/cmake-print-out-all-accessible-variables-in-a-script
get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach()

# https://stackoverflow.com/questions/32183975/how-to-print-all-the-properties-of-a-target-in-cmake

# Get all propreties that cmake supports
execute_process(COMMAND cmake --help-property-list OUTPUT_VARIABLE CMAKE_PROPERTY_LIST)

# Convert command output into a CMake list
STRING(REGEX REPLACE ";" "\\\\;" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
STRING(REGEX REPLACE "\n" ";" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")

function(print_properties)
    message ("CMAKE_PROPERTY_LIST = ${CMAKE_PROPERTY_LIST}")
endfunction(print_properties)

function(print_target_properties tgt)
    if(NOT TARGET ${tgt})
      message("There is no target named '${tgt}'")
      return()
    endif()

    foreach (prop ${CMAKE_PROPERTY_LIST})
        string(REPLACE "<CONFIG>" "${CMAKE_BUILD_TYPE}" prop ${prop})
    # Fix https://stackoverflow.com/questions/32197663/how-can-i-remove-the-the-location-property-may-not-be-read-from-target-error-i
    if(prop STREQUAL "LOCATION" OR prop MATCHES "^LOCATION_" OR prop MATCHES "_LOCATION$")
        continue()
    endif()
        # message ("Checking ${prop}")
        get_property(propval TARGET ${tgt} PROPERTY ${prop} SET)
        if (propval)
            get_target_property(propval ${tgt} ${prop})
            message ("${tgt} ${prop} = ${propval}")
        endif()
    endforeach(prop)
endfunction(print_target_properties)

add_executable(threadcancel threadcancel.cpp)
target_link_libraries(threadcancel pthread)

message("#### properties ####")
print_target_properties(threadcancel)

#[[
[kanda@f25 build]$ cmake -G Ninja ..
#### variables ####
-- CMAKE_AR=/usr/bin/ar
-- CMAKE_INSTALL_PREFIX=/usr/local

#### properties ####
threadcancel BINARY_DIR = /home/kanda/git/cppsample/build
threadcancel INTERFACE_LINK_LIBRARIES = pthread
threadcancel LINK_LIBRARIES = pthread
threadcancel NAME = threadcancel
]]
