//
// Created by Ben Luyck on 14/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_DATA_H
#define GBA_SPRITE_ENGINE_PROJECT_DATA_H
class data{
    public:
        int speed, fallspeed, topscore1=0, topscore2=0, topscore3=0;

    int getSpeed();
    void setSpeed(int newspeed);
    void setFallSpeed(int newfallspeed);
    int getFallSpeed();
    void setTopScore1(int newtop);
    int getTopScore1();
    void setTopScore2(int newtop);
    int getTopScore2();
    void setTopScore3(int newtop);
    int getTopScore3();
    void setEndgameScore(int newtop);
};
#endif //GBA_SPRITE_ENGINE_PROJECT_DATA_H
