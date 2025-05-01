#ifndef BOSS_THREAT
#define BOSS_THREAT

#include "BObject.h"
#include "Game_Stat.h"
#include "Main_o.h"

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

    void SetATK (const int& x) {ATK=x;}
    void SetHP (const int& x) {HP=x;}
    void SetSPEED (const int& x) {SPEED=x;}

    void MinusHP (const int& x) {HP-=x;}
    bool BossCombat (MainObject Player);
private:
    int HP;
    int ATK;
    int SPEED;

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
