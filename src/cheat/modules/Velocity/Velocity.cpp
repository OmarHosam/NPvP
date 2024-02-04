#include "Velocity.h"
#include "../../net/minecraft/entity/Entity.h"

void Velocity::runModule()
{
    if (C_Entity::getHurtResistantTime() > 0) {
        jdouble motionX = C_Entity::getMotionX();
        jdouble motionY = C_Entity::getMotionY();
        jdouble motionZ = C_Entity::getMotionZ();

        motionX *= 0.5;
        motionY *= 0.5;
        motionZ *= 0.5;
        
        // worst implementation possible
        C_Entity::setMotionX(motionX);
        C_Entity::setMotionY(motionY);
        C_Entity::setMotionZ(motionZ);
    }
}
