cmake_minimum_required(VERSION 3.20)
project(magazyn)

set(CMAKE_CXX_STANDARD 17)

add_executable(magazyn
    main.cpp
    App.cpp
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_impl_sdl2.cpp
    imgui_impl_opengl3.cpp
)

target_include_directories(magazyn PRIVATE
    ${CMAKE_SOURCE_DIR}
    C:/SDL2/include/SDL2
)

target_link_directories(magazyn PRIVATE C:/SDL2/lib)

target_link_libraries(magazyn
    PRIVATE mingw32 SDL2main SDL2 opengl32
)