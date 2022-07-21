cmake_minimum_required(VERSION 3.2.0)  
project(threadpool_example)        

find_package(Threads REQUIRED)
find_package (Eigen3 3.3 REQUIRED  NO_MODULE)

set(TARGET library) # Define a library
set(CMAKE_BUILD_TYPE Debug)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_STANDARD 14)

# Add supporting cpp files of project root directory as source files
set(SOURCE_FILES 
    thread_pool.cpp
    )

# Add source files to library
add_library(${TARGET} STATIC ${SOURCE_FILES})

# Link other libraries to library
target_link_libraries(${TARGET} PUBLIC
        Eigen3::Eigen
        Threads::Threads
        )

# Add executable target 
add_executable(main main.cpp)

# Link library to executable
target_link_libraries( main library )