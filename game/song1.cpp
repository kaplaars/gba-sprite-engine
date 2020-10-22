#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "karakter.h"
#include "SongSelect.h"
#include "song1.h"
#include "StartScene.h"
#include "danceroom1.h"

song1::song1(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> song1::sprites() {
    return {animation.get()};
}

std::vector<Background *> song1::backgrounds() {
    return {
            bg.get()
    };
}

void song1::tick(u16 keys) {
//ga terug naar startscene
    if (keys & KEY_R) {
        engine->setScene(new SongSelect(engine));
    }
}

void song1::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(gbmapPal, sizeof(gbmapPal)));

    engine.get()->enableText();

    bg = std::unique_ptr<Background>(new Background(1, gbmapTiles, sizeof(gbmapTiles), gbmapMap, sizeof(gbmapMap)));
    bg.get()->useMapScreenBlock(16);

    SpriteBuilder<Sprite> builder;

    animation = builder
            .withData(bokmanTiles, sizeof(bokmanTiles))
            .withSize(SIZE_32_32)
            .withAnimated(3, 20)
            .withLocation((GBA_SCREEN_WIDTH/2)-16, GBA_SCREEN_HEIGHT-64)
            .withinBounds()
            .buildPtr();
}