#ifndef _bullet_h
#define _bullet_h

#include "dynamicObject.h"

//bullet class
class Bullet:public DynamicObject {
private:
    int id;
public:
	//construction functions
	Bullet(){};
	Bullet(string image,
              Position pos,
              Scale cale,
              MoveDistance move_distance,
              MoveRange move_range, int life_value);
	Bullet(string image,
             int x, int y,
             int width, int height,
             int distance_up, int distance_down, int distance_left, int distance_right,
             int range_top, int range_bottom, int range_left, int range_right, int life_value);
    void set_id(int id_value);
    int get_id();
	~Bullet(){};
};

#endif