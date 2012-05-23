#ifndef _moveRange_h
#define _moveRange_h

class MoveRange
{
private:
	int top;
	int bottom;
	int left;
	int right;
public:
	MoveRange(){};
	MoveRange(int top, int bottom, int left, int right);
	void set_top(int top);
	void set_bottom(int bottom);
	void set_left(int left);
	void set_right(int right);
	void set_move_range(int top, int bottom, int left, int right);
	int get_top();
	int get_bottom();
	int get_left();
	int get_right();
	~MoveRange(){}
};

#endif