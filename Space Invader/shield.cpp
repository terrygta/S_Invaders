#include "shield.h"

Shield::Shield(string image,
							Position init_pos,
							Scale shield_scale, int life_value)
							:
							Object(image, init_pos, shield_scale, life_value)
{
	path = image.substr(0, image.size() - 4);
};

Shield::Shield(string image,
							int x, int y,
							int width, int height, int life_value)
							:
							Object(image, x, y, width, height, life_value)
{
	path = image.substr(0, image.size() - 4);
};

void Shield::damage(int value)
{
	Object::damage(value);
	if(!isDead())
	{
		char suffix[2];
		itoa(get_life(), suffix, 10);
		set_image(path + "_" + suffix + ".png");
	}
}