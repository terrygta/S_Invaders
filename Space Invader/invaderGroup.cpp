#include "invaderGroup.h"
//#include <iostream>
#include <ctime>
#include <cstdlib>

InvaderGroup* InvaderGroup::instance = 0;

InvaderGroup::InvaderGroup(Position init_pos, Scale invader_scale, int margin, MoveDistance move_distance, MoveRange move_range, 
	int number_per_row, int number_per_column, int mine_number_val):
                                             init_pos(init_pos), invader_scale(invader_scale), margin(margin), move_distance(move_distance), 
												 move_range(move_range), number_per_row(number_per_row), number_per_column(number_per_column), 
												 current_move("RIGHT"), next_move("RIGHT"), total_invaders(number_per_row*number_per_column),
												 mine_number(mine_number_val)
{
	init_invaders();
	init_mines();
}

InvaderGroup* InvaderGroup::getInstance(Position init_pos, Scale invader_scale, int margin, MoveDistance move_distance, MoveRange move_range, 
	int number_per_row, int number_per_column, int mine_number_val)
{
	if(instance == 0)
		instance = new InvaderGroup(init_pos,invader_scale, margin, move_distance, move_range, number_per_row, number_per_column, mine_number_val);
	return instance;
}

int InvaderGroup::get_number_per_row()
{
	return number_per_row;
}

int InvaderGroup::get_number_per_column()
{
	return number_per_column;
}

int InvaderGroup::get_total_invaders()
{
	return total_invaders;
}

Invader& InvaderGroup::get_invader(int row_no, int column_no)
{
	return invader_list[row_no][column_no];
}
//Assignment 4
Invader& InvaderGroup::get_mothership()
{
	return mothership;
}

Invader& InvaderGroup::get_front_invader()
{
	int row = 0, column = 0;
	for(int i = 0; i < number_per_column; i++)
	{
		bool stop = false;
		for(int j = 0; j < number_per_row; j++)
		{
			if(!invader_list[i][j].isDead())
			{
				row = i;
				column = j;
				stop = true;
				break;
			}
		}
		if(stop)
			break;
	}
	return invader_list[row][column];
}

void InvaderGroup::move_up()
{
	for(int i = 0; i < number_per_column; i++)
	{
		for(int j = 0; j < number_per_row; j++)
		{
			invader_list[i][j].move_up();
		}
	}
	for(int i = 0; i < mine_number; i++)
		mine_list[i].move_up();
}

void InvaderGroup::move_down()
{
	for(int i = 0; i < number_per_column; i++)
	{
		for(int j = 0; j < number_per_row; j++)
		{
			invader_list[i][j].move_down();
		}
	}
	for(int i = 0; i < mine_number; i++)
		mine_list[i].move_down();
}

void InvaderGroup::move_left()
{
	for(int i = 0; i < number_per_column; i++)
	{
		for(int j = 0; j < number_per_row; j++)
		{
			invader_list[i][j].move_left();
		}
	}
	for(int i = 0; i < mine_number; i++)
		mine_list[i].move_left();
}

void InvaderGroup::move_right()
{
	for(int i = 0; i < number_per_column; i++)
	{
		for(int j = 0; j < number_per_row; j++)
		{
			invader_list[i][j].move_right();
		}
	}
	for(int i = 0; i < mine_number; i++)
		mine_list[i].move_right();
}

bool InvaderGroup::move()
{
	if (next_move == "RIGHT" && invader_list[0][number_per_row-1].get_x()+move_distance.get_right()+invader_scale.get_width() > move_range.get_right())
	{
		current_move = "DOWN";
		next_move = "LEFT";
	}
	else if (next_move == "LEFT" && invader_list[0][0].get_x()-move_distance.get_left()-invader_scale.get_width() < move_range.get_left())
	{
		current_move = "DOWN";
		next_move = "RIGHT";
	}
	else
	{
		current_move = next_move;
	}
	if (current_move == "RIGHT")
	{
		this->move_right();
	}
	else if (current_move == "LEFT")
	{
		this->move_left();
	}
	else
	{
		this->move_down();
        // when invader reachs the shield blocks, stop moving, game over
		if (get_front_invader().get_y()-invader_scale.get_height() <= move_range.get_bottom())
			return false;
	}
	//Assignment 4
	// mothership movement/revival.
	if(mothership.isDead() && rand() % 200 <9)
	{
		mothership.set_life(1);
		mothership.set_x(770);
	}
	//else if (mothership.isDead())
		//std::cout << "mothership is dead"  <<std::endl ;
	if(!mothership.isDead())
	{	
		//std::cout << "mothership is alive at x: " << mothership.get_x() << ", y: " << mothership.get_y() <<std::endl ;
		
		//if(mothership.get_x()<100 || mothership.get_x()>670)
		//	mothership.move_left();
		//if(mothership.get_x()<250 || mothership.get_x()>520)
		//	mothership.move_left();
		//if(mothership.get_x()==400 && rand() % 200 < 7)
		//	mothership.move_left();
		//if(mothership.get_x()!=400)
		//	mothership.move_left();
		//if(mothership.get_x()<=0)
		//	mothership.set_life(0);
		if(!mothership.move_left())
			mothership.set_life(0);
	}	
	return true;
}

string InvaderGroup::get_current_move()
{
    return current_move;
}

void InvaderGroup::increase_death_number(int num)
{
	death_number = death_number + num;
}

bool InvaderGroup::is_clear()
{
	if(death_number == number_per_row * number_per_column)
		return true;
	return false;
}

Bullet InvaderGroup::fire()
{
	int column = rand() % number_per_row;          //randomly choose an invader to shoot
	int row = 0;
	bool found = false;
	for(int i = 0; i < number_per_column; i++)
	{
		if(!invader_list[i][column].isDead())
		{
			found = true;
			row = i;
			break;
		}
	}
	if(!found)
	{
		for(int i = 0; i < number_per_column; i++)
	    {
		    for(int j = 0; j < number_per_row; j++)
		    {
				if(!invader_list[i][j].isDead())
		        {
			        found = true;
			        row = i;
					column = j;
			        break;
				}
		    }
			if(found)
				break;
		}
	}   
    return invader_list[row][column].fire();
}

int InvaderGroup::explode(int no)
{
	int score = 0;
	Mine mine = mine_list[no];
	int row = mine.getRow();
	int column = mine.getColumn();
	for(int i = row - 1; i <= row + 1; i++)
	{
		for(int j = column - 1; j <= column + 1; j++)
		{
			if( i < 0 || i >= number_per_column)
				break;
			if( j >=0 && j < number_per_row)
			{
				if(!invader_list[i][j].isDead())
				{
					score = score + invader_list[i][j].get_score();
					invader_list[i][j].set_life(0);
					death_number++;
				}
			}
		}
	}
	mine_list[no].set_life(0);
	return score;
}

InvaderGroup::~InvaderGroup()
{
	for(int i = 0; i < number_per_column; i++)
		delete [] invader_list[i];
	delete [] invader_list;
	delete instance;
	instance = 0;
}

void InvaderGroup::init_invaders()
{
	invader_list = new Invader* [number_per_column];
	for(int i = 0; i < number_per_column; i++)
		invader_list[i] = new Invader[number_per_row];
    
    InvaderType *invaderType;
	for(int i = 0; i < number_per_column; i++)
	{
        if(i == 0 || i == 1)
            invaderType = new  InvaderType("image/invader.png",1,1);
        if(i == 2)
            invaderType = new InvaderType("image/invader_2.png",1,2);
        if(i == 3)
            invaderType = new InvaderType("image/invader_3.png",1,3);
        if(i == 4)
            invaderType = new InvaderType("image/invader_4.png",1,4);
		for(int j = 0; j < number_per_row; j++)
		{
		    invader_list[i][j] = Invader(*invaderType, Position(init_pos.get_x()+j*(invader_scale.get_width()*2+margin), init_pos.get_y()+i*(invader_scale.get_height()*2+margin)), invader_scale, move_distance, move_range);
		}
	}
	death_number = 0;
	//Assignment 4
	invaderType = new InvaderType("image/invader.png",0,50);
	MoveDistance mother_distance = invader_list[0][0].get_move_distance();
	mother_distance.set_left( 3 * mother_distance.get_left());
	mothership = Invader(*invaderType,Position(770,670),invader_scale/*Scale(invader_scale.get_width()*2,invader_scale.get_height())*/,mother_distance,move_range/*MoveRange(791,789,10,790)*/);
	srand(time(NULL));
}

void InvaderGroup::init_mines()
{
	mine_list = new Mine[mine_number];
	death_number = mine_number;
	for(int i = 0; i < mine_number; i++)
	{
		if(i < 0)
			break;
		int row = rand() % number_per_column;
		int column = rand() % number_per_row;
		if(!invader_list[row][column].isDead())
		{
			invader_list[row][column].set_life(0);
			mine_list[i] = Mine("image/mine.jpg", invader_list[row][column].get_position(), Scale(20,20), invader_list[row][column].get_move_distance(),
				invader_list[row][column].get_move_range(),1, row, column);
		}
		else
			i--;
	}
}

void InvaderGroup::increase_move_distance()
{
    int left = move_distance.get_left() + 1;
    int right = move_distance.get_right() + 1;
    int up = move_distance.get_up();
    int down = move_distance.get_down();
    move_distance.set_moveDistance(up,down,left,right);
    for(int i = 0; i < number_per_column; i++)
	{
		for(int j = 0; j < number_per_row; j++)
		{
            invader_list[i][j].set_move_distance(move_distance);
        }
    }
	for(int i = 0; i < mine_number; i++)
		mine_list[i].set_move_distance(move_distance);
}