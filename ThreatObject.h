#ifndef T_OBJECT
#define T_OBJECT

#include "BObject.h"
#include "Game_Stat.h"

#define THREAT_SPEED 4
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
    void SetXpos (const float& a) {x_pos = a;}
    void SetYpos (const float& b) {y_pos = b;}
    float GetXpos () {return x_pos;}
    float GetYpos () {return y_pos;}

    void DoThreat(Map& map_data);
    void CheckMap(Map& map_data);
    void SetMapXY(const int x, const int y) {mapvalue_x = x; mapvalue_y = y;}

    void SetType (const int& Type) {type = Type;}
    void SetBorderX (const int& aBord, const int& bBord) {animation_left = aBord; animation_right = bBord;}
    void SetInputL (const int& IpLeft) {Input_type.left = IpLeft;}
    void Move (SDL_Renderer* screen);
private:

    int revive_time;

    float x_val;
    float y_val;

    float x_pos;
    float y_pos;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[6];
    int frame_num;

    int mapvalue_x;
    int mapvalue_y;

    int type;
    int animation_right;
    int animation_left;
    Input_action Input_type;
};

#endif // T_OBJECT
