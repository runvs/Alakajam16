#include "game_properties.hpp"

jt::Palette GP::getPalette()
{
    static auto const p = jt::Palette::parseGPL(R"(GIMP Palette
#Palette Name: Dreamscape8
#Description: A palette made of low saturation colours to give your art a dreamlike quality. 
#Colors: 8
201	204	161	c9cca1
202	160	90	caa05a
174	106	71	ae6a47
139	64	73	8b4049
84	51	68	543344
81	82	98	515262
99	120	125	63787d
142	160	145	8ea091
)");
    return p;
}

jt::Vector2f GP::PlayerSize() { return jt::Vector2f { 16.0f, 16.0f }; }
jt::Vector2f GP::PiratePosition() { return jt::Vector2f { 64.0f, 110.0f }; }
jt::Vector2f GP::ParrotPosition() { return jt::Vector2f { 108.0f, 102.0f }; }
jt::Vector2f GP::QueueOffset() { return jt::Vector2f { 30.0f, 80.0f }; }
