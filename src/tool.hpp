#include <iostream>
#include<string>
#include <raylib.h>
using namespace std;

//colection of class for element reusable

class button
{
    public:
        //position of the button
        float x;
        float y;
        float w;
        float h;
        Rectangle Cord ;
        string text;
        //other 
        Color color;

        button(float x, float y, float w, float h, Color c,string txt)
        {
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
            this->color=c;
            this->text = txt;
        }
        
        bool ButtonPress(Vector2 mouse)
        {
            Rectangle Cord = {x,y,w,h};
            if (CheckCollisionPointRec(mouse, Cord))
            {
                return true;
            }
            else
                return false;
            
        }

        void drawbut()
        {
            DrawRectangle(x, y, w, h, color);
            DrawText(text.c_str(), x+5, y+5, 40, BLACK);
        }
};