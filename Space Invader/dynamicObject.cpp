#include "dynamicObject.h"

DynamicObject::DynamicObject(string image, Position init_pos, Scale object_scale, MoveDistance move_distance, MoveRange move_range, int life_value):
                                                 Object(image, init_pos, object_scale, life_value), move_distance(move_distance), move_range(move_range)
{
}

DynamicObject::DynamicObject(string image, int x, int y, int width, int height, int distance_up, int distance_down, int distance_left, int distance_right, int range_top, int range_bottom, int range_left, int range_right, int life_value):
                                                 Object(image, x, y, width, height, life_value), move_distance ( distance_up, distance_down, distance_left, distance_right), move_range (range_top, range_bottom, range_left, range_right)
{
}

void DynamicObject::set_move_distance(MoveDistance move_distance)
{
	this->move_distance = move_distance;
}

void DynamicObject::set_move_distance(int distance_up, int distance_down, int distance_left, int distance_right)
{
    move_distance.set_moveDistance(distance_up, distance_down, distance_left, distance_right);
}

MoveDistance DynamicObject::get_move_distance()
{
	return move_distance;
}

void DynamicObject::set_move_range(MoveRange move_range)
{
	this->move_range = move_range;
}

void DynamicObject::set_move_range(int range_top, int range_bottom, int range_left, int range_right)
{
    move_range.set_move_range(range_top, range_bottom, range_left, range_right);
}

MoveRange DynamicObject::get_move_range()
{
	return move_range;
}

bool DynamicObject::move_up()
{
    if(get_y() + get_height() >= move_range.get_top())
        return false;
    set_y(get_y()+move_distance.get_up());
    return true;
}

bool DynamicObject::move_down()
{
    if(get_y() - get_height() <= move_range.get_bottom())
        return false;
    set_y(get_y()-move_distance.get_down());
    return true;
}

bool DynamicObject::move_left()
{
    if(get_x() - get_width() <= move_range.get_left())
        return false;
    set_x(get_x()-move_distance.get_left());
    return true;
}

bool DynamicObject::move_right()
{
    if(get_x() + get_width() >= move_range.get_right())
        return false;
    set_x(get_x()+move_distance.get_right());
    return true;
}