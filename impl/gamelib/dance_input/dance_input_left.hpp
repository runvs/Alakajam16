
#ifndef ALAKAJAM16_DANCE_INPUT_LEFT_HPP
#define ALAKAJAM16_DANCE_INPUT_LEFT_HPP

#include <dance_input/dance_input_impl.hpp>
#include <texture_manager_interface.hpp>

class DanceInputLeft : public DanceInputImpl {
public:
    explicit DanceInputLeft(jt::TextureManagerInterface& tm);
    bool correctInputPressed(jt::InputGetInterface& input) const override;
    eDanceInput getType() const override;
};

#endif // ALAKAJAM16_DANCE_INPUT_LEFT_HPP
