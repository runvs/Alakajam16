
#ifndef ALAKAJAM16_DANCE_INPUT_INTERFACE_HPP
#define ALAKAJAM16_DANCE_INPUT_INTERFACE_HPP

#include <dance_input_icon/dance_input_icon_interface.hpp>
#include <input/input_get_interface.hpp>
#include <cstdint>
#include <optional>

enum class eDanceInput : std::uint8_t { Left, Right, Up, Down };

class DanceInputInterface {
public:
    virtual ~DanceInputInterface() = default;
    virtual bool correctInputPressed(jt::InputGetInterface& input) const = 0;
    virtual eDanceInput getType() const = 0;
    virtual std::shared_ptr<DanceInputIconInterface> getIcon() = 0;
};

#endif // ALAKAJAM16_DANCE_INPUT_INTERFACE_HPP
