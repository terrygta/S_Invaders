#include "game.h"
#include <sstream>
#include <ctime>

Game::Game(){
	//initialise the invaders
	invader_group = InvaderGroup::getInstance(Position(50,450), Scale(20,15),
								15, MoveDistance(0,5,5,5), MoveRange(700,230,10,790), 11, 5, 2); //invader group
	//initialise the tank
    theTank = Tank("image/tank.png", Position(400,60), Scale(25,15), MoveDistance(0,0,10,10), 
								MoveRange(0,0,10,790),3); //tank

    for(int i = 0; i < 4; i++)
	{
		//initialise the shields
		theShield[i] = Shield("image/shield.png", Position(100+i*200,200), Scale(50,30), 10);
	}
    invader_last_time = -1;
    invader_current_time = -1;
    invader_step_time = 300; //300 ms
    bullet_last_time = -1;
    bullet_current_time = -1;
    bullet_step_time = 30; //30 ms
	//Assignment 4
	tank_last_time = -1;
	tank_last_milli = -1;
	tank_current_time = -1;
	tank_current_milli = -1;
	tank_step_time = 500; // 500 ms
    conti = true;
	srand(time(NULL));
	lose = false;
	theTank.readHighScore();
}

int Game::get_invader_time_period()
{
    SYSTEMTIME sys; 
    GetLocalTime( &sys ); 
    if(invader_last_time == -1)
    {
    	invader_last_time = sys.wMilliseconds;
		
		return 0;
    }
    else
    {
    	invader_current_time = sys.wMilliseconds;
    }
    return invader_current_time - invader_last_time;
}
//Assignment 4
bool Game::tank_can_shoot()
{
	if(tank_step_time == 0)
		return true;
	SYSTEMTIME sys; 
    GetLocalTime( &sys ); 
	if(tank_last_time == -1)
    {
    	tank_last_time = sys.wSecond;
		tank_last_milli = sys.wMilliseconds;
        return true;
    }
    else
    {
		tank_current_time = sys.wSecond;
    	tank_current_milli = sys.wMilliseconds;
    } 
	if((tank_last_time == tank_current_time-1 && tank_last_milli > 1000 - tank_step_time && tank_current_milli + 1000 - tank_last_milli < tank_step_time )|| (tank_last_time==tank_current_time && tank_current_milli -tank_last_milli < tank_step_time))
		return false;
	tank_last_time = tank_current_time;
	tank_last_milli = tank_current_milli;
    return true;
}
int Game::get_bullet_time_period()
{
    SYSTEMTIME sys; 
    GetLocalTime( &sys ); 
    if(bullet_last_time == -1)
    {
    	bullet_last_time = sys.wMilliseconds;
        return 0;
    }
    else
    {
    	bullet_current_time = sys.wMilliseconds;
    }
    return bullet_current_time - bullet_last_time;
}

/* exit the program with a message */
void Game::exit_with_msg(int error)
{
	if (error) 
	{
		// something wrong
		std::cerr << "Error: program ended with error code: " << error << std::endl;
		exit(error);
	} 
	else 
	{
		// no error
		std::cout << "Program ended normal" << std::endl;
		exit(0);
	}
}

void Game::render_invaders()
{
	for(int i = 0; i < invader_group->get_number_per_column(); i++)
	{
		for(int j = 0; j < invader_group->get_number_per_row(); j++)
		{
			if(!invader_group->get_invader(i,j).isDead())
			{
		        int err = invader_group->get_invader(i,j).display();
		        if (err != WOGL_SUCCESS)
		        {
			        exit_with_msg(__LINE__);
		        }
			}
		}
	}
}
//Assignment 4
void Game::render_mothership()
{
	if(!invader_group->get_mothership().isDead())
	{
		int err = invader_group->get_mothership().display();
		if (err != WOGL_SUCCESS)
		{
			        exit_with_msg(__LINE__);
		}
	}	
}


void Game::render_shields()
{
	for(int i = 0; i < 4; i++)
	{
		if(!theShield[i].isDead())
		{
		    int err = theShield[i].display();
		    if (err != WOGL_SUCCESS)
		    {
			    exit_with_msg(__LINE__);
		    }
		}
	}
}

void Game::render_tank()
{
    int err = theTank.display();
    if (err != WOGL_SUCCESS)
    {
        exit_with_msg(__LINE__);
    }
}

void Game::render_bullets()
{
	for(unsigned int i = 0; i < invaders_bullets.size(); i++)
	{
		invaders_bullets[i].display();
	}
	for(unsigned int i = 0; i < tank_bullets.size(); i++)
	{
        tank_bullets[i].display();
	}
}

void Game::render_mines()
{
	for(int i = 0; i < invader_group->get_mine_number(); i++)
		if(!invader_group->get_mine(i).isDead())
			invader_group->get_mine(i).display();
}

void Game::move_invader()
{
	// every X ms, the invaders take a move
	if (conti)
	{
        if((get_invader_time_period() < 0 && get_invader_time_period() >= invader_step_time-1000) || get_invader_time_period() >= invader_step_time) // every 300ms, move
        {
        	conti = invader_group->move();
            if(invader_group->get_current_move() == "DOWN")
                invader_group->increase_move_distance();
        	if(rand() % 2)
            {
        	    invaders_bullets.push_back(invader_group->fire());
            }
        	invader_last_time = invader_current_time;
        }
	}
}

void Game::invaders_fire()
{
	invaders_bullets.push_back(invader_group->fire());
}

void Game::control_tank(int key)
{
	//press ESC to exit the game
    if (key == WOGL_KEY_ESCAPE)
    {
        // exit nicely
        exit_with_msg(0);
    }
	
	//if (key == WOGL_KEY_UP)
 //   {
 //   }

	//if (key == WOGL_KEY_DOWN)
 //   {
 //   }

	// press left and right keys to control the tank
	if (key == WOGL_KEY_LEFT)
    {
		theTank.move_left();
    }

	if (key == WOGL_KEY_RIGHT)
    {
		theTank.move_right();
    }

	if(key == WOGL_KEY_SPACE)
	{
		if(!theTank.isDead())
        {
			//Assignment 4
			if(tank_can_shoot())
				tank_bullets.push_back(theTank.fire());
        }
	}
}

void Game::move_tank_bullets()
{
	for(unsigned int i = 0; i < tank_bullets.size(); i++)
	{
		if(!tank_bullets[i].move_up())
        {
            tank_bullets.erase(tank_bullets.begin() + i);
            i = i - 1;
        }
	}
}

void Game::move_invaders_bullets()
{
	for(unsigned int i = 0; i < invaders_bullets.size(); i++)
	{
		if(!invaders_bullets[i].move_down())
        {
            invaders_bullets.erase(invaders_bullets.begin() + i);
            i = i - 1;
        }
	}
}

void Game::move_bullets()
{
	if (conti)
	{
        if((get_bullet_time_period() < 0 && get_bullet_time_period() >= bullet_step_time-1000) || get_bullet_time_period() >= bullet_step_time) // every 30ms, move
        {
            move_tank_bullets();
            move_invaders_bullets();
        	bullet_last_time = bullet_current_time;
        }
	}
}

void Game::hit_bullets()
{
    bool hit = false;
	for(unsigned int i = 0; i < tank_bullets.size(); i++)
	{
		for(unsigned int j = 0; j < invaders_bullets.size(); j++)
	    {
            if(tank_bullets[i].hit_object(invaders_bullets[j]))
            {
                invaders_bullets.erase(invaders_bullets.begin() + j);
                hit = true;
                break;
            }
        }
        if (hit)
        {
            tank_bullets.erase(tank_bullets.begin() + i);
            hit = false;
            i = i - 1;
        }
    }
}

void Game::hit_invaders()
{
	for(unsigned int i = 0; i < tank_bullets.size(); i++)
	{
		bool hit = false;
		for(int column = 0; column < invader_group->get_number_per_row(); column++)
		{
		    for(int row = 0; row < invader_group->get_number_per_column(); row++)
	        {
				if((!invader_group->get_invader(row,column).isDead()) && 
					tank_bullets[i].hit_object(invader_group->get_invader(row,column)))
				{
					invader_group->get_invader(row,column).damage(1);
					if(invader_group->get_invader(row,column).isDead())
                    {
						theTank.increaseScore(column, invader_group->get_invader(row,column).get_score());
						//Assignment 4
						if (tank_step_time != 0)
						{
							if(theTank.getCurrentScore()>=250)
								tank_step_time = 0;
							else if (theTank.getCurrentScore()>=100)
								tank_step_time = 250;
						}
						invader_group->increase_death_number(1);
                    }
					tank_bullets.erase(tank_bullets.begin() + i);
					i = i - 1;
					hit = true;
					break;
				}
			}
			if(hit)
				break;
		}
	}
    check_clear();
}

void Game::hit_mines()
{
	for(unsigned int i = 0; i < tank_bullets.size(); i++)
	{
		for(int j = 0; j < invader_group->get_mine_number(); j++)
		{
			if(tank_bullets[i].hit_object(invader_group->get_mine(j)) && (!invader_group->get_mine(j).isDead()))
			{
				theTank.increaseScore(invader_group->explode(j));
				tank_bullets.erase(tank_bullets.begin() + i);
				i = i - 1;
				break;
			}
		}
	}
}
//Assignment 4
void Game::hit_mothership()
{
	for(unsigned int i = 0; i < tank_bullets.size(); i++)
	{
		if(!invader_group->get_mothership().isDead())
		{
			if(tank_bullets[i].hit_object(invader_group->get_mothership()))
			{
				invader_group->get_mothership().damage(1);
				if(invader_group->get_mothership().isDead())
					theTank.increaseScore(invader_group->get_mothership().get_score());
				tank_bullets.erase(tank_bullets.begin() + i);
				i = i - 1;
				break;
			}
		}
	}
}


void Game::hit_tank()
{
	for(unsigned int i = 0; i < invaders_bullets.size(); i++)
	{
		if(invaders_bullets[i].hit_object(theTank))
		{
			theTank.damage(1);
			if(theTank.isDead())
			{
                conti = false;
		        lose = true;
				break;
			}
            else
            {
                invaders_bullets.erase(invaders_bullets.begin() + i);
				i = i - 1;
                theTank.set_position(400,60);
            }
		}
	}
}

void Game::hit_shield()
{
	for(int i = 0; i < 4; i++)
	{
		for(unsigned int j = 0; j < invaders_bullets.size(); j++)
		{
			if(!theShield[i].isDead() && invaders_bullets[j].hit_object(theShield[i]))
			{
				theShield[i].damage(1);
				invaders_bullets.erase(invaders_bullets.begin() + j);
				j = j - 1;
			}
		}

		for(unsigned int k = 0; k < tank_bullets.size(); k++)
		{
			if(!theShield[i].isDead() && tank_bullets[k].hit_object(theShield[i]))
			{
				theShield[i].damage(1);
				tank_bullets.erase(tank_bullets.begin() + k);
				k = k - 1;
			}
		}
	}
}

void Game::hit()
{
    hit_invaders(); // must call hit_invaders() first (for combo)
    hit_bullets();
    hit_tank();
    hit_shield();
	hit_mines();
	//Assignment 4
	hit_mothership();
}

void Game::check_clear()
{
	if(invader_group->is_clear() && conti)
    {
		conti = false;
		theTank.addRestScore();
	}
}

void Game::display()
{
    //render invaders
    render_invaders();
    //render shield blocks
    render_shields();
    //render tank
    render_tank();
    //render bullets
    render_bullets();
	//render mines
	render_mines();
	//render mothership //Assignment 4
	render_mothership();
    // draw score
    int err = wogl_render_text(10, 10, small_font, "Current Score:");
    if (err != WOGL_SUCCESS)
    	exit_with_msg(__LINE__);
    /*err = wogl_render_text(10, 20, small_font, "Total Score:");
    if (err != WOGL_SUCCESS)
    	exit_with_msg(__LINE__);*/
    err = wogl_render_text(10, 20, small_font, "Highest Score:");
    if (err != WOGL_SUCCESS)
    	exit_with_msg(__LINE__);
    stringstream current;
	current<<theTank.getCurrentScore();
    err = wogl_render_text(85, 10, small_font, current.str().c_str());
    if (err != WOGL_SUCCESS)
    	exit_with_msg(__LINE__);
    //stringstream total;
    //total<<total_score;
    //err = wogl_render_text(85, 20, small_font, total.str().c_str());
    //if (err != WOGL_SUCCESS)
    //	exit_with_msg(__LINE__);
    stringstream highest;
	highest<<theTank.getHighScore();
    err = wogl_render_text(85, 20, small_font, highest.str().c_str());
    if (err != WOGL_SUCCESS)
    	exit_with_msg(__LINE__);
    err = wogl_render_text(700, 10, small_font, "Tank Life:");
    if (err != WOGL_SUCCESS)
    	exit_with_msg(__LINE__);
    stringstream tank_life;
    tank_life<<theTank.get_life();
    err = wogl_render_text(750, 10, small_font, tank_life.str().c_str());
    if (err != WOGL_SUCCESS)
    	exit_with_msg(__LINE__);
}

void Game::run()
{
    move_invader();
    move_bullets();
    hit();
}

void Game::game_over()
{
	if (lose)
	{
		// draw "Game Over"
		int err = wogl_render_text(350, 650, medium_font, "Game Over!");
		if (err != WOGL_SUCCESS)
			exit_with_msg(__LINE__);
	}
    else
    {
        //draw "You Win"
		int err = wogl_render_text(300, 650, medium_font, "You Win!");
		if (err != WOGL_SUCCESS)
	        exit_with_msg(__LINE__);
    }
}