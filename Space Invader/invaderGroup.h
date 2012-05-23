#ifndef _invaderGroup_h
#define _invaderGroup_h

#include "invader.h"
#include "bullet.h"
#include "mine.h"

//the group of invaders
class InvaderGroup
{
private:
	static InvaderGroup* instance;
	Invader** invader_list; //the pointer to the array of all the invaders in this group
	Mine* mine_list;
	//Assignment 4
	Invader mothership; // the mothership
	Position init_pos;// the initial position of this group
	Scale invader_scale;// the scale of the invaders
	int margin; //margin between every two invaders
	MoveDistance move_distance; // the move distance: left, right, up, down
	MoveRange move_range;// the move range of the group: top, bottom, left, right
	int number_per_row;//invaders number per each row
	int number_per_column;//invaders number per each column
	int total_invaders;//the number of all the invaders in this group
    string current_move; //the current move direction
	string next_move;//the next move direction
	int death_number; //the death number of the invaders
	int mine_number;
	void init_invaders(); //initialize the invader group
	void init_mines();
protected:
	InvaderGroup(Position init_pos, 
                          Scale invader_scale,
                          int margin,
                          MoveDistance move_distance,
                          MoveRange move_range,
                          int number_per_row,
                          int number_per_column,int mine_number_val);
public:
	//construction functions
	static InvaderGroup* getInstance(Position init_pos, 
                          Scale invader_scale,
                          int margin,
                          MoveDistance move_distance,
                          MoveRange move_range,
                          int number_per_row,
                          int number_per_column,int mine_number_val);
	//get
	int get_number_per_row();
	int get_number_per_column();
	int get_mine_number() {return mine_number;}
	int get_total_invaders();
	//Assignment 4
	Invader& get_mothership();
	Invader& get_invader(int row_no, int column_no);
	Invader& get_front_invader();
	Mine& get_mine(int no) {return mine_list[no];}
	void move_up();
	void move_down();
    void move_right();
	void move_left();
	bool move();
    string get_current_move();
    void increase_move_distance();
	void increase_death_number(int num);  //increase the death number of the invaders
	bool is_clear();                      //check whether the invaders are all dead
	Bullet fire();                        //shoot
	int explode(int no);
	~InvaderGroup();
};

#endif