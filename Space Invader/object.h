#ifndef _object_h
#define _object_h

#include "position.h"
#include "scale.h"
#include "wogl.h"
#include <string>

using namespace std;

//superclass of a object
class Object {
private:
	string image; //the image file path of this object
	Position init_pos; //the initial position of this object
	Scale object_scale; //the scale of this object
	int life;  //the life value of the object.
public:
	//construction functions
	Object(){};
	Object(string image, int x, int y, int width, int height, int life_value);
	Object(string image, Position init_pos, Scale object_scale, int life_value);
	//set
	void set_image(string filename);
	void set_position(Position pos);
	void set_position(int x, int y);
	void set_x(int x);
	void set_y(int y);
	void set_scale(Scale object_scale);
	void set_scale(int width, int height);
	void set_width(int width);
	void set_height(int height);
	void set_life(int life_value);
	//get
	string get_image();
	Position get_position();
	Scale get_scale();
	int get_x();
	int get_y();
	int get_width();
	int get_height();
	int get_life();

	int display();  //display the object based on its scale and position
	virtual void damage(int value); //if the object is hit and then is damaged by other object, deduce the life value
	bool isDead();  //check whether the object is dead based on its life value
	bool hit_object(Object& o); //judge whether the object is hit by other object
	~Object(){};
};

#endif