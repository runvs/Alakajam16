
#ifndef ALAKAJAM16_DANCE_INPUT_ICON_HPP
#define ALAKAJAM16_DANCE_INPUT_ICON_HPP

#include <dance_input_icon/dance_input_icon_interface.hpp>
#include <sprite.hpp>

class DanceInputIconUp : public DanceInputIconInterface {
public:
    explicit DanceInputIconUp(jt::TextureManagerInterface& tm);
    std::vector<std::shared_ptr<jt::DrawableInterface>> getAllDrawables() override;

private:
    std::shared_ptr<jt::Sprite> m_sprite { nullptr };
};

class DanceInputIconDown : public DanceInputIconInterface {
public:
    explicit DanceInputIconDown(jt::TextureManagerInterface& tm);
    std::vector<std::shared_ptr<jt::DrawableInterface>> getAllDrawables() override;

private:
    std::shared_ptr<jt::Sprite> m_sprite { nullptr };
};

#endif // ALAKAJAM16_DANCE_INPUT_ICON_HPP
