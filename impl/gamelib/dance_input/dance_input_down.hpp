#ifndef ALAKAJAM16_DANCE_INPUT_DOWN_HPP
#define ALAKAJAM16_DANCE_INPUT_DOWN_HPP

#include <dance_input/dance_input_impl.hpp>
#include <texture_manager_interface.hpp>

class DanceInputDown : public DanceInputImpl {
public:
    explicit DanceInputDown(jt::TextureManagerInterface& tm);
    bool correctInputPressed(jt::InputGetInterface& input) const override;
    eDanceInput getType() const override;
};

#endif // ALAKAJAM16_DANCE_INPUT_DOWN_HPP
