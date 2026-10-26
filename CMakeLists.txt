cmake_minimum_required(VERSION 4.1)
project(CS455_RayTracer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")

add_executable(CS455_RayTracer main.cpp
        Vec3.h
        Ray.h
        Sphere.h
        Material.h
        Plane.h
        Polygon.h
        Object3D.h
        Triangle.h
)
