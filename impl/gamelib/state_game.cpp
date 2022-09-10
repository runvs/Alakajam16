#include "state_game.hpp"
#include "random/random.hpp"
#include <box2dwrapper/box2d_world_impl.hpp>
#include <color/color.hpp>
#include <dance_input/dance_input_down.hpp>
#include <dance_input/dance_input_up.hpp>
#include <game_interface.hpp>
#include <game_properties.hpp>
#include <hud/hud.hpp>
#include <screeneffects/vignette.hpp>
#include <shape.hpp>
#include <sprite.hpp>
#include <state_menu.hpp>
#include <timer.hpp>
#include <tweens/tween_alpha.hpp>
#include <tweens/tween_color.hpp>
#include <tweens/tween_scale.hpp>

void StateGame::doInternalCreate()
{
    float const w = static_cast<float>(GP::GetWindowSize().x);
    float const h = static_cast<float>(GP::GetWindowSize().y);

    using jt::Shape;
    using jt::TweenAlpha;

    m_background = std::make_shared<Shape>();
    m_background->makeRect({ w, h }, textureManager());
    m_background->setColor(GP::PaletteBackground());
    m_background->setIgnoreCamMovement(true);
    m_background->update(0.0f);

    m_inputQueue = std::make_shared<InputQueue>();
    m_inputQueue->setAllInputs({ std::make_shared<DanceInputUp>(textureManager()),
        std::make_shared<DanceInputDown>(textureManager()) });

    m_inputQueue->setWrongInputCallback([this]() {
        getGame()->logger().info("wrong input callback invoked");
        auto icons = m_inputQueue->getAllIcons();
        for (auto& ic : icons) {

            ic->flash(0.45f, jt::colors::Red);
        }

        add(std::make_shared<jt::Timer>(
            0.5f, [this]() { resetInputQueue(); }, 1));
    });

    m_inputQueue->setAddInputCallback(
        [this](std::vector<std::shared_ptr<jt::DrawableInterface>> const& icons) {
            getGame()->logger().info("add input");
            for (auto& i : icons) {
                i->setScale(jt::Vector2f { 2.0f, 2.0f });

                auto tws = jt::TweenScale::create(
                    i, 0.3f, jt::Vector2f { 2.0f, 2.0f }, jt::Vector2f { 1.0f, 1.0f });
                add(tws);

                jt::Color const startColor { 255, 255, 255, 0 };
                jt::Color const endColor { 255, 255, 255, 255 };
                auto twc = jt::TweenColor::create(i, 0.3f, startColor, endColor);
                add(twc);
            }
        });

    m_inputQueue->setHideCallback(
        [this](std::vector<std::shared_ptr<jt::DrawableInterface>> const& icons) {
            getGame()->logger().info("hide input");
            for (auto& i : icons) {
                auto twa = jt::TweenAlpha::create(i, 0.3f, 255U, 0U);
                add(twa);
            }
        });

    add(m_inputQueue);

    addInputsToQueue(3);

    createPlayer();

    m_vignette = std::make_shared<jt::Vignette>(GP::GetScreenSize());
    add(m_vignette);
    m_hud = std::make_shared<Hud>();
    add(m_hud);

    // StateGame will call drawObjects itself.
    setAutoDraw(false);
}
void StateGame::resetInputQueue() { m_inputQueue->clear(); }

void StateGame::createPlayer() { }

void StateGame::doInternalUpdate(float const elapsed)
{
    if (m_running) {
        // update game logic here
        if (getGame()->input().keyboard()->justPressed(jt::KeyCode::A)) {
            m_scoreP1++;
            m_hud->getObserverScoreP1()->notify(m_scoreP1);
        }
        if (getGame()->input().keyboard()->justPressed(jt::KeyCode::D)) {
            m_scoreP2++;
            m_hud->getObserverScoreP2()->notify(m_scoreP2);
        }
    }

    m_background->update(elapsed);
    m_vignette->update(elapsed);
}

void StateGame::doInternalDraw() const
{
    m_background->draw(renderTarget());
    drawObjects();
    m_vignette->draw();
    m_hud->draw();
}

void StateGame::endGame()
{
    if (m_hasEnded) {
        // trigger this function only once
        return;
    }
    m_hasEnded = true;
    m_running = false;

    getGame()->stateManager().switchState(std::make_shared<StateMenu>());
}

std::string StateGame::getName() const { return "State Game"; }

std::shared_ptr<DanceInputInterface> createRandomDanceInput(jt::TextureManagerInterface& tm)
{
    auto const randomValue = jt::Random::getInt(0, 3);
    if (randomValue == 0) {
        return std::make_shared<DanceInputUp>(tm);
    } else if (randomValue == 1) {
        return std::make_shared<DanceInputDown>(tm);
    } else {
        // TODO
        return std::make_shared<DanceInputUp>(tm);
    }
}

// call this only once
void StateGame::addInputsToQueue(std::size_t numberOfInputsToAdd)
{
    for (auto i = 0; i != numberOfInputsToAdd; ++i) {
        auto t = std::make_shared<jt::Timer>(
            0.75f * i, [this]() { m_inputQueue->add(createRandomDanceInput(textureManager())); },
            1);
        add(t);
    }
    auto t = std::make_shared<jt::Timer>(
        0.75f * (numberOfInputsToAdd + 1), [this]() { m_inputQueue->hide(); }, 1);
    add(t);
}
