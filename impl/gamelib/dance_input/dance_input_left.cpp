
#include "dance_input_left.hpp"
#include "dance_input_icon/dance_input_icon_left.hpp"

DanceInputLeft::DanceInputLeft(jt::TextureManagerInterface& tm)
{
    m_icon = std::make_shared<DanceInputIconLeft>(tm);
}

bool DanceInputLeft::correctInputPressed(jt::InputGetInterface& input) const
{
    if (input.keyboard()->justPressed(jt::KeyCode::Left)
        || input.keyboard()->justPressed(jt::KeyCode::A)) {
        return true;
    }
    if (input.gamepad(0)->justPressed(jt::GamepadButtonCode::GBU4)) {
        return true;
    }
    return false;
}
eDanceInput DanceInputLeft::getType() const { return eDanceInput::Left; }
