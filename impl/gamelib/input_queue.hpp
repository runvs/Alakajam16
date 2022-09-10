
#ifndef ALAKAJAM16_INPUT_QUEUE_HPP
#define ALAKAJAM16_INPUT_QUEUE_HPP

#include <dance_input/dance_input_interface.hpp>
#include <game_object.hpp>
#include <deque>
#include <functional>
#include <memory>

class InputQueue : public jt::GameObject {
public:
    void add(std::shared_ptr<DanceInputInterface> input);

    void setAllInputs(std::vector<std::shared_ptr<DanceInputInterface>> const& allInputs);
    void setWrongInputCallback(std::function<void(void)> const& cb);

    void clear();

private:
    std::deque<std::shared_ptr<DanceInputInterface>> m_inputs;

    std::vector<std::shared_ptr<DanceInputInterface>> m_allInputs;

    std::function<void(void)> m_wrongInputCallback;

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    void updateIcons(float elapsed);
    void checkForInput();
};

#endif // ALAKAJAM16_INPUT_QUEUE_HPP
