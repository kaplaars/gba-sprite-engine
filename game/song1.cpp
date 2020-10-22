#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "karakter.h"
#include "SongSelect.h"
#include "song1.h"
#include "danceroom1.h"

song1::song1(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> song1::sprites() {
    return {animation.get(),
            buttons.get()};
}

std::vector<Background *> song1::backgrounds() {
    return {
            bg.get()
    };
}

void song1::tick(u16 keys) {
    //moving and generating the buttons
    if(buttons->isOffScreen()) {
        int frame=rand()%5;
        buttons->animateToFrame(frame);
        //buttons->animateToFrame(0);
        TextStream::instance().setText("frame:", 3, 1);
        TextStream::instance().setText(std::to_string(frame), 4, 1);
        buttons->moveTo((GBA_SCREEN_WIDTH/2)-16,0);
    }else{
        buttons->setVelocity(0, 1);
    }

    //points detection
    if(buttons->getY()>=50 && buttons->getY() <= 100){
        if(keys & KEY_B && buttons->getCurrentFrame() == 0){
            score1+=50;
        }else if(keys & KEY_A && buttons->getCurrentFrame() == 1){
            score1+=50;
        }else if(keys & KEY_LEFT && buttons->getCurrentFrame() == 2){
            score1+=50;
        }else if(keys & KEY_DOWN && buttons->getCurrentFrame() == 3){
            score1+=50;
        }else if(keys & KEY_RIGHT && buttons->getCurrentFrame() == 4){
            score1+=50;
        }else if(keys & KEY_UP && buttons->getCurrentFrame() == 5){
            score1+=50;
        }
        TextStream::instance().setText("score:", 1, 1);
        TextStream::instance().setText(std::to_string(score1), 2, 1);
    }

}

void song1::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(danceroom1Pal, sizeof(danceroom1Pal)));

    engine.get()->enableText();

    bg = std::unique_ptr<Background>(new Background(1, danceroom1Tiles, sizeof(danceroom1Tiles), danceroom1Map, sizeof(danceroom1Map)));
    bg.get()->useMapScreenBlock(16);

    SpriteBuilder<Sprite> builder;

    buttons = builder
            .withData(buttonsTiles, sizeof(buttonsTiles))
            .withSize(SIZE_32_32)
            .withLocation((GBA_SCREEN_WIDTH/2)-16, 0)
            .buildPtr();

    animation = builder
            .withData(bokmanTiles, sizeof(bokmanTiles))
            .withSize(SIZE_32_32)
            .withAnimated(3, 20)
            .withLocation((GBA_SCREEN_WIDTH/4)-16, GBA_SCREEN_HEIGHT-64)
            .withinBounds()
            .buildPtr();

    score1 = 0;
}