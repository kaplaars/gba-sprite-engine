#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "danceroom1.h"
#include "karakter.h"
#include "song2.h"
#include "SongSelect.h"

song2::song2(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> song2::sprites() {
    return {
            animation.get()
    };
}

std::vector<Background *> song2::backgrounds() {
    return {
            bg.get()
    };
}

void song2::tick(u16 keys) {
//ga terug naar startscene
    if (keys & KEY_R) {
        engine->setScene(new SongSelect(engine));
    }
}

void song2::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(danceroom1Pal, sizeof(danceroom1Pal)));

    engine.get()->enableText();

    bg = std::unique_ptr<Background>(new Background(1, danceroom1Tiles, sizeof(danceroom1Tiles), danceroom1Map, sizeof(danceroom1Map)));
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