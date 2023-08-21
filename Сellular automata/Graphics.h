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
		float x_;												//���������� ���� �� X
		float y_;												//���������� ���� �� Y
		int menu_step_;											//���������� ����� �������� ����
		int font_size_;											//������ ������
		int selected_item_ = 0;									//����� �������� ������ ���� 
		Font font_;												//����� ���� 
		std::vector<Text*> menu_items_;							//�������� ������� ����
		Color text_color_;										//���� ������� ����
		Color choose_text_color_;								//���� ��� ������ ������ ����
		Color border_color_;									//���� ������� ������ ������� ����
		Color choose_border_color_;								//���� ������� ������ ��� ������ ������ ����
		float border_width_;									//�������� ������� ������ ������� ����
		float choose_border_width_;								//�������� ������� ������ ��� ������ ������ ����
		SceneManager* manager_;									//��������� �� �������� ����
		std::vector <RectangleShape*> background_;				//������ ���� ������ ����
		RectangleShape* choose_background_ = nullptr;			//������ ���� ��� ������ ������ ����

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
		float x_;												//���������� ������ �� x
		float y_;												//���������� ������ �� y
		String filename_;										//�������� ������� �����, ����� ������� ��������: ###001.format
		AVFormatContext* format_context_ = nullptr;				//�������� ������� (�������� ���������)
		AVCodecContext* codec_context_ = nullptr;				//�������� ������ (�������� �����)
		const AVCodec* codec_ = nullptr;						//�������� ��������� ������
		AVFrame* frame_ = nullptr;								//����
		AVFrame* frame_inc_ = nullptr;							//���� �������������� ������
		uint8_t* buffer_ = nullptr;								//����� ��� �������� �������������� ������
		struct SwsContext* sws_context_ = nullptr;				//software scaling ��������
		AVPacket packet_;										//����� �������������� ������ ������
		int video_stream_ = -1;									//id ������ �����
		Texture* texture_ = nullptr;							//����������� �����
		RectangleShape* window_ = nullptr;						//���� �����������

		SceneManager* manager_;									//�������� ����

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
		float transparency_;									//������������
		Time time_;												//����� ��������
		char sign_;												//���� ��������� ������������
		Clock clock_;											//������
		SceneManager* scene_manager_;							//��������� �� �������� ����
		RectangleShape* rect_;									//����� ��������

	public:

		explicit Blackening(const Time& time, bool start, SceneManager* scene_manager);		//���� start == true, �� ������� �� ������� � ����, ����� �� ����� � ������
		void update();
	};
}