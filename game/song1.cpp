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
    return {};
}

std::vector<Background *> song1::backgrounds() {
    return {
            bg.get()
    };
}

void song1::tick(u16 keys) {
    //ga terug naar startscene
    if (keys & KEY_SELECT) {
        engine->setScene(new StartScene(engine));
    }
}

void song1::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager( danceroom1Pal, sizeof( danceroom1Pal)));

    engine.get()->enableText();



    bg = std::unique_ptr<Background>(new Background(1,  danceroom1Tiles, sizeof( danceroom1Tiles), danceroom1Map, sizeof( danceroom1Map)));
    bg.get()->useMapScreenBlock(16);

    TextStream::instance().clear();

    SpriteBuilder<Sprite> builder;

}