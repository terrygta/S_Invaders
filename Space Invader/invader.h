#ifndef _invade_h
#define _invader_h

#include "dynamicObject.h"
#include "bullet.h"
#include "invaderType.h"

//invader class
class Invader:public DynamicObject {
private:
    int score;
public:
	//construction functions
	Invader(){};
	Invader(InvaderType invaderType,
                 Position init_pos,
                 Scale invader_scale,
                 MoveDistance move_distance,
                 MoveRange move_range);
	Invader(string image,
                 int x, int y,
                 int width, int height,
                 int distance_up, int distance_down, int distance_left, int distance_right,
                 int range_top, int range_bottom, int range_left, int range_right, int life_value, int score_value);
    Bullet fire();
    int get_score();
	~Invader(){};
};

#endif