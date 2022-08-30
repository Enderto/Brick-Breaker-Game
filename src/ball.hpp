
//Initialization class for the ball
#include <iostream>
#include <raylib.h>
#include <vector>
#include "brick.hpp"
using namespace std;

//using std::vector;

class ball {
	public:             
        //position of the ball
        int posx;        
		int posy; 
        //position when we want to reset the ball
        int centerx;
        int centery;

        Vector2 ballPosition;
        Vector2 speed = { 5.0f, 4.0f };
        int ballRadius = 15;
		
		ball(int x,int y)// get position
		{
			this->posx = x;
            this->posy = y;
            this->centerx = x;
            this->centery = y;
            ballPosition = {static_cast<float>(posx),static_cast<float>(posy)};
		}
        //apply the velocity of the ball
        void update()
        {
            ballPosition.x += speed.x;
            ballPosition.y += speed.y;

            if(speed.x > 6)
                speed.x=6;
            if(speed.y > 6)
                speed.y = 6;

            bounce();
        }
         void reset()
        {
            speed.x = 2;
            speed.y = 2;
            this->posx = centerx;
            this->posy = centery;
            
        }
		//draw ball
        void drawball()
        {
            DrawCircle(ballPosition.x, ballPosition.y, 15, GRAY);
        }

        void bounce()
        {
            
            if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius)) speed.x *= -1.0f;
            if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) speed.y *= -1.0f;

        }
        void bouncebob(int x, int y, int w, int h)
        {
            Vector2 lucien = {ballPosition.x+speed.x,ballPosition.y+speed.y};
            Rectangle left = {static_cast<float>(x),static_cast<float>(y+0.5),0.1,static_cast<float>(h-0.5)};
            if(CheckCollisionCircleRec(lucien, ballRadius, left))
            {
                speed.x *= -1.0f;
                speed.y *= -1.0f;

            }

            Rectangle right = {static_cast<float>(x+w),static_cast<float>(y+0.5),-0.1,static_cast<float>(h-0.5)};
            if(CheckCollisionCircleRec(lucien, ballRadius, right))
            {
                speed.x *= -1.0f;
                speed.y *= -1.0f;
            }
            Rectangle rec = {static_cast<float>(x+0.1),static_cast<float>(y),static_cast<float>(w-0.1),static_cast<float>(h)};
            if(CheckCollisionCircleRec(lucien, ballRadius, rec))
            {
                speed.y *= -1.0f;
                
                
            }
           
        }
};



