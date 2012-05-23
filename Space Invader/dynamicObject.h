#ifndef DYNAMICOBJECT_H
#define DYNAMICOBJECT_H

#include "object.h"
#include "moveDistance.h"
#include "moveRange.h"

class DynamicObject:public Object
{
protected:
	MoveDistance move_distance; // the move distance of moving left, right, up, down
	MoveRange move_range;// the move range of the object: top, bottom, left, right
public:
	DynamicObject(){};
	DynamicObject(string image,
                            Position init_pos,
                            Scale object_scale,
                            MoveDistance move_distance,
                            MoveRange move_range, int life_value);
	DynamicObject(string image,
                            int x, int y,
                            int width, int height,
                            int distance_up, int distance_down, int distance_left, int distance_right,
                            int range_top, int range_bottom, int range_left, int range_right, int life_value);
	void set_move_distance(MoveDistance move_distance);
    void set_move_distance(int distance_up, int distance_down, int distance_left, int distance_right);
	void set_move_range(MoveRange move_range);
    void set_move_range(int range_top, int range_bottom, int range_left, int range_right);
	MoveDistance get_move_distance();
	MoveRange get_move_range();
	//move
	bool move_up();
	bool move_down();
	bool move_left();
	bool move_right();
	~DynamicObject(){};
};

#endif