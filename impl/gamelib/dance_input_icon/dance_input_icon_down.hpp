
#ifndef ALAKAJAM16_DANCE_INPUT_ICON_DOWN_HPP
#define ALAKAJAM16_DANCE_INPUT_ICON_DOWN_HPP

#include <dance_input_icon/dance_input_icon_interface.hpp>
#include <sprite.hpp>

class DanceInputIconDown : public DanceInputIconInterface {
public:
    explicit DanceInputIconDown(jt::TextureManagerInterface& tm);
    std::vector<std::shared_ptr<jt::DrawableInterface>> getAllDrawables() override;

private:
    std::shared_ptr<jt::Sprite> m_sprite { nullptr };
};

#endif // ALAKAJAM16_DANCE_INPUT_ICON_DOWN_HPP
