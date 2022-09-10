
#ifndef ALAKAJAM16_PIRATE_HPP
#define ALAKAJAM16_PIRATE_HPP

#include <animation.hpp>
#include <game_object.hpp>

class Pirate : public jt::GameObject {
public:
    std::shared_ptr<jt::Animation> m_anim { nullptr };

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // ALAKAJAM16_PIRATE_HPP
