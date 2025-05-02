#ifndef BOSS_THREAT
#define BOSS_THREAT

#include "BObject.h"
#include "Game_Stat.h"
#include "Main_o.h"
#include "Text.h"

class BossThreat : public BaseObject
{
public:
    BossThreat();
    ~BossThreat();

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void Clip();
    int GetWidthFrame () {return width_frame;}
    int GetHeightFrame () {return height_frame;}

    void SetXpos (const float& a) {x_pos = a;}
    void SetYpos (const float& b) {y_pos = b;}
    float GetXpos () {return x_pos;}
    float GetYpos () {return y_pos;}

    void SetMapXY(const int x, const int y) {mapvalue_x = x; mapvalue_y = y;}

    void SetType (const int& Type) {type = Type;}
    void SetStatus (const bool& x) {dead = x;}

    int HP;
    int ATK;
    int SPEED;

    void MinusHP (const int& x) {HP-=x;}
    bool BossCombat (MainObject Player, TTF_Font* font_combat, SDL_Renderer* screen);
private:

    float x_pos;
    float y_pos;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[12];
    int frame_num;

    int mapvalue_x;
    int mapvalue_y;

    int type;
    bool dead;
};

#endif // BOSS_THREAT
