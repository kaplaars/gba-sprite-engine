#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "StartScene.h"
#include "Menu.h"
#include "karakter.h"

Menu::Menu(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> Menu::sprites() {
    return {
    };
}

std::vector<Background *> Menu::backgrounds() {
    return {
            bg.get()
    };
}

void Menu::tick(u16 keys) {
    //ga terug naar startscene
    if (keys & KEY_SELECT) {
        engine->setScene(new StartScene(engine));
    }

    TextStream::instance().setText("Press A ", 4, 11);
    TextStream::instance().setText("to select a character", 5, 4);
    TextStream::instance().setText("Press B", 8, 11);
    TextStream::instance().setText("to select a song", 9, 6);
    TextStream::instance().setText("Press R", 12, 11);
    TextStream::instance().setText("to see highscores", 13, 6);
    if (keys & KEY_A) {
        // go to character select
        engine->setScene(new StartScene(engine));
    } else if (keys & KEY_B) {
        // go to song select
        engine->setScene(new StartScene(engine));
    } else if (keys & KEY_R) {
        // go to highscore view
        engine->setScene(new StartScene(engine));
    }


}

void Menu::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(gbmapPal, sizeof(gbmapPal)));

    engine.get()->enableText();

    bg = std::unique_ptr<Background>(new Background(1, gbmapTiles, sizeof(gbmapTiles), gbmapMap, sizeof(gbmapMap)));
    bg.get()->useMapScreenBlock(16);

    SpriteBuilder<Sprite> builder;

}