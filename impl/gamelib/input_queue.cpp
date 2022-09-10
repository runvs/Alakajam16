
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
    auto expectedInput = m_inputs.front();
    if (expectedInput->correctInputPressed(getGame()->input())) {
        std::cout << "correct\n";
        m_inputs.pop_front();
    }
}
void InputQueue::doDraw() const { }
