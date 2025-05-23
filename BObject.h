#ifndef BASE_OBJECT
#define BASE_OBJECT

#include "Game_Stat.h"
#include <string>

class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int &x, const int &y) {rect.x = x, rect.y = y;}
    void SetRectWH(const int &w, const int &h) {rect.w = w, rect.h = h;}
    SDL_Rect GetRect() const {return rect;}
    SDL_Texture* GetTexture() const {return texture;}

    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* design, const SDL_Rect* clip = NULL);
    void Free();
protected:
    SDL_Texture* texture;
    SDL_Rect rect;
};

#endif // BASE_OBJECT
