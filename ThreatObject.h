#ifndef T_OBJECT
#define T_OBJECT

#include "BObject.h"
#include "Game_Stat.h"
#include "BulletObject.h"

#define THREAT_SPEED 4

#define SLIME_IDLE_NUM 20
#define SLIME_MOVE_NUM 20
#define SPIDER_MOVE_NUM 5
#define SPIDER_SHOOT_LEFT_NUM 5
#define SPIDER_SHOOT_RIGHT_NUM 5
#define MUSH_MOVE_UD_NUM 5
#define MUSH_MOVE_LR_NUM 5
#define RMUSH_MOVE_UD_NUM 5
#define RMUSH_MOVE_LR_NUM 5

class ThreatObject : public BaseObject
{
public:
    ThreatObject();
    ~ThreatObject();

    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void Clip();
    int GetWidthFrame () {return width_frame;}
    int GetHeightFrame () {return height_frame;}

    void SetXvalue (const float& a) {x_val = a;}
    void SetYvalue (const float& b) {y_val = b;}
    void SetRevTime (const int& x) {revive_time = x;}
    void SetXpos (const float& a) {x_pos = a;}
    void SetYpos (const float& b) {y_pos = b;}
    void SetXYposRes () {x_pos__respawn = x_pos; y_pos_respawn=y_pos;}
    float GetXpos () {return x_pos;}
    float GetYpos () {return y_pos;}
    int GetRevTime () {return revive_time;}

    void DoThreat(Map& map_data);
    void CheckMap(Map& map_data);
    void SetMapXY(const int x, const int y) {mapvalue_x = x; mapvalue_y = y;}

    void SetType (const int& Type) {type = Type;}
    int GetType () {return type;}
    void SetBorderX (const int& aBord, const int& bBord) {animation_left = aBord; animation_right = bBord;}
    void SetBorderY (const int& aBord, const int& bBord) {animation_up = aBord; animation_down = bBord;}
    void SetInputL (const int& IpLeft) {Input_type.left = IpLeft;}
    void SetInputD (const int& IpDown) {Input_type.down = IpDown;}
    void Move (SDL_Renderer* screen);

    int HP;
    int ATK;

    int XP_drop;
    int HP_drop;

    std::vector<BulletObject*> get_bullet_list () const {return bullet_list;}
    void set_bullet_list(const std::vector<BulletObject*>& bl_list) {bullet_list = bl_list;}
    void InitBullet (BulletObject* p_bullet, SDL_Renderer*screen);
    void MakeBullet (SDL_Renderer* screen, const int& x_limit, const int& y_limit);

private:
    std::vector<BulletObject*> bullet_list;
    int revive_time;

    float x_val;
    float y_val;

    float x_pos;
    float y_pos;

    float x_pos__respawn;
    float y_pos_respawn;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[12];
    int frame_num;

    int mapvalue_x;
    int mapvalue_y;

    int type;
    int animation_up;
    int animation_down;

    int animation_right;
    int animation_left;
    Input_action Input_type;
};

#endif // T_OBJECT
