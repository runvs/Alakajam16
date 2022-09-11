#ifndef GAME_GAMEPROPERTIES_HPP
#define GAME_GAMEPROPERTIES_HPP

#include <color/color.hpp>
#include <color/make_color.hpp>
#include <color/palette.hpp>
#include <vector.hpp>
#include <string>

class GP {
public:
    GP() = delete;

    static std::string GameName() { return ""; }
    static std::string AuthorName() { return "Laguna_999 and BloodyOrange"; }
    static std::string JamName() { return "Alakajam 16"; }
    static std::string JamDate() { return "2022-09-11"; }
    static std::string ExplanationText() { return ""; }

    static jt::Vector2f GetWindowSize() { return jt::Vector2f { 1200, 800 }; }
    static float GetZoom() { return 5.0f; }
    static jt::Vector2f GetScreenSize() { return GetWindowSize() * (1.0f / GetZoom()); }

    static jt::Color PaletteBackground() { return GP::getPalette().getColor(5); }
    static jt::Color PaletteFontFront() { return GP::getPalette().getColor(0); }
    static jt::Color PalleteFrontHighlight() { return GP::getPalette().getColor(1); }
    static jt::Color PaletteFontShadow() { return GP::getPalette().getColor(6); }
    static jt::Color PaletteFontCredits() { return jt::MakeColor::FromHexString("053914"); }

    static jt::Palette getPalette();

    static jt::Vector2f PlayerSize();
    static jt::Vector2f PiratePosition();
    static jt::Vector2f QueueOffset();
    static jt::Vector2f ParrotPosition();
};

#endif
