/*
    Переменные, которые будут сохранены в файл
*/

#pragma once
#include <Urho3D/Urho3DAll.h>

class Config : public Object
{
    URHO3D_OBJECT(Config, Object);

private:
    // Путь для сохранения конфига
    String GetConfigFileName();

    // Загружает конфиг (вызывается в конструкторе)
    void Load();

public:
    Config(Context* context);

    // Сохранение конфига в файл
    void Save();

    // Значениями по умолчанию задаются тут
    int windowWidth_ = 800;
    int windowHeight_ = 600;
    bool fullscreen_ = false;
    bool borderless_ = false;
};
