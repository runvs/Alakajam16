
#ifndef ALAKAJAM16_INPUT_QUEUE_HPP
#define ALAKAJAM16_INPUT_QUEUE_HPP

#include "sprite.hpp"
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
    void setAddInputCallback(
        std::function<void(std::vector<std::shared_ptr<jt::DrawableInterface>>)> const& cb);
    void setHideCallback(
        std::function<void(std::vector<std::shared_ptr<jt::DrawableInterface>>)> const& cb);
    void setCorrectCallback(std::function<void(std::shared_ptr<DanceInputInterface>)> const& cb);

    void setAllCorrectCallback(
        std::function<void(std::vector<std::shared_ptr<jt::DrawableInterface>>)> const& cb);
    void clear();
    void hide();

    std::vector<std::shared_ptr<jt::DrawableInterface>> getAllIcons() const;
    std::shared_ptr<jt::Sprite> m_bubblePirate { nullptr };

private:
    std::deque<std::shared_ptr<DanceInputInterface>> m_inputs;
    std::vector<std::shared_ptr<DanceInputInterface>> m_allInputs;
    std::shared_ptr<jt::Sprite> m_bubbleParrot { nullptr };

    std::function<void(void)> m_wrongInputCallback;
    std::function<void(std::shared_ptr<DanceInputInterface>)> m_correctInputCallback;
    std::function<void(std::vector<std::shared_ptr<jt::DrawableInterface>>)>
        m_allCorrectInputCallback;
    std::function<void(std::vector<std::shared_ptr<jt::DrawableInterface>>)> m_addInputCallback;
    std::function<void(std::vector<std::shared_ptr<jt::DrawableInterface>>)> m_hideCallback;

    float m_inputBlockedFor = 0.0f;
    std::size_t m_currentInputIndex { 0U };
    bool m_isHidden { false };

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    void updateIcons(float elapsed);
    void checkForInput();
    // returns true if invalid input has been pressed
    bool checkForInvalidInput() const;

    bool canTakeInput() const;
    std::shared_ptr<DanceInputInterface> getCurrentInput() const;
};

#endif // ALAKAJAM16_INPUT_QUEUE_HPP
