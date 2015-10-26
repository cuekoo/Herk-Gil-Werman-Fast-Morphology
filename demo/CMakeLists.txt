cmake_minimum_required (VERSION 2.8.0)
project(p)

set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2")

set (TARGETS
    compareEfficiencyWithOpenCV
    erodeImage
    )

find_package(OpenCV REQUIRED)

foreach (target ${TARGETS})
    add_executable(${target} ${target}.cpp)
    target_link_libraries(${target} ${OpenCV_LIBS})
    install(TARGETS ${target} DESTINATION bin)
endforeach()


