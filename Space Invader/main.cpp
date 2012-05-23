/* 
 * File:   main.cpp
 * Author: Chong Gao
 *
 * Assignment 3
 */

#include "game.h"

//global variable
Game* myGame;

/* Called when display is updated */
void displayfunc() 
{
    // clear screen
    wogl_clear_frame();
    // display game
    myGame->display();

	if(!myGame->is_stopped())
	{
	    // every 300 ms, the invaders take a move
	    myGame->run();
	}
    else
    {
        myGame->game_over();
    }
}


/* Called when key is pressed */
void mykeypressedfunc(int key) 
{
	if(!myGame->is_stopped())
	{
        myGame->control_tank(key);
    }

    //press ESC to exit the game
    if (key == WOGL_KEY_ESCAPE)
    {
        myGame->exit_with_msg(0);
    }
}

int main(int argc, char** argv) 
{
	int err;
	myGame = new Game();
	// initialise wogl library with the window dimensions
	err = wogl_init(800, 700);
    if (err != WOGL_SUCCESS) {
        std::cout << "Failed to initialise in '" << __FUNCTION__ << "'  " << std::endl;
		myGame->exit_with_msg(__LINE__);
	}

	// setup the functions that will be called 
	//   - when key is pressed 
	wogl_set_keyboard_callback(mykeypressedfunc);
	
	//   - when display is updated
    wogl_set_display_callback(displayfunc);

	// start the main rendering loop
    err = wogl_start_rendering();

	if (err != WOGL_SUCCESS) {
        std::cout << "Failed to start rendering in '" << __FUNCTION__ << "'  " << std::endl;
		myGame->exit_with_msg(__LINE__);
	}	
	return (EXIT_SUCCESS);
}

