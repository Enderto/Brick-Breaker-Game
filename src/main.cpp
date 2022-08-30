#include <raylib.h>
#include "ball.hpp"
#include "tool.hpp"
#include "pad.hpp"
#include "brick.hpp"
#include <vector>
#include <iostream>
#include <cstdlib>

using std::vector;
// Types and Structures Definition


typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

int main(void)
{
    // Initialization

    //screen
    int screenWidth = 1200;
    int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Breakers");
    SetTargetFPS(60);

    //player
    pad player1(20,600);
    //ball
    ball b(rand()% screenWidth + 10,screenHeight/2);
    //score
    int scoreP1 = 0;

    //current game screen
    GameScreen currentScreen = LOGO;
    bool GameStart = false ;
    //load logo
    Texture2D texture = LoadTexture("assets/logo2.png");
    //mouse position
    Vector2 mousePoint = { 0.0f, 0.0f };

    const int SIZE = 10;
    int wall[SIZE][SIZE] =  {
                            {0,1,1,0,2,1,0,2,1,2},
                            {1,0,0,2,0,2,0,2,2,1}
            };
    //test shema

    vector<brick> brickList;
    brickList.clear();


	for (int i=0; i<SIZE; ++i)
	{
        for (int k=0; k<SIZE; ++k)
        {
            if(wall[i][k]>0)
            {
                if(wall[i][k]==1)
                {
                    brick SomeBrick(100+(85*k),100*(i+1%10),GRAY);
                    brickList.push_back(SomeBrick);
                }
                if(wall[i][k]==2)
                {
                    brick SomeBrick(100+(85*k),100*(i+1%10)+1,RED);
                    brickList.push_back(SomeBrick);

                }

            }
        }

    }
    //other
    int framesCounter = 0;

    button start((screenWidth/2.0)-20,(screenHeight/2.0),150,40,GREEN,"Start");
    button credit((screenWidth/2.0)-20,(screenHeight/2.0)+50,150,40,YELLOW,"Credit");
    button option((screenWidth/2.0)-20,(screenHeight/2.0)+100,150,40,BLUE,"option");
    button exit((screenWidth/2.0)-20,(screenHeight/2.0)+150,150,40,RED,"exit");

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        mousePoint = GetMousePosition(); //Get mouse position

        // Update
        switch(currentScreen)
        {
            case LOGO:
            {
                framesCounter++;    // Count frames

                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter > 120)
                {
                    currentScreen = TITLE;
                }
            } break;
            case TITLE:
            {
                // TODO: Update TITLE screen variables here!

                // Press enter to change to GAMEPLAY screen

                //if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                if (start.ButtonPress(mousePoint)&& IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GAMEPLAY;
                }

                if (exit.ButtonPress(mousePoint)&& IsGestureDetected(GESTURE_TAP))
                {
                    UnloadTexture(texture);
                    CloseWindow();
                }

            } break;
            case GAMEPLAY:
            {
                //control
                //if (IsKeyDown(KEY_UP) and player1.posy>0) player1.posy -= 2.0;
                //if (IsKeyDown(KEY_DOWN) and player1.posy+200<screenHeight) player1.posy += 2.0;
                player1.posx = mousePoint.x-100;
                //update ball
                b.update();
                b.bouncebob(player1.posx,player1.posy,200,20);

                //cout<<"x = "<<b.ballPosition.x<<"\n y = "<<b.ballPosition.y<<"\n";
                if(b.posy+b.ballRadius+10>screenHeight)
                {
                    if(b.posx<0)
                        scoreP1++;

                    b.reset();

                }

                for (int j=0; j<sizeof(wall); ++j)
                {
                    if(brickList[j].col(b.ballPosition,b.ballRadius))
                    {
                        b.bouncebob(brickList[j].x,brickList[j].y,brickList[j].w,brickList[j].h);

                        brickList[j].del();
                       //brickList.erase(brickList.begin() + j);//test
                    }


                }

            } break;
             default: break;
        }
        // Draw thing on screen
        BeginDrawing();
            ClearBackground(RAYWHITE);

            switch(currentScreen)
            {
                case LOGO:
                {

                    ClearBackground(GRAY);
                    // Draw logo
                    DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);


                } break;
                case TITLE:
                {
                    //Draw the start menu
                    DrawRectangle(0, 0, screenWidth, screenHeight, GRAY);//background
                    start.drawbut();
                    credit.drawbut();
                    option.drawbut();
                    exit.drawbut();
                    DrawText("PONG", screenWidth/3, 40, 40, BLACK);
                    DrawText("Made by Enderto", screenWidth/1.5, screenHeight-30, 20, BLACK);


                } break;
                case GAMEPLAY:
                {
                    //draw the game
                    ClearBackground(RAYWHITE);
                    //draw bricks
                    for (int j=0; j<sizeof(wall); ++j)
                    {
                        brickList[j].drawbrick();
                    }
                    //Draw scores

                    DrawText("Scores:", (screenWidth/2)-15, 650, 20, LIGHTGRAY);
                    DrawText(TextFormat("%01i", scoreP1), (screenWidth/2)-30, 650, 20, LIGHTGRAY);
                    //Draw player & ball
                    player1.drawpad();
                    b.drawball();
                    //drawbrick();

                } break;
                 default: break;
            }



        EndDrawing();

    }

    // De-Initialization
    brickList.clear();
    brickList.erase(brickList.begin(),brickList.end());
    UnloadTexture(texture);
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
