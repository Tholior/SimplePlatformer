cmake_minimum_required(VERSION 3.30)
project(SimplePlatformer)

set(CMAKE_CXX_STANDARD 20)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    endif()
endif()

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

add_executable(SimplePlatformer main.cpp
        src/game.cpp
        include/game.hpp
        src/player.cpp
        include/player.hpp
        src/levels.cpp
        include/levels.hpp
        src/menu.cpp
        include/menu.hpp
        include/gamestate.hpp
        src/enemy.cpp
        include/enemy.hpp
)

target_link_libraries(${PROJECT_NAME} raylib)