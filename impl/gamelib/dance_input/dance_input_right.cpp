
#include "dance_input_right.hpp"
#include "dance_input_icon/dance_input_icon_right.hpp"

DanceInputRight::DanceInputRight(jt::TextureManagerInterface& tm)
{
    m_icon = std::make_shared<DanceInputIconRight>(tm);
}

bool DanceInputRight::correctInputPressed(jt::InputGetInterface& input) const
{
    if (input.keyboard()->justPressed(jt::KeyCode::Right)
        || input.keyboard()->justPressed(jt::KeyCode::D)) {
        return true;
    }
    if (input.gamepad(0)->justPressed(jt::GamepadButtonCode::GBB)) {
        return true;
    }
    return false;
}

eDanceInput DanceInputRight::getType() const { return eDanceInput::Right; }
