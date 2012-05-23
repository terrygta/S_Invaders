#ifndef _invade_h
#define _invaderType_h

#include <string>

using namespace std;

//invaderType class
class InvaderType {
public:
    string image; //the image file path of this invader
    int life; //the life value of the invader.
    int score; //the score of distorying this invader
    InvaderType();
    InvaderType(string invaderImage, int invaderLife, int invaderScore):image(invaderImage), life(invaderLife), score(invaderScore) {}
};

#endif