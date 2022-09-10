
#include "dance_input_icon.hpp"
DanceInputIconUp::DanceInputIconUp(jt::TextureManagerInterface& tm)
{
    m_sprite = std::make_shared<jt::Sprite>("assets/up.png", tm);
    m_sprite->setOrigin(jt::OriginMode::CENTER);
}

std::vector<std::shared_ptr<jt::DrawableInterface>> DanceInputIconUp::getAllDrawables()
{
    return { m_sprite };
}

DanceInputIconDown::DanceInputIconDown(jt::TextureManagerInterface& tm)
{
    m_sprite = std::make_shared<jt::Sprite>("assets/down.png", tm);
    m_sprite->setOrigin(jt::OriginMode::CENTER);
}
std::vector<std::shared_ptr<jt::DrawableInterface>> DanceInputIconDown::getAllDrawables()
{
    return { m_sprite };
}
