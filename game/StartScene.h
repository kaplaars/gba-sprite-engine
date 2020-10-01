//
// Created by Wouter Groeneveld on 02/08/18.
//

#ifndef GBA_SPRITE_ENGINE_START_SCENE_H
#define GBA_SPRITE_ENGINE_START_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include "gbmap.h"

class StartScene : public Scene {
private:
    std::unique_ptr<Background> bg;
    std::unique_ptr<Sprite> animation;
public:
    StartScene(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;

};


#endif //GBA_SPRITE_ENGINE_SAMPLE_START_SCENE_H
