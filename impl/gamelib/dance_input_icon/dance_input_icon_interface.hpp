#ifndef ALAKAJAM16_DANCE_INPUT_ICON_INTERFACE_HPP
#define ALAKAJAM16_DANCE_INPUT_ICON_INTERFACE_HPP

#include <graphics/drawable_interface.hpp>
#include <memory>
#include <vector>

class DanceInputIconInterface {
public:
    virtual ~DanceInputIconInterface() = default;
    virtual std::vector<std::shared_ptr<jt::DrawableInterface>> getAllDrawables() = 0;
};

#endif // ALAKAJAM16_DANCE_INPUT_ICON_INTERFACE_HPP
