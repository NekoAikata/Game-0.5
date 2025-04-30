#ifndef TEXT_OBJECT
#define TEXT_OBJECT

#include "Game_Stat.h"

class Text_object
{
public:
    Text_object();
    ~Text_object();

    bool LoadFromRenderText (TTF_Font* font, SDL_Renderer* screen);
    void Free();

    void SetColor(Uint8 red, Uint8 blue, Uint8 green);
    void SetColor(SDL_Color sample);

    void RenderText(SDL_Renderer* screen,
                    int xp, int yp,
                    SDL_Rect* clip = 0,
                    double angle=0.0,
                    SDL_Point* center = NULL,
                    SDL_RendererFlip flip = SDL_FLIP_NONE);
    int GetWidth() {return width;}
    int GetHeight () {return height;}

    void SetText (const std::string& text) {content = text;}
    std::string GetText () const {return content;}
private:
    std::string content;
    SDL_Color text_color;
    SDL_Texture* texture;
    int width;
    int height;
};

#endif // TEXT_OBJECT
