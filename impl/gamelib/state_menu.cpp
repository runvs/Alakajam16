#include "state_menu.hpp"
#include <audio/intro_looping_sound_with_effect.hpp>
#include <build_info.hpp>
#include <color/color.hpp>

#include <drawable_helpers.hpp>
#include <game_interface.hpp>
#include <game_properties.hpp>
#include <input/input_manager.hpp>
#include <lerp.hpp>
#include <log/license_info.hpp>
#include <math_helper.hpp>
#include <oalpp/effects/utility/gain.hpp>
#include <screeneffects/screen_wrap.hpp>
#include <screeneffects/vignette.hpp>
#include <shape.hpp>
#include <sprite.hpp>
#include <state_game.hpp>
#include <state_manager/state_manager_transition_fade_to_black.hpp>
#include <text.hpp>
#include <tweens/tween_alpha.hpp>
#include <tweens/tween_color.hpp>
#include <tweens/tween_position.hpp>
#include <algorithm>

void StateMenu::doInternalCreate()
{
    createMenuText();
    createShapes();
    createVignette();

    createTweens();

    add(std::make_shared<jt::LicenseInfo>());

    getGame()->stateManager().setTransition(std::make_shared<jt::StateManagerTransitionFadeToBlack>(
        GP::GetScreenSize(), textureManager()));

    auto bgm_chill = getGame()->audio().getPermanentSound("bgm_chill");
    if (bgm_chill) {
        bgm_chill->stop();
    }

    oalpp::effects::utility::Gain gain { 0.0f };
    auto bgm = getGame()->audio().addPermanentSound(
        "bgm", "assets/bgm_intro.mp3", "assets/bgm_loop.mp3", gain);
    bgm->setVolume(0.15f);
    bgm->play();
}

void StateMenu::createVignette()
{
    m_vignette = std::make_shared<jt::Vignette>(GP::GetScreenSize());
    add(m_vignette);
}

void StateMenu::createShapes()
{
    m_background = std::make_shared<jt::Animation>();
    m_background->add("assets/Beach.png", "idle", jt::Vector2u { 240, 160 }, { 0, 1, 2, 3 }, 0.3f,
        textureManager());
    m_background->play("idle");
    m_overlay = jt::dh::createShapeRect(GP::GetScreenSize(), jt::colors::Black, textureManager());
}

void StateMenu::createMenuText()
{
    createTextTitle();
    createTextStart();
    createTextExplanation();
    createTextCredits();
}
void StateMenu::createTextExplanation()
{
    m_textExplanation = jt::dh::createText(renderTarget(), "", 16U, GP::PaletteFontFront());
    auto const half_width = GP::GetScreenSize().x / 2.0f;
    m_textExplanation->setPosition({ half_width, 180 });
    m_textExplanation->setShadow(GP::PaletteFontShadow(), jt::Vector2f { 2, 2 });
}

void StateMenu::createTextCredits()
{
    m_textCredits = jt::dh::createText(renderTarget(),
        "Last run: " + jt::MathHelper::floatToStringWithXDigits(m_lastRunTime, 1) + " s\n"
            + GP::AuthorName() + "\nfor " + GP::JamName() /*+ "\n" + GP::JamDate()*/
            + "\nF9 for Game Info",
        16U, GP::PaletteFontCredits());
    m_textCredits->setTextAlign(jt::Text::TextAlign::LEFT);
    m_textCredits->setPosition({ 10, GP::GetScreenSize().y - 65 });
    m_textCredits->setShadow(GP::PaletteFontShadow(), jt::Vector2f { 1, 1 });

    m_textVersion = jt::dh::createText(renderTarget(), "", 16U, GP::PaletteFontCredits());
    if (jt::BuildInfo::gitTagName() != "") {
        m_textVersion->setText(jt::BuildInfo::gitTagName());
    } else {
        m_textVersion->setText(
            jt::BuildInfo::gitCommitHash().substr(0, 6) + " " + jt::BuildInfo::timestamp());
    }
    m_textVersion->setTextAlign(jt::Text::TextAlign::RIGHT);
    m_textVersion->setPosition({ GP::GetScreenSize().x - 5.0f, GP::GetScreenSize().y - 20.0f });
    m_textVersion->setShadow(GP::PaletteFontShadow(), jt::Vector2f { 1, 1 });
}

void StateMenu::createTextStart()
{
    auto const half_width = GP::GetScreenSize().x / 2.0f;
    m_textStart
        = jt::dh::createText(renderTarget(), "Press Space to start", 16U, GP::PaletteFontCredits());
    m_textStart->setPosition({ half_width, 50 });
    m_textStart->setShadow(GP::PaletteFontShadow(), jt::Vector2f { 3, 3 });
}

void StateMenu::createTextTitle()
{
    m_textTitle = std::make_shared<jt::Sprite>("assets/Logo.png", textureManager());
    m_textTitle->setPosition({ 5, 5 });
    //    m_textTitle->setShadow(GP::PaletteFontShadow(), jt::Vector2f { 4, 4 });
}

void StateMenu::createTweens()
{
    createTweenOverlayAlpha();
    createTweenTitleAlpha();
    createTweenCreditsPosition();
    createTweenExplanation();
}

void StateMenu::createInstructionTweenColor1()
{
    auto tc = jt::TweenColor::create(
        m_textStart, 0.5f, GP::PaletteFontCredits(), GP::PalleteFrontHighlight());
    tc->addCompleteCallback([this]() { createInstructionTweenColor2(); });
    tc->setAgePercentConversion([](float age) {
        return jt::Lerp::cubic(0.0f, 1.0f, jt::MathHelper::clamp(age, 0.0f, 1.0f));
    });
    add(tc);
}

void StateMenu::createInstructionTweenColor2()
{
    auto tc = jt::TweenColor::create(
        m_textStart, 0.45f, GP::PalleteFrontHighlight(), GP::PaletteFontCredits());
    tc->setAgePercentConversion([](float age) {
        return jt::Lerp::cubic(0.0f, 1.0f, jt::MathHelper::clamp(age, 0.0f, 1.0f));
    });
    tc->setStartDelay(0.2f);
    tc->addCompleteCallback([this]() { createInstructionTweenColor1(); });
    add(tc);
}

void StateMenu::createTweenExplanation()
{
    auto s2 = m_textStart->getPosition() + jt::Vector2f { -1000, 0 };
    auto e2 = m_textStart->getPosition();

    auto tween = jt::TweenPosition::create(m_textStart, 0.5f, s2, e2);
    tween->setStartDelay(0.3f);
    tween->setSkipFrames();

    tween->addCompleteCallback([this]() { createInstructionTweenColor1(); });
    add(tween);
}

void StateMenu::createTweenTitleAlpha()
{
    auto tween = jt::TweenAlpha::create(m_textTitle, 0.55f, 0, 255);
    tween->setStartDelay(0.2f);
    tween->setSkipFrames();
    add(tween);
}

void StateMenu::createTweenOverlayAlpha()
{
    auto tween = jt::TweenAlpha::create(m_overlay, 0.5f, std::uint8_t { 255 }, std::uint8_t { 0 });
    tween->setSkipFrames();
    add(tween);
}

void StateMenu::createTweenCreditsPosition()
{
    auto creditsPositionStart = m_textCredits->getPosition() + jt::Vector2f { 0, 150 };
    auto creditsPositionEnd = m_textCredits->getPosition();

    auto tweenCredits
        = jt::TweenPosition::create(m_textCredits, 0.75f, creditsPositionStart, creditsPositionEnd);
    tweenCredits->setStartDelay(0.8f);
    tweenCredits->setSkipFrames();
    add(tweenCredits);

    auto versionPositionStart = m_textVersion->getPosition() + jt::Vector2f { 0, 150 };
    auto versionPositionEnd = m_textVersion->getPosition();
    auto tweenVersion
        = jt::TweenPosition::create(m_textVersion, 0.75f, versionPositionStart, versionPositionEnd);
    tweenVersion->setStartDelay(0.8f);
    tweenVersion->setSkipFrames();
    add(tweenVersion);
}

void StateMenu::doInternalUpdate(float const elapsed)
{
    updateDrawables(elapsed);
    checkForTransitionToStateGame();
    jt::Vector2f const& axis = getGame()->input().gamepad(0)->getAxis(jt::GamepadAxisCode::ARight);
    if (m_started) {
        timeSinceStarted += elapsed;
        auto v = timeSinceStarted / 0.75f;
        if (v >= 1.0f) {
            v = 1.0f;
        }
        auto bgm = getGame()->audio().getPermanentSound("bgm");
        bgm->setBlend(v);
    }
}

void StateMenu::updateDrawables(const float& elapsed)
{
    m_background->update(elapsed);
    m_textTitle->update(elapsed);
    m_textStart->update(elapsed);
    m_textExplanation->update(elapsed);
    m_textCredits->update(elapsed);
    m_textVersion->update(elapsed);
    m_overlay->update(elapsed);
    m_vignette->update(elapsed);
}

void StateMenu::checkForTransitionToStateGame()
{
    auto const keysToTriggerTransition = { jt::KeyCode::Space, jt::KeyCode::Enter };

    if (std::any_of(keysToTriggerTransition.begin(), keysToTriggerTransition.end(),
            [this](auto const k) { return getGame()->input().keyboard()->justPressed(k); })) {
        startTransitionToStateGame();
    }
}

void StateMenu::startTransitionToStateGame()
{
    if (!m_started) {
        m_started = true;
        getGame()->stateManager().switchState(std::make_shared<StateGame>());
    }
}

void StateMenu::doInternalDraw() const
{
    m_background->draw(renderTarget());
    m_textTitle->draw(renderTarget());
    m_textStart->draw(renderTarget());
    m_textExplanation->draw(renderTarget());
    m_textCredits->draw(renderTarget());
    //    m_textVersion->draw(renderTarget());
    m_overlay->draw(renderTarget());
    m_vignette->draw();
}

std::string StateMenu::getName() const { return "State Menu"; }
void StateMenu::setLastTime(float s) { m_lastRunTime = s; }
