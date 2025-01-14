#include "fighter.h"

Fighter::Fighter():
    Item(Asset(PATH_FIGHTER), FIGHTER_INIT_POSITION),
    currentWeapon(WeaponsEnum(BULLET)){
    itemId = FIGHTER;
    stopGoing();
    stopFiring();
    animationProcessor->shallRandomPictures(true);
    acceleration = FIGHTER_ACCELERATION;
    speed = FIGHTER_SPEED;
    stoppedImage = new Image(PATH_FIGHTER_STOPPED);
    initParticles();
}

Fighter::~Fighter(){
    clear_qptr(particles);
    clear_qptr(stoppedImage);
}

void Fighter::initParticles(){
    particles = new ParticlesProcessor(Asset(PATH_STEAM_S), 30, this);
    particles->getItemsModifier()->setOffset(FIGHTER_PARTICLES_OFFSET_X, FIGHTER_PARTICLES_OFFSET_Y);
    particles->getItemsModifier()->setDefaultScale(0.1);
    particles->getItemsModifier()->applyRotateEffect(2, 20, true);
    particles->getItemsModifier()->applyFadeEffect(0.04, 0.05);
    particles->getItemsModifier()->applyScaleEffect(0.04, 0.09);
    particles->setLooping(true);
    particles->setRadius(3);
    particles->setSpawnDelay(2);
    particles->start();
}

void Fighter::move(){
    if (isGoingLeft && x() > 0)
        go(DirectionsEnum(LEFT));
    else if (isGoingRight && x() <= SceneUtils::getInstance().getTranslatedWidth(100))
        go(DirectionsEnum(RIGHT));

    if (isGoingUp && y() > 0)
        go(DirectionsEnum(UP));
    else if (isGoingDown && y() <= SceneUtils::getInstance().getTranslatedHeight(100))
        go(DirectionsEnum(DOWN));
}

bool Fighter::isMoving(){
    return isGoingLeft || isGoingRight || isGoingUp || isGoingDown;
}

void Fighter::action(){

    if (opacity() <= 0)
        ressurect();

    QList<QPointer<Item> > collisions = getCollidingItems();

    if (!collisions.isEmpty())
        foreach (QPointer<Item> col, collisions)
            if (col->isDestroyable()){
                decreaseHealth(100);
                col->decreaseHealth(100);
                die();
                playSound("bomb2");
                return;
            }
    fire();
}

void Fighter::go(DirectionsEnum direction){

    switch(direction){
    case UP:
        moveBy(0, -acceleration);
        break;
    case DOWN:
        moveBy(0, acceleration);
        break;
    case LEFT:
        moveBy(-acceleration, 0);
        break;
    case RIGHT:
        moveBy(acceleration, 0);
        break;
    }
}

void Fighter::stopGoing(){
    isGoingUp = false;
    isGoingDown = false;
    isGoingLeft = false;
    isGoingRight = false;
}

void Fighter::controlKeyPress(QKeyEvent* event){

    if (!isDead()){

        switch(event->key()){
        case Qt::Key_Up:
            goUp();
            break;
        case Qt::Key_Left:
            goLeft();
            break;
        case Qt::Key_Right:
            goRight();
            break;
        case Qt::Key_Down:
            goDown();
            break;
        case Qt::Key_Control:
            currentWeapon = WeaponsEnum(ROCKET);
            fireRate = WEAPON_ROCKET_FIRE_RATE;
            break;
        case Qt::Key_Space:
            currentWeapon = WeaponsEnum(BULLET);
            fireRate = WEAPON_BULLET_FIRE_RATE;
            break;
        }
    }
}

void Fighter::controlKeyRelease(QKeyEvent* event){

    if (event->isAutoRepeat()){
        event->ignore();
        return;
    }

    if (!isDead()){

        switch(event->key()){
        case Qt::Key_Up:
            isGoingUp = false;
            break;
        case Qt::Key_Left:
            isGoingLeft = false;
            break;
        case Qt::Key_Right:
            isGoingRight = false;
            break;
        case Qt::Key_Down:
            isGoingDown = false;
            break;
        case Qt::Key_Control:
            stopFiring();
            break;
        case Qt::Key_Space:
            stopFiring();
            break;
        }

        event->accept();
    }
}

void Fighter::goUp(){
    isGoingUp = true;
    isGoingDown = false;
}

void Fighter::goDown(){
    isGoingDown = true;
    isGoingUp = false;
}

void Fighter::goRight(){
    isGoingRight = true;
    isGoingLeft = false;
}

void Fighter::goLeft(){
    isGoingLeft = true;
    isGoingRight = false;
}

void Fighter::fire(){

    if (fireRate && TimerUtils::getInstance().countEachFrame(fireRate)){

        QPointer<Weapon> weapon;

        switch(currentWeapon){
        case BULLET:
            weapon = new Bullet(this);
            break;
        case ROCKET:
            weapon = new Rocket(this);
            break;
        }
        if (weapon)
            weapon->start();
    }
}

void Fighter::die(){

    if (transformationEffects.empty()){

        stopMoving();
        stopFiring();

        ItemEffect fadeAway(this, ItemEffectType(FADE), 0.02);
        addEffect(fadeAway);

        ItemEffect rotation(this, ItemEffectType(ROTATE), 10);
        addEffect(rotation);

        ItemEffect scale(this, ItemEffectType(SCALE), -0.01);
        addEffect(scale);
    }
}

void Fighter::ressurect(){
    transformationEffects.clear();
    setPos(FIGHTER_INIT_POSITION);
    resetTransforationState();
    health = 100;
    show();
}

void Fighter::stopMoving(){
    isGoingDown = false;
    isGoingUp = false;
    isGoingRight = false;
    isGoingLeft = false;
}

void Fighter::stopFiring(){
    fireRate = 0;
}

void Fighter::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget){
    if (isMoving())
        Item::paint(painter, option, widget);
    else
        painter->drawImage(pos(), *stoppedImage);
}
