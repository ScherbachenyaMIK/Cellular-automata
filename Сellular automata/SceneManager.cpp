#include "SceneManager.h"

SceneManager::SceneManager()
{
    settings.antialiasingLevel = 8;
    window.create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Cellular automata", Style::None, settings);
}

void SceneManager::LoadLoadingScreen()
{
    window.setMouseCursorVisible(false);
    Graphics::SetBackground("Resources\\Loading screen FullHD.tga", Vector2f(1920, 1080), this);
    Clock clock;
    Animations::Blackening black(seconds(1), true, this);
    do
    {
        black.update();
        window.clear();
        for (auto i : draws_)
        {
            window.draw(*i);
        }
        window.display();
    } while (clock.getElapsedTime().asMilliseconds() <= milliseconds(1700).asMilliseconds());
    clock.restart();
    Animations::Blackening black2(seconds(1), false, this);
    do
    {
        black2.update();
        window.clear();
        for (auto i : draws_)
        {
            window.draw(*i);
        }
        window.display();
    } while (clock.getElapsedTime().asMilliseconds() <= milliseconds(1100).asMilliseconds());
    ClearDraws();
    ClearTextures();
    window.setMouseCursorVisible(true);
}

int SceneManager::LoadMenu()
{
    Clock clock_controls;
    Clock clock_video;
    Font font;
    if (!font.loadFromFile("Resources\\Fonts\\corbel.ttf"))
    {
        SceneManager::LoadErrorMessage();
    }
    Graphics::VideoPlayer background(0, 0, "Resources\\Video\\Menu-background-FullHD-001.mp4", this);
    Graphics::SetRectangle(920, 295, 888, 520, this, Color(86, 3, 25, 255));
    Graphics::VideoPlayer player(940, 315, "Resources\\Video\\Menu-FullHD-001.mp4", this);
    Graphics::SetRectangle(0, 0, 840, 1080, this, Color(86, 3, 25, 255), 18, Color(100, 35, 47, 255));
    Graphics::SetRectangle(142, 215, 565, 620, this, Color(100, 35, 47, 255));
    Graphics::Menu menu(this, 157, 230, { L"Start", L"Options", L"About us", L"Exit" }, font, 120, 140);
    while (window.isOpen())
    {
        Event event;
        window.pollEvent(event);
        if (event.type == Event::KeyPressed && clock_controls.getElapsedTime().asMilliseconds() >= milliseconds(200).asMilliseconds())
        {
            switch (event.key.code)
            {
            case Keyboard::Escape:
                LoadExitMessage();
                break;
            case Keyboard::Up:
                menu.MoveUp();
                break;
            case Keyboard::Down:
                menu.MoveDown();
                break;
            case Keyboard::Return:
                if (menu.GetSelectedItemNumber() == 3)
                {
                    LoadExitMessage();
                }
                else
                {
                    return menu.GetSelectedItemNumber() + 1;
                }
            default:
                break;
            }
            clock_controls.restart();
        }
        if(clock_video.getElapsedTime().asMicroseconds() >= microseconds(16667).asMicroseconds())
        {
            background.update();
            player.update();
            clock_video.restart();
        }
        window.clear();
        for (auto i : draws_)
        {
            window.draw(*i);
        }
        window.display();
    }
    return 0;
}

void SceneManager::LoadErrorMessage()
{
}

void SceneManager::LoadStartScreen()
{
}

void SceneManager::LoadOptions()
{
}

void SceneManager::LoadAboutScreen()
{
}

void SceneManager::LoadExitMessage()
{
    window.close();
}

void SceneManager::ChangeScene(int next_scene)
{
    while (window.isOpen())
    {
        LoadLoadingScreen();
        switch (next_scene)
        {
        case 0:
            next_scene = LoadMenu();
            break;
        case 1:
            LoadStartScreen();
            next_scene = 0;
            break;
        case 2:
            LoadOptions();
            next_scene = 0;
            break;
        case 3:
            LoadAboutScreen();
            next_scene = 0;
            break;
        default:
            LoadErrorMessage();
            next_scene = 0;
        }
        ClearDraws();
        ClearTextures();
    }
}

void SceneManager::AddDraw(Drawable* draw)
{
    draws_.push_back(draw);
}

void SceneManager::AddTexture(Texture* texture)
{
    textures_.push_back(texture);
}

void SceneManager::ClearDraws()
{
    for (auto i : draws_)
    {
        delete i;
    }
    draws_.clear();
}

void SceneManager::ClearTextures()
{
    for (auto i : textures_)
    {
        delete i;
    }
    textures_.clear();
}

bool SceneManager::RemoveDraw(Drawable* draw)
{
    for (auto i = draws_.begin(); i != draws_.end(); ++i)
    {
        if (*i == draw)
        {
            delete *i;
            draws_.erase(i);
            return true;
        }
    }
    return false;
}

bool SceneManager::ChangeDraw(Drawable* old_draw, Drawable* new_draw)
{
    for (auto i = draws_.begin(); i != draws_.end(); ++i)
    {
        if (*i == old_draw)
        {
            delete *i;
            *i = new_draw;
            return true;
        }
    }
    return false;
}
