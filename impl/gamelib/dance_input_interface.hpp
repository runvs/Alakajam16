
#ifndef ALAKAJAM16_DANCE_INPUT_INTERFACE_HPP
#define ALAKAJAM16_DANCE_INPUT_INTERFACE_HPP

#include <cstdint>
#include <optional>
#include <input/input_get_interface.hpp>

enum class eDanceInput  : std::uint8_t {
    Left,
    Right,
    Up,
    Down,
    A,
    BLeft,
    BRight,
    BUp,
    BDown
};

class DanceInputInterface {
public:
    virtual ~DanceInputInterface() = default;
    virtual bool correctInputPressed(jt::InputGetInterface& input) const = 0;
    virtual eDanceInput getType() const = 0;
};

#endif // ALAKAJAM16_DANCE_INPUT_INTERFACE_HPP
