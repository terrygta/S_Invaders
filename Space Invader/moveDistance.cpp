#include "moveDistance.h"

MoveDistance::MoveDistance(int up, int down, int left, int right):up(up),down(down),left(left),right(right)
{
}

void MoveDistance::set_up(int up)
{
	this->up = up;
}

void MoveDistance::set_down(int down)
{
	this->down = down;
}

void MoveDistance::set_left(int left)
{
	this->left = left;
}

void MoveDistance::set_right(int right)
{
	this->right = right;
}

void MoveDistance::set_moveDistance(int up, int down, int left, int right)
{
	this->up = up;
	this->down = down;
	this->left = left;
	this->right = right;
}

int MoveDistance::get_up()
{
	return up;
}

int MoveDistance::get_down()
{
	return down;
}

int MoveDistance::get_left()
{
	return left;
}

int MoveDistance::get_right()
{
	return right;
}