#ifndef BOSS_THREAT
#define BOSS_THREAT

#include "BObject.h"
#include "Game_Stat.h"
#include "Main_o.h"
#include "Text.h"
#include "Map.h"
#include "Timer.h"

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

    int Skill_1 ();
    int Skill_2 ();
    int Skill_3 ();

    void SetXpos (const float& a) {x_pos = a;}
    void SetYpos (const float& b) {y_pos = b;}
    float GetXpos () {return x_pos;}
    float GetYpos () {return y_pos;}

    void SetMapXY(const int x, const int y) {mapvalue_x = x; mapvalue_y = y;}

    void SetType (const int& Type) {type = Type;}
    int GetType () {return type;}

    int HP;
    int maxHP;
    int ATK;
    int SPEED;
    double EF_RES;

    bool battle;
    int XP_drop;
    int count_turn;

    bool attack;
    bool dead;

    void ShowHP(TTF_Font* font, SDL_Renderer* screen);
    void MinusHP (const int& x) {HP-=x;}
    int BossCombat (MainObject& Player, TTF_Font* font_combat, SDL_Renderer* screen, TTF_Font* font_noti, TTF_Font* font_title);
private:

    float x_pos;
    float y_pos;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[12];
    int frame_num;
    int frame_delay = 0;

    int mapvalue_x;
    int mapvalue_y;

    int type;
};

#endif // BOSS_THREAT
