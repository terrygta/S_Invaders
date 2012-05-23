/* 
 * File:   wogl.h
 * Author: sakana
 *
 * Created on February 8, 2012, 3:52 PM
 */


/**
 * \mainpage WOGL library
 * 
 * \section about About
 * 
 * Windowed OpenGL (WOGL) is a simplification of a graphics API for developing 
 * programs with some basic visuals. 
 * 
 * \section idea Idea
 * 
 * Many concepts are needed to be understood when programming with 
 * computer graphics. There are mathematics, the understanding of the graphics 
 * state machine and additionally the link between the graphics subsystem to 
 * the operating system. This library is designed to reduce the burden for 
 * introducing visuals into programs by exposing only a simple graphics API 
 * while most of the work is managed internally.
 * 
 * \section design Design
 * 
 * WOGL is intended to hide many of the underlying mechanisms needed to add 
 * simple graphics to a C/C++ program
 * 
 * Two key concepts:
 * - Remove the need to deal with large graphics API and managing resources
 * - Minimise the programmer effort to attach a graphics subsystem and display content
 * 
 * \section callback Callback register functions 
 * 
 * Obtaining keyboard is relatively easy to achieve with Terminal or command line. 
 * Now with a graphical window, obtaining the keyboard input becomes a little tricky.
 * To allow the user of WOGL to obtain keystrokes, they need to create a function 
 * that accepts a parameter of the key hit. When they register this function 
 * with WOGL, any key that is pressed will be passed in as a parameter to the 
 * user supplied function.
 * 
 * The display situation is similar. When things have changed and the graphics 
 * in the window need to be updated, the user must be able to receive that event.
 * The user needs to create a 'display' function that will be called when the 
 * window need to be updated.
 * To make things a little simpler, this display function will be called as 
 * many times as possible to allow the user to include both program logic and 
 * the graphics in the same function.
 *
 * Registering a callback is actually passing a function pointer with a specific signature 
 * (return type, parameters) to the WOGL library. WOGL will keep this function 
 * and until the appropriate event occurs, it will call that function to be 
 * executed with the parameters that are expected.
 * 
 *  
 * \section functions Functions
 * 
 * WOGL provides functions for three major areas:
 * 
 * - \ref Setup of rendering functionality (display)
 * - \ref Obtaining input (keyboard)
 * - \ref Rendering primitives to display (points, lines, triangles, images, text)
 * 
 * \section Library Interface
 * 
 * <h1>
 * <center> The WOGL interface: \ref wogl.h </center>
 * </h1>
 * 
 * \section credits Credits
 * 
 * Programming and design:
 * 
 * \author Masahiro Takatsuka
 * \author John Stavrakakis
 * 
 * \date 2012
 */

/**
  \page guide Documentation Guide
  
  \section how_doc How to Use the Documentation

  The best way to use the WOGL documentation is as a reference tool. The
  main page includes a brief description and discussion of WOGL features
  and design, and the source header file wogl.h provides details on using the 
  library
 
  \section more_help Where to Find More Help

  For more information on WOGL check the ViSLAB website (<a
  href="https://sites.google.com/a/vislab.net/vislab-home/projects/wogl">www.vislab.net</a>).
*/
/**
  \page license License

  <a href="LICENSE">Read the license</a>
  This software uses the FreeImage open source image library. See http://freeimage.sourceforge.net for details. Executable form of FreeImage is provided under FIPL
FreeImage is used under the (GNU GPL or FIPL), version 1.0

*/

/**
 * \file wogl.h
 * \brief This header file contains defines constants and function headers for WOGL.
 * 
 * This header file contains defines constants and function headers for WOGL.
 */

#ifndef WOGL_H
#define	WOGL_H

/**@{*/
/** \def return code value of a WOGL function */
#define WOGL_SUCCESS 0
#define WOGL_FAILURE -1
/**@}*/



#ifndef DOXYGEN_IGNORE
/** 
 * \def WOGLAPI
 * \brief for cross platform compilation support as a library
 */
#ifndef WOGLAPI
#if defined _WIN32 || defined _WIN64
#define WOGLAPI __declspec(dllimport)
#else
#define WOGLAPI
#endif
#endif

extern "C" {
 extern WOGLAPI int WOGL_DEBUG;
};

#endif /* DOXYGEN_IGNORE */


/**
 * \var wogl_font_size
 * \brief Available font sizes.
 * 
 * These are the possible font size values for rendering text.
 * 
 */
enum wogl_font_size {
    small_font  = 10,
    medium_font = 12,
    large_font  = 18
};

/**@{*/
/** Special key values used by WOGL for recognising arrow keys and the escape key */
extern "C" {
 extern WOGLAPI int WOGL_KEY_LEFT;
 extern WOGLAPI int WOGL_KEY_RIGHT;
 extern WOGLAPI int WOGL_KEY_UP;
 extern WOGLAPI int WOGL_KEY_DOWN;
 extern WOGLAPI int WOGL_KEY_ESCAPE;
};
/**@}*/

/** 
 * \brief Create a new rendering window
 * 
 * Constructs a new rendering window with the window dimensions
 * 
 * \param[in] win_width - window width
 * \param[in] win_height - window height
 * \return WOGL_FAILURE if window cannot be initialised
 */
extern
WOGLAPI int wogl_init(
        int win_width, /**< [in] window width. */
        int win_height /**< [in] window height. */ );

/** 
 * \brief Begin the rendering process. The registered display will be continuously called.
 * 
 * Start the internal rendering loop. User function callbacks for display 
 * and keyboard are called when required.
 * 
 * \return WOGL_SUCCESS. Otherwise, WOGL_FAILURE when wogl not initialised or callbacks not defined
 */
extern
WOGLAPI int wogl_start_rendering(void);



/**
 * \brief Clears all the contents from screen 
 * 
 * \return WOGL_SUCCESS. Otherwise, WOGL_FAILURE if WOGL not initialised
 */
extern 
WOGLAPI int wogl_clear_frame(void);


/**
 * \brief Draw a point on the screen at location x,y. 
 * \warning No reporting when point is outside the screen window.
 * 
 * \param[in] x - x coordinate of point
 * \param[in] y - y coordinate of point
 * 
 */
extern
WOGLAPI void wogl_draw_point(int x, int y );

/** draw a line segment based on two end points
 * \param[in] x1 - x coordinate of end point 1
 * \param[in] y1 - y coordinate of end point 1
 * \param[in] x2 - x coordinate of end point 2
 * \param[in] y2 - y coordinate of end point 2
 */
extern
WOGLAPI void wogl_draw_line( int x1, int y1, int x2, int y2);

/** draw a triangle based on two three points
 * \param[in] x1 - x coordinate of end point 1
 * \param[in] y1 - y coordinate of end point 1
 * \param[in] x2 - x coordinate of end point 2
 * \param[in] y2 - y coordinate of end point 2
 * \param[in] x3 - x coordinate of end point 3
 * \param[in] y3 - y coordinate of end point 3
 */
extern 
WOGLAPI void wogl_draw_triangle( int x1, int y1,
                        int x2, int y2,
                        int x3, int y3); 


/**
 * \brief Draw an image from file to the screen with a starting coordinate and 
 * scaling dimensions.
 * 
 * 
 * Location  - this is relative to (0,0) which is assumed as the the bottom-left 
 * corner of the window. This point is the center of the image to be drawn. 
 * 
 * Scaling - The actual details of the image file format, size, colour ranges do 
 * not need specifying, this is obtained automatically when reading the file. 
 * The scale of the image is normalised and stretched according to the width and 
 * height parameters. 
 * 
 * Filename - An image filename can be specified by full path or relative to 
 * the current working directory. 
 * 
 * 
 * <h3>Example - rendering the bumblebee image at location 34,23 with size 50x50</h3>
 * <pre>
 * wogl_render_image("images/bumblebee.png", 34, 23, 50, 50);
 * </pre>
 * 
 * 
 * \param[in] filename path to image file. Full path or relative to current working directory.
 * \param[in] x,y render location of the center of the image to render from
 * \param[in] width,height dimensions of the image to render (in pixels)
 */
extern 
WOGLAPI int wogl_render_image(const char *filename, 
        int x, int y, int width, int height);


/**
 * \brief Draw text at location with a chosen font size. 
 * 
 * Location  - this is relative to (0,0) which is assumed as the the bottom-left 
 * corner of the window. 
 * 
 * Format string - The text parameter can be used in the same way as stdio printf 
 * format string. Variables can follow the string as parameters to be rendered. 
 * 
 * <h3>Example</h3>
 * <pre>
 * int value = 12;
 * wogl_render_text(100, 100, medium_font, "Variable has value: %d\n", value);
 * </pre>
 * 
 * \param[in] x,y render location of the lower left corner of the text to render
 * \param[in] font_size size of font to use
 * \param[in] text a pointer to the set of characters, the string, to render. ASCII characters only.
 * \param[in] ... optional parameters for use with format string text.
 */
extern 
WOGLAPI int wogl_render_text(int x, int y, enum wogl_font_size font_size, const char *text, ...);



/** 
 * \brief Register the keyboard function that is called when a key is pressed.
 * 
 * When the user presses a key the function parameter keypressed is called 
 * with the key code. Special key codes for arrow and escape are recognised 
 * with WOGL_KEY_X where X is UP, DOWN, LEFT, RIGHT, ESCAPE
 * 
 * \param keypressed the function in user code to be called when a keyboard event happens.
 */
extern 
WOGLAPI void wogl_set_keyboard_callback( void (*keypressed) (int key) );


/**
 * \brief Register the display function that is called when rendering needs to happen.
 *  
 * The function 'display' is repeatedly called by wogl. This can be considered 
 * as the main body of the program.
 * 
 * \param display the function in user code to be called when display event happens.
 */
extern 
WOGLAPI void wogl_set_display_callback( void (*display) (void) );

/* Advanced */

#ifndef DOXYGEN_IGNORE2

/** Get window dimensions
 * \param[out] size the width, height of the window 
 */
extern 
WOGLAPI void wogl_get_window_size(int size[2]);

/**
 * \brief Register the resize event with the function that is called when rendering needs to happen.
 * \param resize function
 */
extern
WOGLAPI void wogl_set_window_resize_callback( void (*resize) (int width, int height) );

/**
 * \brief Set when wogl will automatically redraw at after each execution of the display function. 
 * 
 * Explicitly define if wogl will automatically redraw the frame if key is 
 * pressed or user display function has finished. 
 * When false, the programmer must explicitly call wogl_draw_frame() to 
 * refresh the display.
 * 
 * \param auto_redraw flag to set automatic redraw on/off
 * 
 */
extern 
WOGLAPI bool wogl_set_auto_redraw(bool auto_redraw);


/**
 * \brief Draw the contents to display 
 * 
 * Used with the auto draw feature. This will allow control of when the screen 
 * contents will be displayed.
 * 
 * \return WOGL_SUCCESS if successful
 */
extern 
WOGLAPI int wogl_draw_frame();


/** 
 * \brief Sleep for a number of milliseconds
 * 
 * \param stime milliseconds to sleep
 */
extern 
WOGLAPI void wogl_milli_sleep(unsigned long stime);

/** 
 * \brief After called, points are drawn with the 'size' in pixels 
 * 
 * Adjust the size of the points to be drawn. The size is measured in pixels.
 * 
 * \param size number of pixels to use when drawing a point
 */
extern
WOGLAPI void wogl_set_point_size(float size);

/** 
 * \brief After called, lines are drawn with their 'width' in pixels.
 * 
 * \param width number of pixels thick to use when drawing a line
 * 
 */
extern
WOGLAPI void wogl_set_line_thickness(float width);

/** 
 * \brief Set the color of the background r, g, b values range from 0.0-1.0 
 * 
 * \param r,g,b red green blue colour values 0.0-1.0. Representing the intensity of each channel.
 */
extern
WOGLAPI void wogl_set_clear_color_rgb(float r, float g, float b);

/* Set the color of points, lines, and triangles to be drawn
 * r, g, b values range from 0.0-1.0 
 */
extern
WOGLAPI void wogl_set_color_rgb(float r, float g, float b);


/** 
 * \brief End the continuous rendering callback
 * 
 * While this does not actually end the wogl instance. The window is closed 
 * and the rendering repeated callback is detached. There is still a display event.
 * 
 */
extern
WOGLAPI void wogl_close(void);


#endif /* DOXYGEN_IGNORE */


#endif	/* WOGL_H */

