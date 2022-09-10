
#ifndef ALAKAJAM16_DANCE_INPUT_IMPL_HPP
#define ALAKAJAM16_DANCE_INPUT_IMPL_HPP

#include <dance_input/dance_input_interface.hpp>

class DanceInputImpl : public DanceInputInterface {
public:
    std::shared_ptr<DanceInputIconInterface> getIcon() override;

protected:
    std::shared_ptr<DanceInputIconInterface> m_icon { nullptr };
};
#endif // ALAKAJAM16_DANCE_INPUT_IMPL_HPP
