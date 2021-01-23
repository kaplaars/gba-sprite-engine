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
#include "data.h"
#include "music1.h"

extern data data1;

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
    if (keys & KEY_R) {
        engine->setScene(new Menu(engine));
    }

    TextStream::instance().setText("Song 1: Death of the C++", 1, 5);
    TextStream::instance().setText(" Press UP", 2, 9);
    TextStream::instance().setText("Song 2: Caremella dance", 5, 5);
    TextStream::instance().setText(" Press LEFT", 6, 9);
    TextStream::instance().setText("Song 3: ADHD on cocain", 9, 5);
    TextStream::instance().setText("Press RIGHT", 10, 9);

    if(keys & KEY_UP||keys & KEY_RIGHT||keys & KEY_LEFT) {
        if (keys & KEY_UP) {
            data1.setSpeed(16000);
            data1.setFallSpeed(1);
        } else if (keys & KEY_LEFT) {
            data1.setSpeed(96000);
            data1.setFallSpeed(2);
        } else if (keys & KEY_RIGHT) {
            data1.setSpeed(512000);
            data1.setFallSpeed(3);
        }
        engine->setScene(new song1(engine));
    }
}

void SongSelect::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(SharedPal, sizeof(SharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(gbmapPal, sizeof(gbmapPal)));

    engine.get()->enableText();

    bg = std::unique_ptr<Background>(new Background(1, gbmapTiles, sizeof(gbmapTiles), gbmapMap, sizeof(gbmapMap)));
    bg.get()->useMapScreenBlock(16);

    SpriteBuilder<Sprite> builder;

    engine->enqueueMusic(music1, music1_bytes, 96000);

    animation = builder
            .withData(nederlandmanTiles, sizeof(nederlandmanTiles))
            .withSize(SIZE_32_32)
            .withAnimated(3, 20)
            .withLocation((GBA_SCREEN_WIDTH/2)-16, GBA_SCREEN_HEIGHT-64)
            .withinBounds()
            .buildPtr();
}