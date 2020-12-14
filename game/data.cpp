//
// Created by Ben Luyck on 14/12/2020.
//

#include "data.h"

data data1;

void data::setSpeed(int newspeed){
    speed = newspeed;
}
int data::getSpeed(){
    return speed;
}

void data::setFallSpeed(int newfallspeed){
    fallspeed = newfallspeed;
}
int data::getFallSpeed(){
    return fallspeed;
}

void data::setTopScore1(int newtop){
    topscore1 = newtop;
}
int data::getTopScore1(){
    return topscore1;
}

void data::setTopScore2(int newtop){
    topscore2 = newtop;
}
int data::getTopScore2(){
    return topscore2;
}

void data::setTopScore3(int newtop){
    topscore3 = newtop;
}
int data::getTopScore3(){
    return topscore3;
}