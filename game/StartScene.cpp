#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "StartScene.h"

#include "karakter.h"

#include "gbmap.h"

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
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));

    engine.get()->enableText();

    bg = std::unique_ptr<Background>(new Background(0, gbmapTiles, sizeof(gbmapTiles), gbmapMap, sizeof(gbmapMap)));
    bg.get()->useMapScreenBlock(24);

    SpriteBuilder<Sprite> builder;

    animation = builder
            .withData(karakterTiles, sizeof(karakterTiles))
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

}
