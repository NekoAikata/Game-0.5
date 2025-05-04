#ifndef EXPLOSION
#define EXPLOSION

#include "BObject.h"
#include "Game_Stat.h"

class ExplosionObject : public BaseObject
{
public:
    ExplosionObject();
    ~ExplosionObject();

    void Clip();
    void set_frame(const int& frame_) {frame = frame_;}
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    int GetWidthFrame() const {return width_frame;}
    int GetHeigthFrame() const {return height_frame;}
    void Show(SDL_Renderer*screen);

private:
    int width_frame;
    int height_frame;

    int frame;
    SDL_Rect frame_clip[8];
};

#endif // EXPLOSION
