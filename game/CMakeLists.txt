project(game)

add_executable(${PROJECT_NAME}.elf
        main.cpp
        StartScene.h
        StartScene.cpp
        gbmap.h
        karakter.h
        Menu.cpp
        Menu.h
        )

target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
