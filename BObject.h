#ifndef BASE_OBJECT
#define BASE_OBJECT

#include "Game_Stat.h"

class Object
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int &x, const int &y) {o_rect.x = x; o_rect.y = y}
    SDL_Rect GetRect() const {return o_rect;}
    SDL_Texture GetTexture() const {return texture;}

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Render(SDL_Renderer* design, const SDL_Rect* clip = NULL);
protected:
    SDL_Texture* texture;
    SDL_Rect o_rect
};

#endif // BASE_OBJECT
