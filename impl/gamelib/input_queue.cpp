
#include "input_queue.hpp"
#include <game_interface.hpp>
#include <iostream>

void InputQueue::add(std::shared_ptr<DanceInputInterface> input) { m_inputs.push_back(input); }
void InputQueue::doCreate() { }
void InputQueue::doUpdate(float const elapsed)
{
    if (m_inputs.empty()) {
        return;
    }

    checkForInput();
    updateIcons(elapsed);
}

void InputQueue::checkForInput()
{
    auto expectedInput = m_inputs.front();

    for (auto const& otherInput : m_allInputs) {
        if (otherInput->correctInputPressed(getGame()->input())) {
            std::cout << "incorrect!!!\n";

            if (m_wrongInputCallback) {
                m_wrongInputCallback();
            }
            return;
        }
    }

    if (expectedInput->correctInputPressed(getGame()->input())) {
        std::cout << "correct\n";
        m_inputs.pop_front();
        return;
    }
}

void InputQueue::updateIcons(float elapsed)
{
    for (auto i = 0U; i != m_inputs.size(); ++i) {
        auto& input = m_inputs.at(i);
        auto drawables = input->getIcon()->getAllDrawables();
        for (auto j = 0U; j != drawables.size(); ++j) {
            auto& icon = drawables.at(j);

            auto const offset = jt::Vector2f { 100.0f, 100.0f };
            icon->setPosition(offset + jt::Vector2f { 24.0f * i + -20.0f * j });
            icon->update(elapsed);
        }
    }
}

void InputQueue::doDraw() const
{
    if (m_inputs.empty()) {
        return;
    }
    for (auto const& input : m_inputs) {
        for (auto const& icon : input->getIcon()->getAllDrawables()) {
            icon->draw(renderTarget());
        }
    }
}
void InputQueue::setAllInputs(std::vector<std::shared_ptr<DanceInputInterface>> const& allInputs)
{
    m_allInputs = allInputs;
}
void InputQueue::setWrongInputCallback(std::function<void(void)> const& cb)
{
    m_wrongInputCallback = cb;
}
void InputQueue::clear() { m_inputs.clear(); }
