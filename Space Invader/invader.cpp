#include "invader.h"

Invader::Invader(InvaderType invaderType, Position init_pos, Scale invader_scale, MoveDistance move_distance, MoveRange move_range):
                           DynamicObject(invaderType.image, init_pos, invader_scale, move_distance, move_range, invaderType.life), score(invaderType.score)
{
}
Invader::Invader(string image, int x, int y, int width, int height, int distance_up, int distance_down, int distance_left, int distance_right, int range_top, int range_bottom, int range_left, int range_right, int life_value, int score_value):
                           DynamicObject(image, x, y, width, height, life_value, distance_up, distance_down, distance_left, distance_right, range_top, range_bottom, range_left, range_right), score(score_value)
{
}

Bullet Invader::fire()
{
    Position pos = get_position();
    pos.set_y(get_y() - get_height());
	return Bullet("image/invader_bullet.png", pos, Scale(2,6), MoveDistance(0,6,0,0), MoveRange(700,0,0,0), 1);
}

int Invader::get_score()
{
    return score;
}