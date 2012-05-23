#ifndef MINE_H
#define MINE_H

#include "dynamicObject.h"

class Mine : public DynamicObject {
private:
	int row;
	int column;
public:
	Mine(){}
	Mine(string image,
            Position init_pos,
            Scale mine_scale,
            MoveDistance move_distance,
            MoveRange move_range, int life_value, int r, int c);
	int getRow() {return row;}
	int getColumn() {return column;}
	~Mine(){}
};

#endif