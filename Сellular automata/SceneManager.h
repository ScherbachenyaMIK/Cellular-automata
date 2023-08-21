#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Graphics.h"
#include <list>

using namespace sf;

class SceneManager
{
	RenderWindow window;				//окно программы
	ContextSettings settings;			//настройки окна
	std::list <Drawable*> draws_;		//рисуемые объекты
	std::vector <Texture*> textures_;	//текстуры

public:

	SceneManager();

	void LoadLoadingScreen();
	int LoadMenu();
	static void LoadErrorMessage();
	void LoadStartScreen();
	void LoadOptions();
	void LoadAboutScreen();
	void LoadExitMessage();
	void ChangeScene(int next_scene);

	void AddDraw(Drawable* draw);
	void AddTexture(Texture* texture);
	void ClearDraws();
	void ClearTextures();
	bool RemoveDraw(Drawable* draw);
	bool ChangeDraw(Drawable* old_draw, Drawable* new_draw);
};

