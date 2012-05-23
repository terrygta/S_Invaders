#include "tank.h"

Tank::Tank(string image, Position init_pos, Scale tank_scale, MoveDistance move_distance, MoveRange move_range, int life_value):
                     DynamicObject(image, init_pos, tank_scale, move_distance, move_range, life_value)
{
	last_column = -1;
	combo = 1;
	combo_score = 0;
	current_score = 0;
}
Tank::Tank(string image, int x, int y, int width, int height, int distance_up, int distance_down, int distance_left, int distance_right, int range_top, int range_bottom, int range_left, int range_right, int life_value):
                     DynamicObject(image, x, y, width, height,  distance_up, distance_down, distance_left, distance_right,  range_top, range_bottom, range_left, range_right, life_value)
{
	last_column = -1;
	combo = 1;
	combo_score = 0;
	current_score = 0;
}

Bullet Tank::fire()
{
    Position pos = get_position();
    pos.set_y(get_y() + get_height());
	return Bullet("image/tank_bullet.png", pos, Scale(2,6), MoveDistance(6,0,0,0), MoveRange(700,0,0,0), 1);
}

void Tank::readHighScore()
{
	ifstream fin;
	fin.open("score/score.dat");
	if(fin.fail())
	{
		high_score = 0;
		return;
	}
	string head;
	getline(fin, head);
	if(head != "space invader")
	{
		high_score = 0;
		return;
	}
	fin.clear();
	fin >> high_score;
	if(high_score < 0)
		high_score = 0;
}

int Tank::getHighScore()
{
	if(current_score > high_score)
		return current_score;
	else
		return high_score;
}

void Tank::setHighScore()
{
	ofstream fout;
	fout.open("score/score.dat");
	fout<<"space invader"<<endl;
	if(current_score > high_score)
		high_score = current_score;
	fout<<high_score;
}

void Tank::increaseScore(int column, int s)
{
	if(column == last_column)
	{
		combo = combo + 1;
		combo_score = combo_score + s;
	}
	else
	{
		current_score = current_score + combo_score * combo;
		combo = 1;
		combo_score = s;
	}
	last_column = column;
}

void Tank::damage(int value)
{
	Object::damage(value);
	if(get_life() == 0)
	{
		addRestScore();
	}

}

void Tank::addRestScore()
{
	current_score = current_score + combo_score * combo;
	combo = 0;
	setHighScore();
}