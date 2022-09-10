
#include "pirate.hpp"
#include <game_properties.hpp>

void Pirate::doCreate()
{
    m_anim = std::make_shared<jt::Animation>();
    m_anim->loadFromJson("assets/Pirate.json", textureManager());
    m_anim->play("idle3");
    m_anim->setPosition(GP::PiratePosition());
}
void Pirate::doUpdate(float const elapsed) { m_anim->update(elapsed); }
void Pirate::doDraw() const { m_anim->draw(renderTarget()); }
