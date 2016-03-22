#ifndef SPELLCARDSHOOT_H_INCLUDED
#define SPELLCARDSHOOT_H_INCLUDED

class Enemy;
class BulletStage;
class SpellCardShoot: public ShootBehavior {
private:
    float dt;
    float bulletDeg[7];
    Enemy* e;
public:
    SpellCardShoot(float dt, Enemy* e): dt(dt), e(e) {
        for(int i=0; i<7; i++)
            bulletDeg[i] = 0;
    }
    void operator() (BulletStage* stage, vec2f position) override;
    static SpellCardShoot* getInstance(float dt, Enemy* e);

};

#endif // SPELLCARDSHOOT_H_INCLUDED
