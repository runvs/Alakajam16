
#include "dance_input_down.hpp"
<<<<<<< HEAD
#include "dance_input_icon/dance_input_icon_down.hpp"
=======
#include <dance_input_icon/dance_input_icon.hpp>
>>>>>>> 68199e9fdbe59486eccdcedb923097244f0a670d

DanceInputDown::DanceInputDown(jt::TextureManagerInterface& tm)
{
    m_icon = std::make_shared<DanceInputIconDown>(tm);
}
bool DanceInputDown::correctInputPressed(jt::InputGetInterface& input) const
{
    if (input.keyboard()->justPressed(jt::KeyCode::Down)
        || input.keyboard()->justPressed(jt::KeyCode::S)) {
        return true;
    }
    if (input.gamepad(0)->justPressed(jt::GamepadButtonCode::GBU3)) {
        return true;
    }
    return false;
}
eDanceInput DanceInputDown::getType() const { return eDanceInput::Down; }
