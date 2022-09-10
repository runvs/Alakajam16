
#ifndef ALAKAJAM16_INPUT_QUEUE_HPP
#define ALAKAJAM16_INPUT_QUEUE_HPP

#include <dance_input_interface.hpp>
#include <game_object.hpp>
#include <deque>
#include <memory>

class InputQueue : public jt::GameObject {
public:
    void add(std::shared_ptr<DanceInputInterface> input);

private:
    std::deque<std::shared_ptr<DanceInputInterface>> m_inputs;

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // ALAKAJAM16_INPUT_QUEUE_HPP
