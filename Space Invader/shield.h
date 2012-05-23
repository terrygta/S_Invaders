#ifndef _shield_h
#define _shield_h

#include"object.h"

//shield block class
class Shield:public Object {
private:
	string path;
public:
	//construction functions
	Shield(){};
	Shield(string image,
				int x, int y,
				int width, int height, int life_value);
	Shield(string image,
				Position init_pos,
				Scale shield_scale, int life_value);
	void damage(int value);
	~Shield(){}
};

#endif