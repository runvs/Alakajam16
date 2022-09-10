
#ifndef ALAKAJAM16_DANCE_INPUT_HPP
#define ALAKAJAM16_DANCE_INPUT_HPP

#include <dance_input/dance_input_interface.hpp>
#include <texture_manager_interface.hpp>

class DanceInputImpl : public DanceInputInterface {
public:
    std::shared_ptr<DanceInputIconInterface> getIcon() override;

protected:
    std::shared_ptr<DanceInputIconInterface> m_icon { nullptr };
};

class DanceInputUp : public DanceInputImpl {
public:
    explicit DanceInputUp(jt::TextureManagerInterface& tm);
    bool correctInputPressed(jt::InputGetInterface& input) const override;
    eDanceInput getType() const override;
};

class DanceInputDown : public DanceInputImpl {
public:
    explicit DanceInputDown(jt::TextureManagerInterface& tm);
    bool correctInputPressed(jt::InputGetInterface& input) const override;
    eDanceInput getType() const override;
};

#endif // ALAKAJAM16_DANCE_INPUT_HPP
