cmake_minimum_required(VERSION 3.4.1)

add_library(
             native-lib
             SHARED
             src/main/cpp/native-lib.cpp
             src/main/cpp/rgbtopng.cpp
              )
add_library(
             bitmap
             SHARED
             IMPORTED)

find_library(
              log-lib
              log )
set_target_properties(
            bitmap
            PROPERTIES IMPORTED_LOCATION
            ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI}/libbitmap.so
           )

target_link_libraries(
                       native-lib
                       bitmap
                       ${log-lib} )