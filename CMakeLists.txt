cmake_minimum_required (VERSION 2.8.0)
project(p)

set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2")

set (SRCS
    Connectivity
    )
set (TARGETS
    test-dilate-uchar-time
    # test-dilate-ushort
    test-dilate-ushort-time
    test-dilate-ushort-arm
    calc_c_map
    verify-morph-result
    )

find_package(OPENCV)
find_library (YScires NAMES yscires PATHS /usr/local/lib)

foreach (target ${TARGETS})
    add_executable(${target} ${SRCS} ${target}.cpp)
    target_link_libraries(${target} ${OpenCV_LIBS} ${YScires})
endforeach()
