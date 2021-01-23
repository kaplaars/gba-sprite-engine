#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "karakter.h"
#include "SongSelect.h"
#include "song1.h"
#include "danceroom1.h"
#include "Menu.h"
#include "music1.h"
#include "data.h"
extern data data1;

song1::song1(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> song1::sprites() {
    return {animation.get(),
            animation2.get(),
            animation3.get(),
            animation4.get(),
            buttons.get()};
}

std::vector<Background *> song1::backgrounds() {
    return {
            bg.get()
    };
}

void song1::tick(u16 keys) {
//ga terug naar startscene
    if (keys & KEY_R) {
        engine->setScene(new Menu(engine));
    }
    //topscore timer
    if(engine->getTimer()->getMinutes()>=1){
        if(data1.getFallSpeed()==1 && data1.getTopScore1()<score1){
            data1.setTopScore1(score1);
        }else if(data1.getFallSpeed()==2 && data1.getTopScore1()<score1){
            data1.setTopScore2(score1);
        }else if(data1.getFallSpeed()==3 && data1.getTopScore1()<score1){
            data1.setTopScore3(score1);
        }
        engine->setScene(new Menu(engine));
    }

    TextStream::instance().setText("score:", 1, 1);
    TextStream::instance().setText(std::to_string(score1), 2, 1);
    TextStream::instance().setText(std::to_string((engine->getTimer()->getSecs())),3,1);

    //moving and generating the buttons
    if(buttons->isOffScreen()) {
        int frame=(rand()%6)+6;
        buttons->animateToFrame(frame);
        buttons->moveTo((GBA_SCREEN_WIDTH/2)-16,0);
        pressed = 0;
    }else{
        buttons->setVelocity(0, data1.getFallSpeed());
    }

    //y pos checker
    /*TextStream::instance().setText("Y-position:", 3, 1);
    TextStream::instance().setText(std::to_string(buttons->getY()), 4, 1);*/

    //points detection
    if(buttons->getY()>=60 && buttons->getY() <= 75 && pressed == 0){
        if(keys & KEY_B && buttons->getCurrentFrame() == 6){
            score1+=buttons->getY();
            pressed = 1;
        }else if(keys & KEY_A && buttons->getCurrentFrame() == 7){
            score1+=buttons->getY();
            pressed = 1;
        }else if(keys & KEY_LEFT && buttons->getCurrentFrame() == 8){
            score1+=buttons->getY();
            pressed = 1;
        }else if(keys & KEY_DOWN && buttons->getCurrentFrame() == 9){
            score1+=buttons->getY();
            pressed = 1;
        }else if(keys & KEY_RIGHT && buttons->getCurrentFrame() == 10){
            score1+=buttons->getY();
            pressed = 1;
        }else if(keys & KEY_UP && buttons->getCurrentFrame() == 11){
            score1+=buttons->getY();
            pressed = 1;
        }
    }
}

void song1::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(SharedPal, sizeof(SharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(danceroomPal, sizeof(danceroomPal)));

    engine.get()->enableText();
    engine->getTimer()->reset();
    engine->getTimer()->start();
    engine->enqueueMusic(music1, music1_bytes, data1.getSpeed());


    bg = std::unique_ptr<Background>(new Background(1, danceroomTiles, sizeof(danceroomTiles), danceroomMap, sizeof(danceroomMap)));
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
            .withAnimated(3, (16-(data1.getFallSpeed()*5)))
            .withLocation((GBA_SCREEN_WIDTH/4)-16, (GBA_SCREEN_HEIGHT/4)-16)
            .withinBounds()
            .buildPtr();

    animation2 = builder
            .withData(dancingmichmanTiles, sizeof(dancingmichmanTiles))
            .withSize(SIZE_32_32)
            .withAnimated(3, (16-(data1.getFallSpeed()*5)))
            .withLocation((GBA_SCREEN_WIDTH/4)-16, ((GBA_SCREEN_HEIGHT*3)/4)-16)
            .withinBounds()
            .buildPtr();

    animation3= builder
            .withData(nederlandmanTiles, sizeof(nederlandmanTiles))
            .withSize(SIZE_32_32)
            .withAnimated(3, (16-(data1.getFallSpeed()*5)))
            .withLocation(((GBA_SCREEN_WIDTH*3)/4)-16, (GBA_SCREEN_HEIGHT/4)-16)
            .withinBounds()
            .buildPtr();

    animation4 = builder
            .withData(j_germanTiles, sizeof(j_germanTiles))
            .withSize(SIZE_32_32)
            .withAnimated(3, (16-(data1.getFallSpeed()*5)))
            .withLocation(((GBA_SCREEN_WIDTH*3)/4)-16, ((GBA_SCREEN_HEIGHT*3)/4)-16)
            .withinBounds()
            .buildPtr();

    score1 = 0;
}