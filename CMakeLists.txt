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
        src/objects/Enemy.cpp
        src/objects/Enemy.h
        src/components/BombermanGame.cpp
        src/components/BombermanGame.h
        src/render/Renderer.cpp
        src/render/Renderer.h
        src/render/Sprite.cpp
        src/render/Sprite.h
        src/render/Transform.h
        src/Constants.h
        src/objects/Enemy.cpp
        src/objects/Enemy.h
        src/objects/Bomb.cpp
        src/objects/Bomb.h
        src/objects/BombExplosion.cpp
        src/objects/BombExplosion.h
        src/pages/MainMenuPage.cpp
        src/pages/MainMenuPage.h
        src/pages/AboutPage.cpp
        src/pages/AboutPage.h
        src/pages/GamePage.cpp
        src/pages/GamePage.h
        src/components/HudDisplay.cpp
        src/components/HudDisplay.h
        src/render/AnimatedSprite.cpp
        src/render/AnimatedSprite.h
)
target_link_libraries(projekt ${wxWidgets_LIBRARIES})

IF(WIN32)
    target_sources(projekt PRIVATE resource.rc)
    set_target_properties(projekt PROPERTIES WIN32_EXECUTABLE TRUE)
    add_custom_command(
        TARGET projekt POST_BUILD
        COMMAND bash copydlls "$<TARGET_FILE:projekt>"
    )
    get_filename_component(CMAKE_BIN_DIR "${CMAKE_COMMAND}" DIRECTORY)
    add_custom_command(
        TARGET projekt POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:projekt>/share/glib-2.0/schemas"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BIN_DIR}/../share/glib-2.0/schemas/gschemas.compiled"
                "$<TARGET_FILE_DIR:projekt>/share/glib-2.0/schemas/gschemas.compiled"
    )
ENDIF()

add_custom_command(
    TARGET projekt POST_BUILD
    COMMAND ${CMAKE_COMMAND}
    ARGS -E copy_directory_if_different "${PROJECT_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:projekt>/assets"
)

install(TARGETS projekt RUNTIME DESTINATION bin)
