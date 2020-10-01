#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "StartScene.h"
#include "Highscore.h"
#include "Menu.h"
#include "karakter.h"

Highscore::Highscore(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> Highscore::sprites() {
    return {
    };
}

std::vector<Background *> Highscore::backgrounds() {
    return {
            bg.get()
    };
}

void Highscore::tick(u16 keys) {
    //ga terug naar startscene
    if (keys & KEY_L) {
        engine->setScene(new Menu(engine));
    }

    TextStream::instance().setText("Song 1:", 4, 11);
    //TextStream::instance().setText(score1, 5, 4);
    TextStream::instance().setText("Song 2:", 8, 11);
    //TextStream::instance().setText(score2, 9, 6);
    TextStream::instance().setText("Song 3:", 12, 11);
    //TextStream::instance().setText(score3, 13, 6);

}

void Highscore::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(gbmapPal, sizeof(gbmapPal)));

    engine.get()->enableText();

    bg = std::unique_ptr<Background>(new Background(1, gbmapTiles, sizeof(gbmapTiles), gbmapMap, sizeof(gbmapMap)));
    bg.get()->useMapScreenBlock(16);

    SpriteBuilder<Sprite> builder;

}