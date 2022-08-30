//Initialization class for player
#include <raylib.h>
class pad {

	public:        //position of the player     
		int posx;        
		int posy;  
		
		pad(int x,int y)// get position
		{
			this->posx = x;
            this->posy = y;
		}
		//draw player
        void drawpad()
        {
            DrawRectangle(posx, posy, 200, 20, GRAY);
        }
        //for the robot player move with the ball
        int follow(int y)
        {
            if(posy+100>y and posy>0)
                return -2;
            else if(posy+200>y and posy+200 < 450)
                return 2;
            else
                return 0;
        }
};


