#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "StartScene.h"
#include "Menu.h"
#include "karakter.h"
#include "music1.h"

StartScene::StartScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine){}

std::vector<Sprite *> StartScene::sprites() {
    return {animation.get()};
}

std::vector<Background *> StartScene::backgrounds() {
    return {
            bg.get()
    };
}

void StartScene::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(gbmapPal, sizeof(gbmapPal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(SharedPal, sizeof(SharedPal)));

    engine.get()->enableText();

    bg = std::unique_ptr<Background>(new Background(0, gbmapTiles, sizeof(gbmapTiles), gbmapMap, sizeof(gbmapMap)));
    bg.get()->useMapScreenBlock(24);

    SpriteBuilder<Sprite> builder;

    engine->enqueueMusic(music1, music1_bytes, 96000);

    animation = builder
            .withData(j_germanTiles, sizeof(j_germanTiles))
            .withSize(SIZE_32_32)
            .withAnimated(3, 20)
            .withLocation((GBA_SCREEN_WIDTH/2)-16, (GBA_SCREEN_HEIGHT/2)-16)
            .withinBounds()
            .buildPtr();

    engine->getTimer()->start();

    TextStream::instance().setText("Dance dance revolution" , 1, 4);
    TextStream::instance().setText("Are you ready" , 2, 8);
    TextStream::instance().setText("Press start" , 17, 9);
}

void StartScene::tick(u16 keys) {
    if(keys & KEY_START) {
        engine->setScene(new Menu(engine));
    }
}
