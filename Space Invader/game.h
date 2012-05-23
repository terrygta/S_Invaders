#include <iostream>
#include<vector>

#include "wogl.h"
#include "invaderGroup.h"
#include "tank.h"
#include "shield.h"
#include "bullet.h"
#include "windows.h"

#ifndef WOGL_KEY_SPACE
#define WOGL_KEY_SPACE 32
#endif

class Game
{
private:
	InvaderGroup* invader_group; //invader group
    Tank theTank; //tank
    Shield theShield[4]; //shields
	vector<Bullet> invaders_bullets;  //invaders' bullets
	vector<Bullet> tank_bullets;  //tank's bullets
    int invader_last_time;
    int invader_current_time;
    int invader_step_time;
    int bullet_last_time;
    int bullet_current_time;
    int bullet_step_time;
	int tank_last_time;
	int tank_last_milli;
	int tank_current_time;
	int tank_current_milli;
	int tank_step_time;
    bool conti;
	bool lose;  //determines whether you lose the game
    int get_invader_time_period();
    int get_bullet_time_period();
	bool tank_can_shoot();

public:
	Game();
	void exit_with_msg(int error);
	void render_invaders();  //display invaders
	void render_mothership(); //display mothership
	void render_shields();   //display shields
	void render_tank();      //display the tank
    void render_bullets();  //display bullets
	void render_mines();
	void move_invader();     //move the invader group
	void invaders_fire();    //let invaders shoot
	void control_tank(int key);  //control the tank based on the user's input
	void move_tank_bullets();  //move up tank's bullets
	void move_invaders_bullets();  //move down invader's bullets
    void move_bullets();  //move invader and tank bullets
    void hit(); //check whether the bullet hit any object
    void hit_bullets(); //check whether the bullet is hit by the bullet
	void hit_invaders();  //check whether the invader is hit by the bullet
	void hit_mines();
	void hit_mothership(); // check whether the mothership is hit by the bullet
	void hit_tank();      //check whether the tank is hit by the bullet
	void hit_shield();    //check whether the shield is hit by the bullet
	void check_clear();   //check whether the invader group is clear
	bool is_stopped(){return !conti;}  //check whether the game should be stopped
    void display(); //display all the objects
    void run(); //run the game
    void game_over(); //game over
	~Game(){delete invader_group;}
};