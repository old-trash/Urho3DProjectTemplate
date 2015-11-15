#pragma once
#include <Urho3D/Urho3DAll.h>

class MyLogicComponent : public LogicComponent
{
    URHO3D_OBJECT(MyLogicComponent, LogicComponent);

public:
    MyLogicComponent(Context* context);
    static void RegisterObject(Context* context);

private:
    virtual void Start();
    virtual void FixedUpdate(float timeStep);
};
