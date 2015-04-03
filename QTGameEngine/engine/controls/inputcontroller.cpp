#include "engine/controls/inputcontroller.h"
#include "engine/utils/utils.h"

void InputController::controlKeyPress(QKeyEvent* event){
    if (controlableItem != NULL)
        controlableItem->controlKeyPress(event);

    switch(event->key()){
    case Qt::Key_Escape:
        Utils::getInstance().closeApplication();
        break;
    }
}

void InputController::controlKeyRelease(QKeyEvent* event){

    if (event->isAutoRepeat()){
        event->ignore();
        return;
    }

    if (controlableItem != NULL)
        controlableItem->controlKeyRelease(event);

    event->accept();
}

void InputController::setControlableItem(Controlable* item){
    controlableItem = item;
}
