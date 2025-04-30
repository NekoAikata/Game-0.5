#include "Text.h"

Text_object::Text_object()
{
    text_color.r = 255;
    text_color.b = 255;
    text_color.g = 255;
    width = 0; height = 0;
    texture = NULL;
}

Text_object::~Text_object()
{

}

bool Text_object::LoadFromRenderText (TTF_Font* font, SDL_Renderer* screen)
{
    SDL_Surface* text_surface = TTF_RenderText_Solid(font, content.c_str(), text_color);
    if(text_surface)
    {
        texture = SDL_CreateTextureFromSurface(screen,text_surface);
        width = text_surface->w;
        height = text_surface->h;

        SDL_FreeSurface(text_surface);
    }
    return texture!=NULL;
}

void Text_object::Free()
{
    if(texture!= NULL)
    {
        SDL_DestroyTexture(texture);
        texture=NULL;
    }
}

void Text_object::SetColor(Uint8 red, Uint8 blue, Uint8 green)
{
    text_color.r = red;
    text_color.b = blue;
    text_color.g = green;
}

void Text_object::SetColor(SDL_Color sample)
{
    text_color = sample;
}

void Text_object::RenderText(SDL_Renderer* screen,
                    int xp, int yp,
                    SDL_Rect* clip,
                    double angle,
                    SDL_Point* center,
                    SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {xp, yp, width, height};
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center, flip);
}
