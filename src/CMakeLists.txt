cmake_minimum_required (VERSION 2.6)

set (PROJECT
    rTracer)

set (SOURCES
    main.cpp

    engine.cpp
    engine.h

    scene.cpp
    scene.h

    raytracer.cpp
    raytracer.h

    vector3.h
    ray.h
    light.h
    colorrgb.h
    material.h
    math_c.h

    primitives/primitive.h

    primitives/sphere.cpp
    primitives/sphere.h)

set (EXECUTABLE_OUTPUT_PATH ../bin)

find_package(SDL REQUIRED)

if (NOT SDL_FOUND)
    message(FATAL_ERROR "SDL not found!")
endif (NOT SDL_FOUND)

add_executable (${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} ${SDL_LIBRARY})
