/*
    Главный класс
*/

#include "Global.h"
#include "Consts.h"

#include <Urho3D/Urho3DAll.h>

class Game : public Application
{
    URHO3D_OBJECT(Game, Application);

public:
    Game(Context* context) : Application(context)
    {
        context_->RegisterSubsystem(global = new Global(context_)); // Тут загружается конфиг
        SubscribeToEvent(E_BEGINFRAME, URHO3D_HANDLER(Game, ApplyGameState));
    }

    void Setup() override
    {
        FileSystem* fs = GetSubsystem<FileSystem>();

        engineParameters_[EP_WINDOW_TITLE] = APP_NAME;
        engineParameters_[EP_FULL_SCREEN] = CONFIG->fullscreen_;
        engineParameters_[EP_WINDOW_WIDTH] = CONFIG->windowWidth_;
        engineParameters_[EP_WINDOW_HEIGHT] = CONFIG->windowHeight_;
        engineParameters_[EP_BORDERLESS] = CONFIG->borderless_;
        //engineParameters_[EP_LOG_NAME] = fs->GetAppPreferencesDir(COMPANY_NAME, APP_NAME) + "Log.txt";
        //engineParameters_[EP_RESOURCE_PATHS] = "GameData;Data;CoreData";
    }

    void Start() override
    {
        InitGlobal(context_);
        input->SetToggleFullscreen(false);

        SubscribeToEvent(E_SCREENMODE, URHO3D_HANDLER(Game, HandleScreenMode));
    }

    // Тут меняем текущуюу сцену и состояние игры
    void ApplyGameState(StringHash eventType, VariantMap& eventData)
    {
        if (global->gameState_ == global->neededGameState_)
            return;

        if (global->gameState_ == GameState::MainMenu && global->neededGameState_ == GameState::Play)
        {
            // ...
        }

        global->gameState_ = global->neededGameState_;
    }

    void HandleScreenMode(StringHash eventType, VariantMap& eventData)
    {
        CONFIG->fullscreen_ = eventData[ScreenMode::P_FULLSCREEN].GetBool();
        CONFIG->borderless_ = eventData[ScreenMode::P_BORDERLESS].GetBool();
        CONFIG->windowWidth_ = eventData[ScreenMode::P_WIDTH].GetInt();
        CONFIG->windowHeight_ = eventData[ScreenMode::P_HEIGHT].GetInt();
    }

    void Stop() override
    {
        // Сохраняем конфиг при выходе из игры
        CONFIG->Save();
    }
};

URHO3D_DEFINE_APPLICATION_MAIN(Game)
