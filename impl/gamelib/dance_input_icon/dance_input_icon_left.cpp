#include "dance_input_icon_left.hpp"
DanceInputIconLeft::DanceInputIconLeft(jt::TextureManagerInterface& tm)
{
    m_sprite = std::make_shared<jt::Sprite>("assets/left.png", tm);
    m_sprite->setOrigin(jt::OriginMode::CENTER);
    m_sprite->setPosition(jt::Vector2f { -5000, -5000 });
    m_sprite->update(0.1f);
}

std::vector<std::shared_ptr<jt::DrawableInterface>> DanceInputIconLeft::getAllDrawables()
{
    return { m_sprite };
}
