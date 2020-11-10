#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/background/background.h>


class song2 : public Scene {
private:
    std::unique_ptr<Background> bg;
    std::unique_ptr<Sprite> animation, animation2, animation3, animation4, buttons;
public:
    song2(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;

    int score2=0, pressed=0;
};