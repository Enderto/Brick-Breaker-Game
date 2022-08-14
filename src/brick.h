
class brick
{
    public:
        //position of the button
        float x;
        float y;
        float w = 60;
        float h = 20 ;
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
        
        bool col(int cx, int cy)
        {
            Vector2 coll = {static_cast<float>(cx),static_cast<float>(cy)};
            Rectangle Cord = {x,y,w,h};
            if (CheckCollisionCircleRec(coll,15, Cord))
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