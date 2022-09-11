#ifndef GAME_STATE_GAME_HPP
#define GAME_STATE_GAME_HPP

#include "parrot.hpp"
#include "pirate.hpp"
#include "timer.hpp"
#include <box2dwrapper/box2d_world_interface.hpp>
#include <game_state.hpp>
#include <input_queue.hpp>
#include <memory>
#include <vector>

// fwd decls
namespace jt {
class Shape;
class Sprite;
class Vignette;
} // namespace jt

class Hud;

class StateGame : public jt::GameState {
public:
    std::string getName() const override;

private:
    std::shared_ptr<jt::Animation> m_background { nullptr };
    std::shared_ptr<jt::Vignette> m_vignette { nullptr };
    std::shared_ptr<Hud> m_hud { nullptr };

    std::shared_ptr<InputQueue> m_inputQueue { nullptr };

    std::shared_ptr<Pirate> m_pirate { nullptr };
    std::shared_ptr<jt::Timer> m_pirateReturnToIdleTimer { nullptr };

    std::shared_ptr<Parrot> m_parrot { nullptr };

    bool m_running { true };
    bool m_hasEnded { false };

    int m_score { 1 };

    void doInternalCreate() override;
    void doInternalUpdate(float const elapsed) override;
    void doInternalDraw() const override;

    void endGame();
    void createPirate();
    void resetInputQueue();
    void addInputsToQueue(std::size_t numberOfInputsToAdd);
    void createQueue();
    void createParrot();
};

#endif
