
#ifndef ALAKAJAM16_DANCE_INPUT_HPP
#define ALAKAJAM16_DANCE_INPUT_HPP

#include <dance_input_interface.hpp>

class DanceInputUp : public DanceInputInterface{
public:
    bool correctInputPressed(jt::InputGetInterface& input) const override;
    eDanceInput getType() const override;
};

class DanceInputDown : public DanceInputInterface{
public:
    bool correctInputPressed(jt::InputGetInterface& input) const override;
    eDanceInput getType() const override;
};

#endif // ALAKAJAM16_DANCE_INPUT_HPP
