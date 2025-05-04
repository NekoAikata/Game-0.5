#include "BulletObject.h"


BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
}


BulletObject::~BulletObject()
{

}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
    bool ret = false;
    ret = LoadImg("img//spider_bullet", des);
    return ret;
}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
    if (bullet_dir_ == DIR_RIGHT)
    {
        rect.x += x_val_;
        if (rect.x > x_border)
        {
            is_move_ = false;
        }
    }
    else if (bullet_dir_ == DIR_LEFT)
    {
        rect.x -= x_val_;
        if (rect.x < 0)
        {
            is_move_ = false;
        }
    }
}
