#ifndef PARTICLEEXPLOSION_H
#define PARTICLEEXPLOSION_H
#include "engine/utils/utils.h"
#include "game/resources.h"
#include "engine/items/item.h"
#include "engine/processors/particlesprocessor.h"
#include "game/constants.h"
#include "game/particles/particleexplosiondust.h"

class ParticleExplosion : public ParticleExplosionDust {

public:
    ParticleExplosion(QPointer<Item> owner, qreal offset = 0):
        ParticleExplosionDust(owner, offset){
        initFireballs(owner, PATH_FIREBALL, PATH_FIREBALL2, offset);
    }

    ParticleExplosion(QPointer<Item> owner, const QString fireBallPath1, const QString fireBallPath2, qreal offset = 0):
        ParticleExplosionDust(owner, offset){
        initFireballs(owner, fireBallPath1, fireBallPath2, offset);
    }

    ParticleExplosion(QPointer<Item> owner, const QString fireBallPath1, const QString fireBallPath2, qreal offset, QColor color):
        ParticleExplosionDust(owner, offset),
        fireball2Color(color){
        initFireballs(owner, fireBallPath1, fireBallPath2, offset);
    }

    virtual ~ParticleExplosion(){
        clear_qptr(fireball);
        clear_qptr(fireball2);
    }

private:
    QPointer<ParticlesProcessor> fireball;
    QPointer<ParticlesProcessor> fireball2;

    QColor fireball2Color;

    void initFireballs(QPointer<Item> owner, const QString fireBallPath1, const QString fireBallPath2, qreal offset = 0){
        fireball = new ParticlesProcessor(Asset(fireBallPath1),2, owner);
        fireball->getItemsModifier()->setOffset(offset,offset);
        fireball->getItemsModifier()->applyRotateEffect(5,5,true);
        fireball->getItemsModifier()->setDefaultScale(0.1);
        fireball->getItemsModifier()->applyScaleEffect(0.04, 0.04);
        fireball->getItemsModifier()->applyFadeEffect(0.02, 0.02);
        fireball->getItemsModifier()->moveEveryFrame(const_cast<QPointF&>(MOVE_LEFT_1));
        fireball->getItemsModifier()->addLightEffect(500,250,250);
        fireball->setLooping(false);
        fireball->setRadius(50);
        fireball->start();

        fireball2 = new ParticlesProcessor(Asset(fireBallPath2),2, owner);
        fireball2->getItemsModifier()->setOffset(offset,offset);
        fireball2->getItemsModifier()->applyRotateEffect(2,3,true);
        fireball2->getItemsModifier()->setDefaultScale(0.1);
        fireball2->getItemsModifier()->applyScaleEffect(0.05, 0.10);
        fireball2->getItemsModifier()->applyFadeEffect(0.02, 0.08);
        fireball2->getItemsModifier()->moveEveryFrame(const_cast<QPointF&>(MOVE_LEFT_1));
        fireball2->setLooping(false);
        fireball2->setRadius(50);
        fireball2->getItemsModifier()->addLightEffect(500,250,250);

        if (fireball2Color.isValid())
            fireball2->getItemsModifier()->setLightEffectColor(fireball2Color);

        fireball2->start();
    }

};

#endif // PARTICLEEXPLOSION_H
