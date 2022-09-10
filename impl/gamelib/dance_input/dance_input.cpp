
#include "dance_input.hpp"
#include <dance_input_icon/dance_input_icon.hpp>

std::shared_ptr<DanceInputIconInterface> DanceInputImpl::getIcon() { return m_icon; }

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
    if (input.gamepad(0)->justPressed(jt::GamepadButtonCode::GBU2)) {
        return true;
    }
    return false;
}
eDanceInput DanceInputUp::getType() const { return eDanceInput::Up; }

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
