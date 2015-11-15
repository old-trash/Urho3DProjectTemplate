#include "Global.h"

class Main : public Application
{
    URHO3D_OBJECT(Main, Application);

public:
    SharedPtr<Scene> scene_;
    SharedPtr<Node> cameraNode_;
    float yaw_ = 0.0f;
    float pitch_ = 0.0f;

    Main(Context* context) : Application(context)
    {
        SubscribeToEvent(E_BEGINFRAME, URHO3D_HANDLER(Main, ApplyGameState));
    }

    void Setup()
    {
        engineParameters_[EP_WINDOW_TITLE] = "Urho3D";
        //engineParameters_[EP_LOG_NAME] = FILE_SYSTEM->GetAppPreferencesDir("urho3d", "logs") + GetTypeName() + ".log";
        engineParameters_[EP_FULL_SCREEN] = false;
        engineParameters_[EP_WINDOW_WIDTH] = 800;
        engineParameters_[EP_WINDOW_HEIGHT] = 600;
        //engineParameters_[EP_RESOURCE_PATHS] = "MyData;Data;CoreData";
    }

    void Start()
    {
        InitGlobal(context_);

        CreateScene();
        SetupViewport();
        SubscribeToEvents();
    }

    void SetupViewport()
    {
        Camera* camera = cameraNode_->GetComponent<Camera>();
        SharedPtr<Viewport> viewport(new Viewport(context_, scene_, camera));
        renderer->SetViewport(0, viewport);
    }

    void ApplyGameState(StringHash eventType, VariantMap& eventData)
    {
        /*if (GLOBAL->gameState_ == GLOBAL->neededGameState_)
            return;

        if (GLOBAL->gameState_ == GS_INIT)
        {

        }

        GLOBAL->gameState_ = GLOBAL->neededGameState_;
        UpdateUIVisibility();*/
    }

    void UpdateUIVisibility()
    {
        /*String tag;
        if (GLOBAL->gameState_ == GS_INIT)             tag = "Init";
        else if (GLOBAL->gameState_ == GS_GAMEPLAY)    tag = "Gameplay";

        auto uiElements = UI_ROOT->GetChildren();
        for (auto i = uiElements.Begin(); i != uiElements.End(); i++)
        {
            auto element = *i;
            element->SetVisible(element->HasTag(tag));
        }*/
    }

    void CreateScene()
    {
        scene_ = new Scene(context_);
        scene_->CreateComponent<Octree>();

        Node* planeNode = scene_->CreateChild("Plane");
        planeNode->SetScale(Vector3(100.0f, 1.0f, 100.0f));
        StaticModel* planeObject = planeNode->CreateComponent<StaticModel>();
        planeObject->SetModel(GET_MODEL("Models/Plane.mdl"));
        planeObject->SetMaterial(GET_MATERIAL("Materials/StoneTiled.xml"));

        Node* lightNode = scene_->CreateChild("DirectionalLight");
        lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f));
        Light* light = lightNode->CreateComponent<Light>();
        light->SetColor(Color(0.5f, 0.5f, 0.5f));
        light->SetLightType(LIGHT_DIRECTIONAL);
        light->SetCastShadows(true);
        light->SetShadowBias(BiasParameters(0.00025f, 0.5f));
        light->SetShadowCascade(CascadeParameters(10.0f, 50.0f, 200.0f, 0.0f, 0.8f));
        //light->SetShadowIntensity(0.5f);

        Node* zoneNode = scene_->CreateChild("Zone");
        Zone* zone = zoneNode->CreateComponent<Zone>();
        zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
        zone->SetAmbientColor(Color(0.5f, 0.5f, 0.5f));
        zone->SetFogColor(Color(0.4f, 0.5f, 0.8f));
        zone->SetFogStart(100.0f);
        zone->SetFogEnd(300.0f);

        const unsigned NUM_OBJECTS = 200;
        for (unsigned i = 0; i < NUM_OBJECTS; ++i)
        {
            Node* mushroomNode = scene_->CreateChild("Mushroom");
            mushroomNode->SetPosition(Vector3(Random(90.0f) - 45.0f, 0.0f, Random(90.0f) - 45.0f));
            mushroomNode->SetRotation(Quaternion(0.0f, Random(360.0f), 0.0f));
            mushroomNode->SetScale(0.5f + Random(2.0f));
            StaticModel* mushroomObject = mushroomNode->CreateComponent<StaticModel>();
            mushroomObject->SetModel(GET_MODEL("Models/Mushroom.mdl"));
            mushroomObject->SetMaterial(GET_MATERIAL("Materials/Mushroom.xml"));
            mushroomObject->SetCastShadows(true);
        }

        cameraNode_ = scene_->CreateChild("Camera");
        cameraNode_->CreateComponent<Camera>();
        cameraNode_->SetPosition(Vector3(0.0f, 5.0f, 0.0f));
    }

    void MoveCamera(float timeStep)
    {
        // Не двигаем камеру, если есть активный UI-элемент (консоль).
        if (ui->GetFocusElement())
            return;

        const float MOVE_SPEED = 20.0f;
        const float MOUSE_SENSITIVITY = 0.1f;

        IntVector2 mouseMove = input->GetMouseMove();
        yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
        pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
        pitch_ = Clamp(pitch_, -90.0f, 90.0f);

        cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));

        if (input->GetKeyDown('W'))
            cameraNode_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
        if (input->GetKeyDown('S'))
            cameraNode_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
        if (input->GetKeyDown('A'))
            cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
        if (input->GetKeyDown('D'))
            cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);
    }

    void SubscribeToEvents()
    {
        SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(Main, HandleUpdate));
    }

    void HandleUpdate(StringHash eventType, VariantMap& eventData)
    {
        using namespace Update;
        float timeStep = eventData[P_TIMESTEP].GetFloat();

        if (input->GetKeyPress(KEY_F1))
            console->Toggle();

        if (input->GetKeyPress(KEY_F2))
            debugHud->ToggleAll();

        MoveCamera(timeStep);
    }
};

URHO3D_DEFINE_APPLICATION_MAIN(Main)
