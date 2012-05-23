#include "moveRange.h"

MoveRange::MoveRange(int top, int bottom, int left, int right):top(top), bottom(bottom), left(left), right(right)
{
}

void MoveRange::set_top(int top)
{
	this->top = top;
}

void MoveRange::set_bottom(int bottom)
{
	this->bottom = bottom;
}

void MoveRange::set_left(int left)
{
	this->left = left;
}

void MoveRange::set_right(int right)
{
	this->right = right;
}

void MoveRange::set_move_range(int top, int bottom, int left, int right)
{
	this->top = top;
	this->bottom = bottom;
	this->left = left;
	this->right = right;
}

int MoveRange::get_top()
{
	return top;
}

int MoveRange::get_bottom()
{
	return bottom;
}

int MoveRange::get_left()
{
	return left;
}

int MoveRange::get_right()
{
	return right;
}