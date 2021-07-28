#include "graphics.h"
#include "globals.h"

#define YELLOW 0xFFFF00
#define BLUE   0x0000FF
#define GREEN 0x00FF00
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define BROWN  0xD2691E
#define DIRT   BROWN
#define RED    0xFF0000
#define ORANGE 0xFFA500
#define PURPLE 0xD0B4DC
void draw_img(int u, int v, const char* img) //
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == 'P') colors[i] = PURPLE;
        else if (img[i] == 'B') colors[i] = BROWN;
        else if (img[i] == 'O') colors[i] = ORANGE;
        else if (img[i] == 'U') colors[i] = BLUE;
        else if (img[i] == 'W') colors[i] = WHITE;
        // else if (img[i] == '5') colors[i] = LGREY;
        // else if (img[i] == '3') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(500); // Recovery time!
}

void draw_img_l(int u, int v, const char* img) //
{
    int colors[15*15];
    for (int i = 0; i < 15*15; i++)
    {
       if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == 'P') colors[i] = PURPLE;
        else if (img[i] == 'B') colors[i] = BROWN;
        else if (img[i] == 'O') colors[i] = ORANGE;
        else if (img[i] == 'U') colors[i] = BLUE;
        else if (img[i] == 'W') colors[i] = WHITE;
        // else if (img[i] == '5') colors[i] = LGREY;
        // else if (img[i] == '3') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 15, 15, colors);
    wait_us(500); // Recovery time!
}

void draw_player(int u, int v, int key)
{
    uLCD.filled_rectangle(u, v, u+11, v+11, WHITE);
}

void draw_nothing(boundingBox b)
{
    // Erase a bounding box
    uLCD.filled_rectangle(b.topLeft.x, b.topLeft.y, b.bottomRight.x, b.bottomRight.y, BLACK);
}

void draw_banana_m(boundingBox b) 
{
    
    int u = b.topLeft.x; 
    int v = b.topLeft.y;
    const char* img = " Y         "
        " YY        "
        "  YYY      "
        "   YYYY    "
        "   YYYY    "
        "   YYYY    "
        "   YYYY    "
        "   YYYY    "
        "  YYY      "
        " YY        "
        " Y         ";
        
    draw_img(u, v, img);    
}

void draw_grapes(boundingBox b) 
{
    
    int u = b.topLeft.x; 
    int v = b.topLeft.y;
    const char* img = "BBBBBBBBBBB"
         "   GGG     "
         " PPPPPPPPP "
         " PPPPPPPPP "
         "  PPPPPPP  "
         "  PPPPPPP  "
         "   PPPPP   "
         "   PPPPP   "
         "    PPP    "
         "    PPP    "
         "     P     ";
        
    draw_img(u, v, img);    
}

void draw_heart(boundingBox b) 
{
    
    int u = b.topLeft.x; 
    int v = b.topLeft.y;
    const char* img = "  RRR  RR  "
         "  RR  RRR  "
         " RRRR RRRR "
         " RRRR RRRR "
         " RRRRRRRRR "
         "  RRRRRRR  "
         "  RRRRRRR  "
         "   RRRRR   "
         "   RRRRR   "
         "    RRR    "
         "    RRR    "
         "     R     ";
        
    draw_img(u, v, img);    
}

void draw_explosion(boundingBox b) 
{
    
    int u = b.topLeft.x; 
    int v = b.topLeft.y;
    const char* img = "  RO   RO  "
         "  ROR  ROR  "
         " RORORORORO "
         "  RORRROR   "
         "  ORORORO   "
         " RORORORORO "
         "OROROROROROO"
         "  ORORORO   "
         "  RORRROR   "
         " RORORORORO "
         "  ROR  ROR  "
         "  RO   RO  ";
        
    draw_img(u, v, img);    
}

void draw_banana_l(boundingBox b) 
{
    
    int u = b.topLeft.x; 
    int v = b.topLeft.y;
    const char* img = "   Y           "
        "   YY          "
        "    YYY        "
        "     YYYY      "
        "     YYYYY     "
        "     YYYYY     "
        "     YYYYYY    "
        "     YYYYYY    "
        "     YYYYY     "
        "     YYYYY     "
        "     YYYY      "
        "     YYYY      "
        "    YYY        "
        "   YY          "
        "   Y           ";
        
    draw_img_l(u, v, img);    
}




void draw_bomb(boundingBox b)
{
    // Draw an apple using a filled_rectangle or get creative and use a sprite!
    
    int u = b.topLeft.x; 
    int v = b.topLeft.y;
    const char* img = "     R     "
         "     W     "
         "   UUUUU   "
         "  UUUUUUU  "
         "  UUUUUUU  "
         " UUUUUUUUU "
         " UUUUUUUUU "
         " UUUUUUUUU "
         "  UUUUUUU  "
         "  UUUUUUU  "
         "   UUUUU   ";
        
    draw_img(u, v, img); 
}

void draw_bomb_l(boundingBox b) 
{
    
    int u = b.topLeft.x; 
    int v = b.topLeft.y;
    const char* img = "       R       "
        "      RRR      "
        "       W       "
        "     UUUUU     "
        "    UUUUUUU    "
        "   UUUUUUUUU   "
        "  UUUUUUUUUUU  "
        " UUUUUUUUUUUUU "
        " UUUUUUUUUUUUU "
        " UUUUUUUUUUUUU "
        " UUUUUUUUUUUUU "
        "  UUUUUUUUUUU  "
        "   UUUUUUUUU   "
        "    UUUUUUU    "
        "     UUUUU     ";
    draw_img_l(u, v, img);    
}


void draw_orange(boundingBox b) {
    int u = b.topLeft.x; 
    int v = b.topLeft.y;
    const char* img = 
         "    OOO    "
         "   OOOOO   "
         "  OOOOOOO  "
         "  OOOOOOO  "
         " OOOOOOOOO "
         " OOOOOOOOO "
         " OOOOOOOOO "
         "  OOOOOOO  "
         "  OOOOOOO  "
         "   OOOOO   "
         "    OOO    ";
        
    draw_img(u, v, img); 
}

void draw_box(boundingBox b)
{
// Draw an orange using a filled_rectangle or get creative and use a sprite!
    uLCD.filled_rectangle(b.topLeft.x, b.topLeft.y, b.bottomRight.x, b.bottomRight.y, ORANGE);
}
