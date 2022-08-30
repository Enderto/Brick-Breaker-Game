#ifndef MYHEADEFILE_H
#define MYHEADEFILE_H


#include <iostream>
#include <raylib.h>
#include<string>

using namespace std;
class brick
{
    public:
        //position of the button
        float x;
        float y;
        float w = 80;
        float h = 40 ;
        bool real = true;
        Rectangle Cord ;
        string text;
        //other 
        Color color;

        brick(float x, float y, Color c)
        {
            this->x = x;
            this->y = y;
            this->color=c;
        }
        void drawbrick()
        {
            DrawRectangle(x, y, w, h, color);
        }
        
        bool col(Vector2 ball, int ballrad)
        {
            //Vector2 coll = {static_cast<float>(cx),static_cast<float>(cy)};
            Rectangle Cord = {x,y,w,h};
            if (CheckCollisionCircleRec(ball,ballrad, Cord))
            {
                return true;
            }
            else
                return false;
        }

        void del()
        {
            x=0;
            y=0;
            w = 0;
            h = 0 ;
            real = false;
        }
};

#endif