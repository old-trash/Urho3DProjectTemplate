#include "MyLogicComponent.h"

MyLogicComponent::MyLogicComponent(Context* context) : LogicComponent(context)
{
    SetUpdateEventMask(USE_FIXEDUPDATE);
}

void MyLogicComponent::RegisterObject(Context* context)
{
    context->RegisterFactory<MyLogicComponent>();
}

void MyLogicComponent::Start()
{
}

void MyLogicComponent::FixedUpdate(float timeStep)
{
}
