#pragma once
#include <SFML/Graphics.hpp>
#include "SceneManager.h"

extern "C"
{
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
	#include <libavutil/imgutils.h>
}

using namespace sf;

class SceneManager;

namespace Graphics
{
	void SetBackground(const char* filename, const Vector2f& window_size, SceneManager* scene_manager);

	class Menu
	{
		float x_;												//координаты меню по X
		float y_;												//координаты меню по Y
		int menu_step_;											//расстояние между пунктами меню
		int font_size_;											//размер шрифта
		int selected_item_ = 0;									//номер текущего пункта меню 
		Font font_;												//шрифт меню 
		std::vector<Text*> menu_items_;							//названия пунктов меню
		Color text_color_;										//цвет пунктов меню
		Color choose_text_color_;								//цвет при выборе пункта меню
		Color border_color_;									//цвет обводки текста пунктов меню
		Color choose_border_color_;								//цвет обводки текста при выборе пункта меню
		float border_width_;									//величина обводки текста пунктов меню
		float choose_border_width_;								//величина обводки текста при выборе пункта меню
		SceneManager* manager_;									//указатель на менеджер сцен
		std::vector <RectangleShape*> background_;				//спрайт фона пункта меню
		RectangleShape* choose_background_ = nullptr;			//спрайт фона при выборе пункта меню

		void SetText(Text* text, const String& str, float xpos, float ypos) const;
		void MakeSelected();
		void MakeUnselected();

	public:
		
		Menu(SceneManager* manager, float x, float y, const std::vector<String>& name, const Font& font, 
			int font_size = 60, int menu_step = 80, unsigned char align = 0, const Color& text_color = Color::White,
			const Color& choose_text_color = Color::Red, float border_width = 0, const Color& border_color = Color::White,
			float choose_border_width = 0, const Color& choose_border_color = Color::White, 
			Texture* background = nullptr, Texture* choose_background = nullptr);
		void MoveUp();
		void MoveDown();
		int GetSelectedItemNumber();
	};

	void SetLine(float x1, float y1, float x2, float y2, float thickness, const Color& color, SceneManager* scene_manager);

	class VideoPlayer
	{
		float x_;												//координата плеера по x
		float y_;												//координата плеера по y
		String filename_;										//название первого файла, файлы следует называть: ###001.format
		AVFormatContext* format_context_ = nullptr;				//контекст формата (содержит видеофайл)
		AVCodecContext* codec_context_ = nullptr;				//контекст кодека (содержит кодек)
		const AVCodec* codec_ = nullptr;						//содержит параметры кодека
		AVFrame* frame_ = nullptr;								//кадр
		AVFrame* frame_inc_ = nullptr;							//кадр необработанных данных
		uint8_t* buffer_ = nullptr;								//буфер для хранения необработанных данных
		struct SwsContext* sws_context_ = nullptr;				//software scaling контекст
		AVPacket packet_;										//пакет необработанных данных потока
		int video_stream_ = -1;									//id потока видео
		Texture* texture_ = nullptr;							//изображение кадра
		RectangleShape* window_ = nullptr;						//окно видеоплеера

		SceneManager* manager_;									//менеджер сцен

		bool OpenInputMediaFile();
		bool OpenCodec();
		bool SetFrameStorage();
		bool ReadFrame();
		void SetSWSContext();
		void SaveFrame() const;
		void FreeVideoFile();
		void TransferFrameToSFML();

	public:

		VideoPlayer(float x, float y, const String& filename, SceneManager* manager);
		~VideoPlayer();
		void update();
	};

	void SetRectangle(float x, float y, float width, float height, SceneManager* scene_manager, 
		const Color& color = Color::Black, float outline_thickness = 0, const Color& outline_color = Color::Black);
};

namespace Animations
{
	class Blackening
	{
		float transparency_;									//прозрачность
		Time time_;												//время анимации
		char sign_;												//знак изменения прозрачности
		Clock clock_;											//таймер
		SceneManager* scene_manager_;							//указатель на менеджер сцен
		RectangleShape* rect_;									//маска анимации

	public:

		explicit Blackening(const Time& time, bool start, SceneManager* scene_manager);		//если start == true, то переход из чёрного в цвет, иначе из цвета в чёрный
		void update();
	};
}