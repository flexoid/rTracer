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
    primitives/sphere.h)

set (EXECUTABLE_OUTPUT_PATH ../bin)

find_package(SDL REQUIRED)

if (NOT SDL_FOUND)
    message(FATAL_ERROR "SDL not found!")
endif (NOT SDL_FOUND)

add_executable (${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} ${SDL_LIBRARY})
