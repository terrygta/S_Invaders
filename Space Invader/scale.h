#ifndef _scale_h
#define _scale_h

class Scale
{
private:
	int width;
	int height;
public:
	Scale(){};
	Scale(int width, int height);
	void set_width(int width);
	void set_height(int height);
	void set_scale(int width, int height);
	int get_width();
	int get_height();
	~Scale(){};
};

#endif