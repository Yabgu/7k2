cmake_minimum_required (VERSION 3.4.0)
project(7k2 VERSION 1.0
    DESCRIPTION "https://7kfans.com/"
    LANGUAGES CXX)

add_executable(7k2)

file(GLOB 7k2_SRC
    "src/*.cpp"
    "src/imgfun/*.cpp"
)

target_sources(7k2 PRIVATE ${7k2_SRC})

target_include_directories(7k2 PUBLIC include)

# Libraries

find_package(SDL2 REQUIRED)
find_package(OpenAL REQUIRED)
find_package(JPEG REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

target_include_directories(7k2 PUBLIC "${SDL2_INCLUDE_DIRS}/SDL2")
target_include_directories(7k2 PUBLIC ${OPENAL_INCLUDE_DIR})
target_include_directories(7k2 PUBLIC ${JPEG_INCLUDE_DIRS})
target_include_directories(7k2 PUBLIC ${Boost_INCLUDE_DIRS})

target_link_libraries (7k2
    SDL2::SDL2
    enet
    ${OPENAL_LIBRARY}
    ${JPEG_LIBRARIES}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
)

ADD_DEFINITIONS(-DDEBUG -DNO_WINDOWS)
SET(CMAKE_BUILD_TYPE Debug)
