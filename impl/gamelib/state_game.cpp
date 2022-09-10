#include "state_game.hpp"
#include "dance_input/dance_input_left.hpp"
#include "dance_input/dance_input_right.hpp"
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

    createQueue();

    addInputsToQueue(2);

    createPirate();

    m_vignette = std::make_shared<jt::Vignette>(GP::GetScreenSize());
    add(m_vignette);
    m_hud = std::make_shared<Hud>();
    add(m_hud);

    // StateGame will call drawObjects itself.
    setAutoDraw(false);
}

std::string getAnimNameFromType(eDanceInput input)
{
    std::map<eDanceInput, std::string> conversion { { eDanceInput::Up, "up" },
        { eDanceInput::Down, "down" }, { eDanceInput::Left, "Links" },
        { eDanceInput::Right, "Rechts" } };

    return conversion[input];
}

int getAnimRepeatFromType(eDanceInput input)
{
    std::map<eDanceInput, int> conversion { { eDanceInput::Up, 3 }, { eDanceInput::Down, 3 },
        { eDanceInput::Left, 2 }, { eDanceInput::Right, 2 } };

    return conversion[input];
}

void StateGame::createQueue()
{
    m_inputQueue = std::make_shared<InputQueue>();
    m_inputQueue->setAllInputs({ std::make_shared<DanceInputUp>(textureManager()),
        std::make_shared<DanceInputDown>(textureManager()),
        std::make_shared<DanceInputLeft>(textureManager()),
        std::make_shared<DanceInputRight>(textureManager()) });

    m_inputQueue->setCorrectCallback([this](std::shared_ptr<DanceInputInterface> input) {
        getGame()->logger().info("correct input callback");

        // flash/tween sprites
        for (auto& i : input->getIcon()->getAllDrawables()) {
            i->flash(0.25f, jt::colors::Green);
            auto twa = std::make_shared<jt::TweenAlpha>(i, 0.25f, 0, 255);
            add(twa);
        }

        // play pirate animation
        auto const currentAnimName = m_pirate->m_anim->getCurrentAnimationName();
        auto const nextAnimName = getAnimNameFromType(input->getType());
        if (currentAnimName != nextAnimName) {
            m_pirate->m_anim->play(nextAnimName, 0, true);
        }

        // create timer to make pirate go back to idle
        if (m_pirateReturnToIdleTimer) {
            m_pirateReturnToIdleTimer->cancel();
        }
        auto const time
            = m_pirate->m_anim->getCurrentAnimTotalTime() * getAnimRepeatFromType(input->getType());
        m_pirateReturnToIdleTimer = std::make_shared<jt::Timer>(
            time, [this]() { m_pirate->m_anim->play("down", 0, true); }, 1);
        add(m_pirateReturnToIdleTimer);
    });

    m_inputQueue->setAllCorrectCallback(
        [this](std::vector<std::shared_ptr<jt::DrawableInterface>> const& icons) {
            getGame()->logger().info("all correct input callback");
            for (auto& i : icons) {
                i->flash(0.25f, jt::colors::Green);

                auto twa = std::make_shared<jt::TweenAlpha>(i, 0.45f, 255, 0);
                add(twa);

                auto tws = std::make_shared<jt::TweenScale>(
                    i, 0.45f, jt::Vector2f { 1.0f, 1.0f }, jt::Vector2f { 0.0f, 0.0f });
                add(tws);
            }
            m_score++;
            m_hud->getObserverScoreP1()->notify(m_score);
            auto t = std::make_shared<jt::Timer>(
                1.0f, [this]() { resetInputQueue(); }, 1);
            add(t);
        });

    m_inputQueue->setWrongInputCallback([this]() {
        getGame()->logger().info("wrong input callback");
        auto icons = m_inputQueue->getAllIcons();
        for (auto& ic : icons) {

            ic->flash(0.45f, jt::colors::Red);
        }
        m_score--;
        m_hud->getObserverScoreP1()->notify(m_score);
        if (m_score <= 0) {
            m_score = 0;
        }

        add(std::make_shared<jt::Timer>(
            0.5f, [this]() { resetInputQueue(); }, 1));
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
}
void StateGame::resetInputQueue()
{
    m_inputQueue->clear();
    addInputsToQueue(m_score + 2);
}

void StateGame::createPirate()
{
    m_pirate = std::make_shared<Pirate>();
    add(m_pirate);
}

void StateGame::doInternalUpdate(float const elapsed)
{
    if (m_running) {
        // update game logic here
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
    } else if (randomValue == 2) {
        return std::make_shared<DanceInputLeft>(tm);
    } else {
        return std::make_shared<DanceInputRight>(tm);
    }
}

// call this only once to add multiple inputs
void StateGame::addInputsToQueue(std::size_t numberOfInputsToAdd)
{
    for (auto i = 0; i != numberOfInputsToAdd; ++i) {
        auto t = std::make_shared<jt::Timer>(
            0.75f * i,
            [this]() {
                auto input = createRandomDanceInput(textureManager());
                m_inputQueue->add(input);

                getGame()->logger().debug("add input");
                for (auto& i : input->getIcon()->getAllDrawables()) {
                    i->setScale(jt::Vector2f { 5.0f, 5.0f });
                    i->setColor(jt::Color { 255, 255, 255, 0 });
                    auto tws = jt::TweenScale::create(
                        i, 0.4f, jt::Vector2f { 5.0f, 5.0f }, jt::Vector2f { 1.0f, 1.0f });
                    add(tws);

                    auto twa = jt::TweenAlpha::create(i, 0.4f, 0, 255);
                    twa->addCompleteCallback(
                        [this]() { getGame()->gfx().camera().shake(0.15f, 5.0f); });
                    add(twa);
                }
            },
            1);
        add(t);
    }
    auto t = std::make_shared<jt::Timer>(
        0.75f * (numberOfInputsToAdd + 1), [this]() { m_inputQueue->hide(); }, 1);
    add(t);
}
