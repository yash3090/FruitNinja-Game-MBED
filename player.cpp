//=================================================================
// Implementation for the player module
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================
#include "player_private.h"

PLAYER player; // structure of player

PLAYER player_get_info(void){
    return player;
}

void player_init(void) {    
    player.y = 100;                          // The y-coordinate of knife current position
    player.height = 10;
    player.score = 0;                      // Current score
    player.knife_length = 6;
    player.speed = 8;
    player.knife_boundingBox.topLeft.x = 5 ;
    player.knife_boundingBox.topLeft.y = player.y;
    player.knife_boundingBox.bottomRight.x = 5 + player.knife_length;
    player.knife_boundingBox.bottomRight.y = player.y + 2;
    
    player.knife2_boundingBox.topLeft.x = 5 ;
    player.knife2_boundingBox.topLeft.y = player.y;
    player.knife2_boundingBox.bottomRight.x = 5 + player.knife_length;
    player.knife2_boundingBox.bottomRight.y = player.y + 2;
    
    player.player_has_knife = true;
    player.knifeTwo = true;
    player.knifeOne = true;
    player.knifeOneCombo = 1;
    player.numStrikes = 7;
    player.knifeTwoCombo = 1;
    player.numLives = 2;
    player_draw(0xFFFFFF);

}

void player_moveUp(void) { 
    if (player.y - player.height > 0) {
      pc.printf("in func");
      uLCD.filled_rectangle(0, player.y, 5 + player.height, player.y + player.height, BLACK);
      uLCD.filled_rectangle(5, player.y + player.height, 5 + player.height, player.y + player.height + 2, BLACK);
      player.y -= player.height;
      player_draw(0xFFFFFF);
     
     // erase knife and erase player
 }

}

void player_moveDown(void) { 
 if ((player.y + player.height )< (127 - get_compost_tallest_height())) {
      uLCD.filled_rectangle(0, player.y, player.height, player.y + player.height, BLACK);
      uLCD.filled_rectangle(5, player.y, 5 + player.height, player.y + 2, BLACK);
      player.y += player.height;
      player_draw(0xFFFFFF);
     
     // erase knife and erase player
 }
}

void player_throw(void) { 
    if(player.knifeOne) {
      player.knifeOne = false;
      pc.printf("knife one thrown");
      player.player_has_knife = player.knifeTwo;
    } else if(player.knifeTwo){
        player.knifeTwo = false;
        player.player_has_knife = player.knifeOne;
        pc.printf("knife two thrown");
        
    } else {
        pc.printf("player doesnt have knives");
    }
}

// i created method to update knife position

void update_knifeposition(void) {

    if(!player.knifeOne) {
        if(player.knife_boundingBox.bottomRight.x > 127) {
            pc.printf("returned knife one");
            lostComboKnifeOne();
            player_knife_return();
        } else {
                uLCD.filled_rectangle(player.knife_boundingBox.topLeft.x, player.knife_boundingBox.bottomRight.y, player.knife_boundingBox.bottomRight.x, player.knife_boundingBox.topLeft.y, BLACK);
                player.knife_boundingBox.topLeft.x += player.speed;
                player.knife_boundingBox.bottomRight.x += player.speed;
                uLCD.filled_rectangle(player.knife_boundingBox.topLeft.x, player.knife_boundingBox.bottomRight.y, player.knife_boundingBox.bottomRight.x, player.knife_boundingBox.topLeft.y, WHITE);
        }
    } 
    
}

void update_knife2position(void) {
    if(!player.knifeTwo) {
             if(player.knife2_boundingBox.bottomRight.x > 127) {
                pc.printf("returned knife2");
                lostComboKnifeTwo();
                player_knife2_return();
            } else {
                    uLCD.filled_rectangle(player.knife2_boundingBox.topLeft.x, player.knife2_boundingBox.bottomRight.y, player.knife2_boundingBox.bottomRight.x, player.knife2_boundingBox.topLeft.y, BLACK);
                    player.knife2_boundingBox.topLeft.x += player.speed;
                    player.knife2_boundingBox.bottomRight.x += player.speed;
                    uLCD.filled_rectangle(player.knife2_boundingBox.topLeft.x, player.knife2_boundingBox.bottomRight.y, player.knife2_boundingBox.bottomRight.x, player.knife2_boundingBox.topLeft.y, WHITE);
                
            }
            
    }
}

void player_knife_draw(void) {
  
  uLCD.filled_rectangle(5, player.y, 5 + player.height, player.y + 2, WHITE);
}

void player_knife_return(void) {
    uLCD.filled_rectangle(player.knife_boundingBox.topLeft.x, player.knife_boundingBox.bottomRight.y, player.knife_boundingBox.bottomRight.x, player.knife_boundingBox.topLeft.y, BLACK);
    player.player_has_knife = true;
    player.knifeOne = true;
    player.knife_boundingBox.topLeft.x = 5 ;
    player.knife_boundingBox.topLeft.y = player.y;
    player.knife_boundingBox.bottomRight.x = 5 + player.knife_length;
    player.knife_boundingBox.bottomRight.y = player.y + 2;
    player_knife_draw();
}

void player_knife2_return(void) {
    uLCD.filled_rectangle(player.knife2_boundingBox.topLeft.x, player.knife2_boundingBox.bottomRight.y, player.knife2_boundingBox.bottomRight.x, player.knife2_boundingBox.topLeft.y, BLACK);
    player.player_has_knife = true;
    player.knifeTwo = true;
    player.knife2_boundingBox.topLeft.x = 5 ;
    player.knife2_boundingBox.topLeft.y = player.y;
    player.knife2_boundingBox.bottomRight.x = 5 + player.knife_length;
    player.knife2_boundingBox.bottomRight.y = player.y + 2;
    player_knife_draw();
}

// ==== player_private.h implementation ====
void player_draw(int color) {
    uLCD.filled_rectangle(0, player.y, player.height, player.y + player.height, WHITE); 
    if(player.knifeOne) {
    player.knife_boundingBox.topLeft.x = 5 ;
    player.knife_boundingBox.topLeft.y = player.y;
    player.knife_boundingBox.bottomRight.x = 5 + player.knife_length;
    player.knife_boundingBox.bottomRight.y = player.y + 2;
    }
    
    if(player.knifeTwo){
    player.knife2_boundingBox.topLeft.x = 5 ;
    player.knife2_boundingBox.topLeft.y = player.y;
    player.knife2_boundingBox.bottomRight.x = 5 + player.knife_length;
    player.knife2_boundingBox.bottomRight.y = player.y + 2;
    player_knife_draw();
    }
}

void player_score_inc_one(void) {
    player.score += player.knifeOneCombo; 
}

void player_score_inc_two(void) {
    player.score += player.knifeTwoCombo; 
}

void player_score_dec(void) {
    if(player.score >0){
    player.score -=1; 
    }
}

void strike(void) {
    player.numStrikes = player.numStrikes - 1;
}


void decNumLives(void) {
    player.numLives -= 1; 
}

void incNumLives(void) {
    player.numLives += 1; 
}

void comboKnifeOne(void){
        player.knifeOneCombo = player.knifeOneCombo + 1;
}

void comboKnifeTwo(void){
    player.knifeTwoCombo = player.knifeTwoCombo + 1;
}

void lostComboKnifeOne(void){
        player.knifeOneCombo = 1;
}

void lostComboKnifeTwo(void){
    player.knifeTwoCombo = 1;
}

void easy(void){
    player.speed = 15;
}
void medium(void){
    player.speed = 8;
}
void hard(void){
    player.speed = 4;
}

