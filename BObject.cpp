#include "BObject.h"

BaseObject::BaseObject()
{
    texture = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    Free();
    SDL_Texture* new_texture = NULL;

    SDL_Surface* load_surface = IMG_Load(path.c_str());
    if (load_surface != NULL)
    {
        SDL_SetColorKey(load_surface,SDL_TRUE,SDL_MapRGB(load_surface->format,COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
        if (new_texture != NULL)
        {
            rect.w = load_surface->w;
            rect.h = load_surface->h;
        }
        else
        {
            std::cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(load_surface);
    } else
    {
        std::cerr << "IMG_Load Error: " << IMG_GetError() << std::endl;
    }
    texture = new_texture;
    return texture!=NULL;
}

void BaseObject::Render(SDL_Renderer* design, const SDL_Rect* clip/* = NULL*/)
{
    SDL_Rect renderquad = {rect.x, rect.y, rect.w, rect.h};
    SDL_RenderCopy(design, texture, clip, &renderquad);
}

void BaseObject::Free()
{
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        rect.w = 0;
        rect.h = 0;
    }
}
