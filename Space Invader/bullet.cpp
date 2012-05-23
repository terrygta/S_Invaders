#include "bullet.h"

Bullet::Bullet(string image, Position pos, Scale scale, MoveDistance move_distance, MoveRange move_range, int life_value):
                     DynamicObject(image, pos, scale, move_distance, move_range, life_value)
{
}
Bullet::Bullet(string image, int x, int y, int width, int height, int distance_up, int distance_down, int distance_left, int distance_right, int range_top, int range_bottom, int range_left, int range_right, int life_value):
                     DynamicObject(image, x, y, width, height, distance_up, distance_down, distance_left, distance_right, range_top, range_bottom, range_left, range_right, life_value)
{
}

void Bullet::set_id(int id_value)
{
    id = id_value;
}

int Bullet::get_id()
{
    return id;
}