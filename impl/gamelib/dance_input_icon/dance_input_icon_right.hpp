
#ifndef ALAKAJAM16_DANCE_INPUT_ICON_RIGHT_HPP
#define ALAKAJAM16_DANCE_INPUT_ICON_RIGHT_HPP

#include <dance_input_icon/dance_input_icon_interface.hpp>
#include <sprite.hpp>

class DanceInputIconRight : public DanceInputIconInterface {
public:
    explicit DanceInputIconRight(jt::TextureManagerInterface& tm);
    std::vector<std::shared_ptr<jt::DrawableInterface>> getAllDrawables() override;

private:
    std::shared_ptr<jt::Sprite> m_sprite { nullptr };
};

#endif // ALAKAJAM16_DANCE_INPUT_ICON_RIGHT_HPP
