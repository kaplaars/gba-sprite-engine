project(game)

add_executable(${PROJECT_NAME}.elf
        main.cpp
        StartScene.h
        StartScene.cpp
        gbmap.h
        karakter.h
        Menu.cpp
        Menu.h
        Highscore.cpp
        Highscore.h
        SongSelect.cpp
        SongSelect.h
        song1.cpp
        song1.h
        danceroom1.h
        music1.h
        data.h
        data.cpp
        )

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
