cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(RedLib)
add_library(RedLib MemoryTracker.cpp Trackable.cpp Timer.cpp Vector2D.cpp)
