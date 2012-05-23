#ifndef _tank_h
#define _tank_h

#include<fstream>

#include "dynamicObject.h"
#include "bullet.h"

//tank class
class Tank:public DynamicObject {
private:
	int current_score;
	int high_score;
	int last_column;
	int combo;
	int combo_score;
public:
	//construction functions
	Tank(){};
	Tank(string image,
            Position init_pos,
            Scale tank_scale,
            MoveDistance move_distance,
            MoveRange move_range, int life_value);
	Tank(string image,
             int x, int y,
             int width, int height,
             int distance_up, int distance_down, int distance_left, int distance_right,
             int range_top, int range_bottom, int range_left, int range_right, int life_value);
	void increaseScore(int column, int s);
	void increaseScore(int s) {current_score = current_score + s;}
	void readHighScore();
	int getHighScore();
	int getCurrentScore() {return current_score;}
	void setHighScore();
	Bullet fire();
	void damage(int value);
	void addRestScore();
	~Tank(){};
};

#endif