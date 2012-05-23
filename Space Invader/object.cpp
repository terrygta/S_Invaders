#include "object.h"
#include <cmath>

Object::Object(string image,
							int x, int y,
							int width, int height, int life_value)
							:
							image(image),
							init_pos(Position(x,y)),
							object_scale(Scale(width,height)), life(life_value)
							
{
}

Object::Object(string image,
							Position init_pos,
							Scale object_scale, int life_value)
							:
							image(image),
							init_pos(init_pos),
							object_scale(object_scale), life(life_value)
{
}

void Object::set_image(string image)
{
	this->image = image;
}

void Object::set_position(Position pos)
{
	this->init_pos = init_pos;
}

void Object::set_position(int x, int y)
{
	 init_pos.set_position(x,y);
}

void Object::set_x(int x)
{
	 init_pos.set_x(x);
}

void Object::set_y(int y)
{
	 init_pos.set_y(y);
}

void Object::set_scale(Scale object_scale)
{
	this->object_scale = object_scale;
}

void Object::set_scale(int width, int height)
{
	object_scale.set_scale(width,height);
}

void Object::set_width(int width)
{
	object_scale.set_width(width);
}

void Object::set_height(int height)
{
	object_scale.set_height(height);
}

void Object::set_life(int life_value)
{
	life = life_value;
}

string Object::get_image()
{
	return image;
}

Position Object::get_position()
{
	return  init_pos;
}

Scale Object::get_scale()
{
	return object_scale;
}

int Object::get_x()
{
	return  init_pos.get_x();
}

int Object::get_y()
{
	return  init_pos.get_y();
}

int Object::get_width()
{
	return object_scale.get_width();
}

int Object::get_height()
{
	return object_scale.get_height();
}

int Object::get_life()
{
	return life;
}

int Object::display()
{
	int err = wogl_render_image(image.c_str(), init_pos.get_x(), init_pos.get_y(), 
		object_scale.get_width(), object_scale.get_height());
	return err;
}

void Object::damage(int value)
{
	life = life - value;
	if(life < 0)
		life = 0;
}

bool Object::isDead()
{
	if(life == 0)
		return true;
	return false;
}

bool Object::hit_object(Object& o)
{
	if((abs(this->get_position().get_x() - o.get_position().get_x()) <= this->get_width() + o.get_width())
		&&(abs(this->get_position().get_y() - o.get_position().get_y()) <= this->get_height() + o.get_height()))
		return true;
	return false;
}