#include "position.h"

Position::Position(int x, int y):x(x), y(y)
{
}

void Position::set_x(int x)
{
	this->x = x;
}

void Position::set_y(int y)
{
	this->y = y;
}

void Position::set_position(int x,int y)
{
	this->x = x;
	this->y = y;
}

int Position::get_x()
{
	return x;
}

int Position::get_y()
{
	return y;
}

bool Position::operator == (Position& p)
{
	if(this->get_x() == p.get_x() && this->get_y() == p.get_y())
		return true;
	return false;
}