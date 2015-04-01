#ifndef ITEMSMODIFIER_H
#define ITEMSMODIFIER_H
#include <QList>
#include <QPointer>
#include "engine/utils/itemutils.h"

class ItemsModifier : public QObject {

public:
    ItemsModifier(QList<QPointer<Item> >& attachedItems):
        items(attachedItems){
        qDebug() << "Attaching items: " << items.size();
    }

    void makeVisible(boolean condition){
        ItemUtils::getInstance().makeVisible(items, condition);
    }

    void moveEveryFrame(QPointF& move){
        ItemUtils::getInstance().moveEveryFrame(items, move);
    }

    void rotate(int minAngle, int maxAngle, bool allowNegative, int interval = 1){
        ItemUtils::getInstance().rotate(items, minAngle, maxAngle, allowNegative, interval);
    }

    void fadeAway(qreal minSpeed, qreal maxSpeed, int interval = 1){
        ItemUtils::getInstance().fadeAway(items, minSpeed, maxSpeed, interval);
    }

    void scale(qreal minSpeed, qreal maxSpeed, int interval = 1){
        ItemUtils::getInstance().scale(items, minSpeed, maxSpeed, interval);
    }

    void setInitialScale(qreal scale){
       ItemUtils::getInstance().setInitialScale(items, scale);
    }

    void setInitialOpacity(qreal opacity){
       ItemUtils::getInstance().setInitialOpacity(items, opacity);
    }

    void stop(){
        ItemUtils::getInstance().stop(items);
    }

    void start(){
        ItemUtils::getInstance().start(items);
    }

    void setVisible(boolean value){
       ItemUtils::getInstance().setVisible(items, value);
    }

    void setStarted(boolean value){
       ItemUtils::getInstance().setStarted(items, value);
    }

    void setPos(QPointF& pos){
       ItemUtils::getInstance().setPos(items, pos);
    }

    void setBias(qreal x, qreal y){
        ItemUtils::getInstance().setBias(items, x, y);
    }

    void setDestroyable(bool value){
       ItemUtils::getInstance().setDestroyable(items, value);
    }

    void setRepeatable(bool value){
        ItemUtils::getInstance().setRepeatable(items, value);
    }

    void shallBlink(bool value, int minFrequency, int maxFrequency){
        ItemUtils::getInstance().shallBlink(items, value, minFrequency, maxFrequency);
    }

    void addLightEffect(int radius, int biasX = 0, int biasY = 0){
        ItemUtils::getInstance().addLightEffect(items, radius, biasX, biasY);
    }

private:
    QList<QPointer<Item> > items;
};

#endif // ITEMSMODIFIER_H
