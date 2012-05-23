#ifndef _position_h
#define _position_h

class Position
{
private:
	int x;
	int y;
public:
	Position(){};
	Position(int x, int y);
	void set_x(int x);
	void set_y(int y);
	void set_position(int x, int y);
	int get_x();
	int get_y();
	bool operator == (Position& p);
	~Position(){};
};

#endif