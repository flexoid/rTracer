cmake_minimum_required (VERSION 2.6)

set(CMAKE_BUILD_TYPE Debug)
#add_definitions(-pg)
#set(CMAKE_EXE_LINKER_FLAGS_DEBUG -pg)


set (PROJECT
    rTracer)

set (SOURCES
    main.cpp

    engine.cpp
    engine.h

    scene.cpp
    scene.h

    sceneparser.cpp
    sceneparser.h

    raytracer.cpp
    raytracer.h

    camera.h
    vector3.h
    ray.h
    light.h
    pixel.h

    screen.h
    screen.cpp

    colorrgb.h
    colorrgb.cpp

    material.h
    math_c.h

    primitives/primitive.h

    primitives/sphere.cpp
    primitives/sphere.h

    primitives/plane.cpp
    primitives/plane.h

    primitives/prism.cpp
    primitives/prism.h

    primitives/texturehplane.cpp
    primitives/texturehplane.h
)

set (EXECUTABLE_OUTPUT_PATH ../bin)

find_package(SDL REQUIRED)

if (NOT SDL_FOUND)
    message(FATAL_ERROR "SDL not found!")
endif (NOT SDL_FOUND)

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-mwindows -static-libgcc -static-libstdc++")
endif (WIN32)

if(NOT CMAKE_BUILD_TYPE EQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif(NOT CMAKE_BUILD_TYPE EQUAL Debug)

add_executable (${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} ${SDL_LIBRARY})
