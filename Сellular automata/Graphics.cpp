#include "Graphics.h"
#include <iostream>

void Graphics::SetBackground(const char* filename, const Vector2f& window_size, SceneManager* scene_manager)
{
    auto background = new RectangleShape(window_size);
    auto background_texture = new Texture;
    if (!background_texture->loadFromFile(filename, IntRect(0, 0, window_size.x, window_size.y)))
    {
        SceneManager::LoadErrorMessage();
    }
    background->setTexture(background_texture);
    background->setPosition(Vector2f(0, 0));
    scene_manager->AddDraw(background);
    scene_manager->AddTexture(background_texture);
}

void Graphics::Menu::SetText(Text* text, const String& str, float xpos, float ypos) const
{
    text->setFont(font_);
    text->setFillColor(text_color_);
    text->setString(str);
    text->setCharacterSize(font_size_);
    text->setPosition(xpos, ypos);
    text->setOutlineThickness(border_width_);
    text->setOutlineColor(border_color_);
}

void Graphics::Menu::MakeSelected()
{
    menu_items_[selected_item_]->setFillColor(choose_text_color_);
    menu_items_[selected_item_]->setCharacterSize(font_size_ * 1.2f);
    menu_items_[selected_item_]->setOutlineThickness(choose_border_width_);
    menu_items_[selected_item_]->setOutlineColor(choose_border_color_);
    if (choose_background_ != nullptr)
    {
        choose_background_->setSize(Vector2f(menu_items_[selected_item_]->getGlobalBounds().width + font_size_ / 8, menu_items_[selected_item_]->getGlobalBounds().height + font_size_ / 8));
        choose_background_->setPosition(menu_items_[selected_item_]->getPosition().x - font_size_ / 16, menu_items_[selected_item_]->getGlobalBounds().top - font_size_ / 16);
    }
}

void Graphics::Menu::MakeUnselected()
{
    menu_items_[selected_item_]->setFillColor(text_color_);
    menu_items_[selected_item_]->setCharacterSize(font_size_);
    menu_items_[selected_item_]->setOutlineThickness(border_width_);
    menu_items_[selected_item_]->setOutlineColor(border_color_);
}

Graphics::Menu::Menu(SceneManager* manager, float x, float y, const std::vector<String>& name, const Font& font,
    int font_size, int menu_step, unsigned char align, const Color& text_color, const Color& choose_text_color, 
    float border_width, const Color& border_color, float choose_border_width, const Color& choose_border_color,
    Texture* background, Texture* choose_background) :
    x_(x), y_(y), menu_step_(menu_step), font_size_(font_size), font_(font), text_color_(text_color), 
    choose_text_color_(choose_text_color), border_color_(border_color), choose_border_color_(choose_border_color), 
    border_width_(border_width), choose_border_width_(choose_border_width), manager_(manager)
{
    if (choose_background != nullptr)
    {
        manager_->AddTexture(choose_background);
        choose_background_ = new RectangleShape();
        choose_background_->setTexture(choose_background);
        manager_->AddDraw(choose_background_);
    }
    Text* text;
    if (background == nullptr)
    {
        for (int i = 0; i < name.size(); ++i)
        {
            text = new Text;
            SetText(text, name[i], x_, y_ + i * menu_step_);
            menu_items_.push_back(text);
            manager_->AddDraw(text);
        }
    }
    else
    {
        for (int i = 0; i < name.size(); ++i)   //не протестировано!!!
        {
            text = new Text;
            SetText(text, name[i], x_, y_ + i * menu_step_);
            menu_items_.push_back(text);
            manager_->AddTexture(background);
            auto background_shape = new RectangleShape(Vector2f(text->getGlobalBounds().width + font_size_ / 8, text->getGlobalBounds().height + font_size_ / 8));
            background_shape->setTexture(background);
            background_shape->setPosition(text->getPosition().x - font_size_ / 16, text->getGlobalBounds().top - font_size_ / 16);
            background_.push_back(background_shape);
            manager_->AddDraw(background_[i]);
            manager_->AddDraw(text);
        }
    }
    float x_offset = 0;
    for (auto i : menu_items_)                          //выравнивание: 0 - слева, 1 - справа, 2 - по центру
    {
        switch (align)
        {
        case 1:
            x_offset = i->getLocalBounds().width;
            break;
        case 2:
            x_offset = i->getLocalBounds().width / 2;
            break;
        default:
            x_offset = 0;
            break;

        }
        i->setPosition(i->getPosition().x - x_offset, i->getPosition().y);
    }
    MakeSelected();
}

void Graphics::Menu::MoveUp()
{
    MakeUnselected();
    if (--selected_item_ < 0)
    {
        selected_item_ = menu_items_.size() - 1;
    }
    MakeSelected();
}

void Graphics::Menu::MoveDown()
{
    MakeUnselected();
    if (++selected_item_ >= menu_items_.size())
    {
        selected_item_ = 0;
    }
    MakeSelected();
}

int Graphics::Menu::GetSelectedItemNumber()
{
    return selected_item_;
}

void Graphics::SetLine(float x1, float y1, float x2, float y2, float thickness, const Color& color, SceneManager* scene_manager)
{
    auto line = new RectangleShape(Vector2f(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)), thickness));
    auto angle = atan2f(abs(y1 - y2), abs(x1 - x2));
    line->setRotation(angle * 180);
    line->setFillColor(color);
    if (angle * 180 >= 0 && angle * 180 <= 90)
    {
        x2 += thickness / 2 * sin(angle);
        y2 -= thickness / 2 * cos(angle);
    }
    else
    {
        if (angle * 180 >= 90 && angle * 180 <= 180)
        {
            x2 += thickness / 2 * sin(angle);
            y2 += thickness / 2 * cos(angle);
        }
        else
        {
            if (angle * 180 >= 180 && angle * 180 <= 270)
            {
                x2 -= thickness / 2 * sin(angle);
                y2 += thickness / 2 * cos(angle);
            }
            else
            {
                if (angle * 180 >= 270 && angle * 180 <= 360)
                {
                    x2 -= thickness / 2 * sin(angle);
                    y2 -= thickness / 2 * cos(angle);
                }
            }
        }
    }
    line->setPosition(x2, y2);
    scene_manager->AddDraw(line);
}

Animations::Blackening::Blackening(const Time& time, bool start, SceneManager* scene_manager) : time_(time), scene_manager_(scene_manager)
{
    if (start)
    {
        transparency_ = 255;
        sign_ = -1;
    }
    else
    {
        transparency_ = 0;
        sign_ = 1;
    }
    rect_ = new RectangleShape(Vector2f(1920, 1080));
    rect_->setFillColor(Color(0, 0, 0, transparency_));
    rect_->setPosition(Vector2f(0, 0));
    scene_manager_->AddDraw(rect_);
    clock_.restart();
}

void Animations::Blackening::update()
{
    transparency_ += static_cast<long double>(clock_.getElapsedTime().asMicroseconds()) / time_.asMicroseconds() * (255 * sign_);
    clock_.restart();
    if (transparency_ > 255 && sign_ > 0)
    {
        transparency_ = 255;
        sign_ = 0;
    }
    if (transparency_ < 0 && sign_ < 0)
    {
        transparency_ = 0;
        sign_ = 0;
    }
    rect_->setFillColor(Color(0, 0, 0, transparency_));
}

bool Graphics::VideoPlayer::OpenInputMediaFile()
{
    int response;
    format_context_ = avformat_alloc_context();
    if (!format_context_)
    {
        return false;
    }
    response = avformat_open_input(&format_context_, filename_.toAnsiString().c_str(), nullptr, nullptr);
    if (response != 0)
    {
        return false;
    }
    response = avformat_find_stream_info(format_context_, nullptr);
    if (response < 0)
    {
        return false;
    }
    return true;
}

bool Graphics::VideoPlayer::SetFrameStorage()
{
    frame_inc_ = av_frame_alloc();
    frame_ = av_frame_alloc();
    if (frame_ == nullptr)
    {
        return false;
    }
    int numBytes;
    numBytes = av_image_get_buffer_size(AV_PIX_FMT_RGBA, codec_context_->width, codec_context_->height, 1);
    buffer_ = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));
    av_image_fill_arrays(frame_->data, frame_->linesize, buffer_, AV_PIX_FMT_RGBA, codec_context_->width, codec_context_->height, 1);
    return true;
}

bool Graphics::VideoPlayer::ReadFrame()
{
    bool result;
    do
    {
        result = av_read_frame(format_context_, &packet_) == 0;
    } while (result && packet_.stream_index != video_stream_);
    if (!result)
    {
        return false;
    }
    if (avcodec_send_packet(codec_context_, &packet_) == 0 && avcodec_receive_frame(codec_context_, frame_inc_) == 0)
    {
        sws_scale(sws_context_, (uint8_t const* const*)frame_inc_->data,
                    frame_inc_->linesize, 0, codec_context_->height,
                    frame_->data, frame_->linesize);

        TransferFrameToSFML();
    }
    else
    {
        return false;
    }
    av_packet_unref(&packet_);
    return true;
}

void Graphics::VideoPlayer::SetSWSContext()
{
    sws_context_ = sws_getContext(codec_context_->width, 
        codec_context_->height, 
        codec_context_->pix_fmt,
        codec_context_->width, 
        codec_context_->height,
        AV_PIX_FMT_RGBA,
        SWS_BILINEAR,
        nullptr,
        nullptr,
        nullptr
    );
}

void Graphics::VideoPlayer::SaveFrame() const                   //эта функция нужна для тестировки
{
    FILE* file;
    file = fopen("temp.ppm", "wb");
    if (file == nullptr)
    {
        return;
    }
    fprintf(file, "P6\n%d %d\n255\n", codec_context_->width, codec_context_->height);
    for (int y = 0; y < codec_context_->height; y++)
    {
        fwrite(frame_->data[0] + y * frame_->linesize[0], 1, codec_context_->width * 3, file);
    }
    fclose(file);
}

void Graphics::VideoPlayer::FreeVideoFile()
{
    av_free(buffer_);
    av_free(frame_);
    av_free(frame_inc_);
    avcodec_close(codec_context_);
    avformat_close_input(&format_context_);
}

void Graphics::VideoPlayer::TransferFrameToSFML()
{
    Image image_;
    image_.create(codec_context_->width, codec_context_->height, frame_->data[0]);
    texture_->loadFromImage(image_);
    window_->setTexture(texture_);
}

void Graphics::VideoPlayer::update()
{
    if (!ReadFrame())
    {
        FreeVideoFile();
        int i;
        for (i = 0; filename_[filename_.getSize() - 5 - i] == '9' && i < 3; ++i)
        {
            filename_[filename_.getSize() - 5 - i] = '0';
        }
        ++filename_[filename_.getSize() - 5 - i];
        bool error = true;
        error = OpenInputMediaFile();
        if (!error)
        {
            filename_.replace(filename_.getSize() - 7, 3, L"001");
        }
        OpenInputMediaFile();
        if (!OpenCodec())
        {
            SceneManager::LoadErrorMessage();
        }
        if (!SetFrameStorage())
        {
            SceneManager::LoadErrorMessage();
        }
        SetSWSContext();
    }
}

bool Graphics::VideoPlayer::OpenCodec()
{
    codec_context_ = avcodec_alloc_context3(nullptr);
    for (int i = 0; i < format_context_->nb_streams; i++)
    {
        if (format_context_->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            video_stream_ = i;
            break;
        }
    }
    if (video_stream_ == -1)
    {
        return false;
    }
    avcodec_parameters_to_context(codec_context_, format_context_->streams[video_stream_]->codecpar);
    codec_ = avcodec_find_decoder(codec_context_->codec_id);
    if (codec_ == nullptr) 
    {
        return false;
    }
    if (avcodec_open2(codec_context_, codec_, nullptr) < 0)
    {
        return false;
    }
    return true;
}

Graphics::VideoPlayer::VideoPlayer(float x, float y, const String& filename, SceneManager* manager) : x_(x), y_(y), filename_(filename), manager_(manager)
{
    if (!OpenInputMediaFile())
    {
        SceneManager::LoadErrorMessage();
    }
    if (!OpenCodec())
    {
        SceneManager::LoadErrorMessage();
    }
    if (!SetFrameStorage())
    {
        SceneManager::LoadErrorMessage();
    }
    SetSWSContext();
    texture_ = new Texture();
    manager_->AddTexture(texture_);
    window_ = new RectangleShape(Vector2f(codec_context_->width, codec_context_->height));
    window_->setPosition(x_, y_);
    manager_->AddDraw(window_);
}

Graphics::VideoPlayer::~VideoPlayer()
{
    FreeVideoFile();
}

void Graphics::SetRectangle(float x, float y, float width, float height, SceneManager* scene_manager,
    const Color& color, float outline_thickness, const Color& outline_color)
{
    auto menu_background = new RectangleShape(Vector2f(width, height));
    menu_background->setPosition(x, y);
    menu_background->setFillColor(color);
    menu_background->setOutlineThickness(outline_thickness);
    menu_background->setOutlineColor(outline_color);
    scene_manager->AddDraw(menu_background);
}