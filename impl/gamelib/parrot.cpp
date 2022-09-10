
#include "parrot.hpp"
#include <game_properties.hpp>

void Parrot::doCreate()
{
    m_anim = std::make_shared<jt::Animation>();
    m_anim->loadFromJson("assets/Parrot.json", textureManager());
    m_anim->play("idle");
    m_anim->setPosition(GP::ParrotPosition());
}
void Parrot::doUpdate(float const elapsed) { m_anim->update(elapsed); }
void Parrot::doDraw() const { m_anim->draw(renderTarget()); }
