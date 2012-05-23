#ifndef _moveDistance_h
#define _moveDistance_h

class MoveDistance
{
private:
	int up;
	int down;
	int left;
	int right;
public:
	MoveDistance(){};
	MoveDistance(int up, int down, int left, int right);
	void set_up(int up);
	void set_down(int down);
	void set_left(int left);
	void set_right(int right);
	void set_moveDistance(int up, int down, int left, int right);
	int get_up();
	int get_down();
	int get_left();
	int get_right();
	~MoveDistance(){}
};

#endif