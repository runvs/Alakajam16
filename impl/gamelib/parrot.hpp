#ifndef ALAKAJAM16_PARROT_HPP
#define ALAKAJAM16_PARROT_HPP
#include <animation.hpp>
#include <game_object.hpp>

class Parrot : public jt::GameObject {
public:
    std::shared_ptr<jt::Animation> m_anim { nullptr };

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // ALAKAJAM16_PARROT_HPP
