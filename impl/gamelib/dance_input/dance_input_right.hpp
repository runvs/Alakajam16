
#ifndef ALAKAJAM16_DANCE_INPUT_RIGHT_HPP
#define ALAKAJAM16_DANCE_INPUT_RIGHT_HPP

#include <dance_input/dance_input_impl.hpp>
#include <texture_manager_interface.hpp>

class DanceInputRight : public DanceInputImpl {
public:
    explicit DanceInputRight(jt::TextureManagerInterface& tm);
    bool correctInputPressed(jt::InputGetInterface& input) const override;
    eDanceInput getType() const override;
};

#endif // ALAKAJAM16_DANCE_INPUT_RIGHT_HPP
