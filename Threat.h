#ifndef T_OBJECT
#define T_OBJECT

#include "Game_Stat.h"
#include "BObject.h"

class ThreatObject : public BaseObject
{
public:
    ThreatObject();
    ~ThreatObject();

private:
    int width_frame;
    int height_frame;
    SDL_Rect frame_clip[6];
    int fram_num;
};

#endif // T_OBJECT
