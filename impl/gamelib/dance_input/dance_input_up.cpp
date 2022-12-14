
#include "dance_input_up.hpp"
#include <dance_input_icon/dance_input_icon_up.hpp>

DanceInputUp::DanceInputUp(jt::TextureManagerInterface& tm)
{
    m_icon = std::make_shared<DanceInputIconUp>(tm);
}

bool DanceInputUp::correctInputPressed(jt::InputGetInterface& input) const
{
    if (input.keyboard()->justPressed(jt::KeyCode::Up)
        || input.keyboard()->justPressed(jt::KeyCode::W)) {
        return true;
    }
    if (input.gamepad(0)->justPressed(jt::GamepadButtonCode::GBY)) {
        return true;
    }
    return false;
}
eDanceInput DanceInputUp::getType() const { return eDanceInput::Up; }
