#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "StartScene.h"
#include "SongSelect.h"
#include "Menu.h"
#include "karakter.h"
#include "song1.h"

SongSelect::SongSelect(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> SongSelect::sprites() {
    return {
            animation.get()
    };
}

std::vector<Background *> SongSelect::backgrounds() {
    return {
            bg.get()
    };
}

void SongSelect::tick(u16 keys) {
    //ga terug naar startscene
    if (keys & KEY_L) {
        engine->setScene(new Menu(engine));
    }

    TextStream::instance().setText("Song 1: xxsong namexx", 1, 5);
    TextStream::instance().setText(" Press UP", 2, 9);
    if(keys&KEY_UP){
        engine->setScene(new song1(engine));
    }

    TextStream::instance().setText("Song 2: xxsong namexx", 5, 5);
    TextStream::instance().setText(" Press LEFT", 6, 9);
    if(keys&KEY_LEFT){
        //engine->setScene(new Song2(engine));
    }

    TextStream::instance().setText("Song 3: xxsong namexx", 9, 5);
    TextStream::instance().setText("Press RIGHT", 10, 9);
    if(keys&KEY_RIGHT){
        //engine->setScene(new Song3(engine));
    }
}

void SongSelect::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(gbmapPal, sizeof(gbmapPal)));

    engine.get()->enableText();

    bg = std::unique_ptr<Background>(new Background(1, gbmapTiles, sizeof(gbmapTiles), gbmapMap, sizeof(gbmapMap)));
    bg.get()->useMapScreenBlock(16);

    SpriteBuilder<Sprite> builder;

    animation = builder
            .withData(karakterTiles, sizeof(karakterTiles))
            .withSize(SIZE_32_32)
            .withAnimated(3, 20)
            .withLocation((GBA_SCREEN_WIDTH/2)-16, GBA_SCREEN_HEIGHT-64)
            .withinBounds()
            .buildPtr();
}