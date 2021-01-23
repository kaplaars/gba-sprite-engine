#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "StartScene.h"
#include "Highscore.h"
#include "Menu.h"
#include "karakter.h"
#include "data.h"
#include "music1.h"

extern data data1;

Highscore::Highscore(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> Highscore::sprites() {
    return {
            animation.get()
    };
}

std::vector<Background *> Highscore::backgrounds() {
    return {
            bg.get()
    };
}

void Highscore::tick(u16 keys) {
    //ga terug naar startscene
    if (keys & KEY_R) {
        engine->setScene(new Menu(engine));
    }

    TextStream::instance().setText("Song 1:", 1, 11);
    TextStream::instance().setText(std::to_string(data1.getTopScore1()), 2, 13);
    TextStream::instance().setText("Song 2:", 5, 11);
    TextStream::instance().setText(std::to_string(data1.getTopScore2()), 6, 13);
    TextStream::instance().setText("Song 3:", 9, 11);
    TextStream::instance().setText(std::to_string(data1.getTopScore3()), 10, 13);

}

void Highscore::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(SharedPal, sizeof(SharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(gbmapPal, sizeof(gbmapPal)));

    engine.get()->enableText();

    bg = std::unique_ptr<Background>(new Background(1, gbmapTiles, sizeof(gbmapTiles), gbmapMap, sizeof(gbmapMap)));
    bg.get()->useMapScreenBlock(16);

    SpriteBuilder<Sprite> builder;

    engine->enqueueMusic(music1, music1_bytes, 96000);

    animation = builder
            .withData(safmanTiles, sizeof(safmanTiles))
            .withSize(SIZE_32_32)
            .withAnimated(3, 20)
            .withLocation((GBA_SCREEN_WIDTH/2)-16, GBA_SCREEN_HEIGHT-64)
            .withinBounds()
            .buildPtr();
}