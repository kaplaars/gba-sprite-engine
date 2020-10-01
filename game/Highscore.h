#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/background/background.h>

class Highscore : public Scene {
private:
    std::unique_ptr<Background> bg;

public:
    Highscore(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;
};