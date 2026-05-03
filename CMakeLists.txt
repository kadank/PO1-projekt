cmake_minimum_required(VERSION 4.1)
project(projekt)

set(CMAKE_CXX_STANDARD 20)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()

add_executable(projekt src/main.cpp
        src/Board.cpp
        src/Board.h
        src/objects/Tile.cpp
        src/objects/Tile.h
        src/objects/Object.cpp
        src/objects/Object.h
        src/utils/Vector.cpp
        src/utils/Vector.h
        src/objects/Player.cpp
        src/objects/Player.h
        src/render/BombermanCanvas.cpp
        src/render/BombermanCanvas.h
)
target_link_libraries(projekt ${wxWidgets_LIBRARIES})

IF(WIN32)
    if(CMAKE_CROSSCOMPILING)
        file(GLOB MINGW_DLLS "/usr/x86_64-w64-mingw32/bin/*.dll")
    else()
        set(MINGW_DLLS "")
    endif()
    add_custom_command(TARGET projekt POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${MINGW_DLLS}
            $<TARGET_FILE_DIR:projekt>
    )
    target_sources(projekt PRIVATE resource.rc)
ENDIF()