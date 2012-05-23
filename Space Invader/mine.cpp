#include "mine.h"

Mine::Mine(string image, Position init_pos, Scale mine_scale, MoveDistance move_distance, MoveRange move_range, int life_value, int r, int c):
                     DynamicObject(image, init_pos, mine_scale, move_distance, move_range, life_value),row(r), column(c)
{
}