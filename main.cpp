//=================================================================
// The main program file.
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// External libs
#include <stdlib.h>

// Project includes
#include "globals.h"
#include "hardware.h"
#include "doubly_linked_list.h"
#include "compost_pile_public.h"
#include "fruit_public.h"
#include "player_public.h"

//For sound components
////AnalogOut DACout(p18);
//PwmOut pwmout(p26);
////PwmOut speaker(p25);

////wave_player waver(&DACout);
//SDFileSystem sd(p5, p6, p7, p8, "sd"); // mosi, miso, sck, cs

DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);

// ===User implementations start===
int fruit_contact(void); // iterate through fruits and see if any collided
void compost_pile_update(void);
bool winGame = false;
bool playGame = true;
int speed = 5;
void playSound(char * wav);
void playNotes(void);
void set_random_seed(Timer);

int main()
{
    
    GameInputs inputs; 
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    inputs = read_inputs();
    
    pc.printf("Program Starting\n");

    // ===User implementations start===
    // Game state variables
    
    // Timer to measure game update speed (secondarily used to generate random seed)
    Timer t;
    int dt; // delta time
    set_random_seed(t);
 
    //pwmout.period(1.0/4000.0);
    //playSound("/sd/wavfiles/BUZZER.wav");//test the sound convert to thread
    //wait(0.1);
    //playNotes();
    
    //initialize functions
    
    // doesnt start game until button pressed
    while(inputs.b1  && inputs.b2 && inputs.b3) {
       inputs = read_inputs();
    }
    
    compost_pile_init();
    fruit_init();
    player_init(); 
    
    if(!inputs.b1){ // changes difficulty/board rate depending on which button used to start the game
       speed = 3; 
       easy();
    }else if(!inputs.b3) {
        speed = 8;
        hard();
    } else {
        speed =5;
        medium();
    }
    
       
    uLCD.baudrate(115200);
        //uLCD.printf("$d", player.score);  
    pc.printf("Initialization complete\n");
    
    pc.printf("1");
    
    while(playGame)
    {
        t.start();
        uLCD.text_height(1);
        uLCD.locate(0,0);
        uLCD.printf("score:%2d lives:%1d  strikes:%1d", player_get_info().score, player_get_info().numLives, player_get_info().numStrikes);
         
        // Draw fruits first
        //pc.printf("fruit_generator\n");
        if(player_get_info().score >= 3){
            fruit_generator(speed, 7);
        } else {
             fruit_generator(speed, 5);
        }
        
        //Put score on screen
        // NOTE: Text is 8 pixels tall
        

        //pc.printf("player_fruit_draw\n");
        
        
        
        
        //pc.printf("Reading inputs\n");
        inputs = read_inputs();
         if(!inputs.b4) {
            while(inputs.b1  && inputs.b2 && inputs.b3) {
                inputs = read_inputs();
            }
        }
       // printf("accelerometer: %d, %d, %d", inputs.ax, inputs.ay, inputs.az);
        //printf("b1 %B", inputs.b1);
        //printf("b2 %B", inputs.b2);
        //printf("b3 %B", inputs.b3);
        

        

        //pc.printf("player motions\n");
        if (!inputs.b1 || inputs.ay>=0.3){
             pc.printf("moved");
             player_moveUp();            
        }
        if (!inputs.b2 || inputs.ay<= -0.3) player_moveDown();                
        if (!inputs.b3){ 
            player_throw();
        }
        
    

        if(player_get_info().knifeOne == false || player_get_info().knifeTwo == false){
            update_knifeposition();
        }
          if(player_get_info().knifeTwo == false){
            update_knife2position();
        }
          
     
        //pc.printf("compost_pile_update\n");
        compost_pile_update();
        if(get_compost_tallest_height() >= 55) {
            playGame = false;
        }
        
        
        

        //pc.printf("fruit_contact\n");
        int is_bomb = fruit_contact();
        if(is_bomb == 1) { // checks if bomb hit, if yes then reduces no of lives
            decNumLives();
            if(player_get_info().numLives <= 0 ||player_get_info().numStrikes <=0 ) { // checks if player has lives,if not ends game.
                playGame = false;
            }
        }
        if(player_get_info().numStrikes <=0 ) {
         playGame = false;   
        }
        
        
      
        // TODO: Check end of the game        
        //pc.printf("check endgame\n");
        
        // TODO: Check if game won
        if(player_get_info().score >= 80) {
            winGame = true;
            playGame = false;
            
        }
        // Compute update time
        t.stop();
        dt = t.read_ms();
            
        if (dt < 100) wait_ms(100 - dt);
    }
    pc.printf("out of main loop\n");
    destroyList(get_fruit_list());
    if(winGame) {
        uLCD.text_height(5);
        uLCD.locate(0,0);
        uLCD.printf("You Won! Congratulations!");
    } else{
        uLCD.text_height(5);
        uLCD.locate(0,0);
        uLCD.printf("You Lost! Hope you had fun!");
    }
    
    return 0;
    // ===User implementations end===
}


// ===User implementations start===

/* This function iterate through the fruit list, checking if anyone one of them is contacting 
*  with the player's knife. Don't forget to check if the "fruit" is the bomb, since we 
*  generated bombs using the fruit_generator. 
*/ 
int fruit_contact(void) {
    
    PLAYER player = player_get_info();
    LLNode*  currNode = getHead(get_fruit_list());
    FRUIT* curr = (FRUIT*) getData(currNode);
    
    while (currNode) {
        
        bool x_check = player.knife_boundingBox.topLeft.x >= curr->box.topLeft.x && curr->box.bottomRight.x >= player.knife_boundingBox.topLeft.x || player.knife_boundingBox.bottomRight.x <= curr->box.bottomRight.x && curr->box.topLeft.x <= player.knife_boundingBox.bottomRight.x ;
        bool y_check = player.knife_boundingBox.topLeft.y <= curr->box.bottomRight.y && curr->box.topLeft.y <= player.knife_boundingBox.topLeft.y || player.knife_boundingBox.bottomRight.y <= curr->box.bottomRight.y && curr->box.topLeft.y <= player.knife_boundingBox.bottomRight.y ;  
        
        
        bool x_check2 = player.knife2_boundingBox.topLeft.x >= curr->box.topLeft.x && curr->box.bottomRight.x >= player.knife2_boundingBox.topLeft.x || player.knife2_boundingBox.bottomRight.x <= curr->box.bottomRight.x && curr->box.topLeft.x <= player.knife2_boundingBox.bottomRight.x ;
        bool y_check2 = player.knife2_boundingBox.topLeft.y <= curr->box.bottomRight.y && curr->box.topLeft.y <= player.knife2_boundingBox.topLeft.y || player.knife2_boundingBox.bottomRight.y <= curr->box.bottomRight.y && curr->box.topLeft.y <= player.knife2_boundingBox.bottomRight.y ;  
        //check intersection of bounding boxes
        if(y_check && x_check) { //means the knife and fruit meet
        
            if(curr->draw == draw_bomb || curr->draw == draw_bomb_l) {
                pc.printf("game over/n");
                draw_explosion(curr->box);
                curr->status = FRUIT_SLICED;
                player_knife_return();
                return 1;
            } else {
                if(curr->draw == draw_heart) {
                    incNumLives(); 
                } else if(curr->draw == draw_grapes){
                    compost_rem(get_compost_tallest_height_index());
                } else{
                    pc.printf("score inc\n");
                    player_score_inc_one();
                    comboKnifeOne();
                }
                pc.printf("new score s %d", player_get_info().score);
                curr->status = FRUIT_SLICED;
                
                player_knife_return();
            }
        
        }
        
        if(y_check2 && x_check2) { //means the knife and fruit meet
        
            if(curr->draw == draw_bomb || curr->draw == draw_bomb_l) {
                pc.printf("game over/n");
                draw_explosion(curr->box);
                curr->status = FRUIT_SLICED;
                player_knife2_return();
                return 1;
            }  else {
                if(curr->draw == draw_heart) {
                    incNumLives(); 
                }else if(curr->draw == draw_grapes){
                    compost_rem(get_compost_tallest_height_index());
                } else{
                    pc.printf("score inc\n");
                    player_score_inc_two();
                    comboKnifeTwo();
                }
                pc.printf("new score s %d", player_get_info().score);
                curr->status = FRUIT_SLICED;
                
                player_knife2_return();
            }
        
        }
        
        currNode = getNext(currNode);
        if(currNode != NULL) {
        curr = (FRUIT*) getData(currNode);
        }
       
    }
    return 0;
}

/** Call compost_pile_update() repeatedly in your game-loop. ex: main()
    This function iterate through the fruit list. Add fruits that reach the bottom of the screen
    to the compost pile.
    @return  Number of remaining cities. You might end the game when all cities are demolished.
*/
void compost_pile_update(void){
// when fruit becomes a compost i just remove it from the dll, dont have to change status to slice
    LLNode*  currNode = getHead(get_fruit_list());
    FRUIT* curr = (FRUIT*) getData(currNode);
    bool tetris = false;
    while (currNode) {
        tetris = true;
        for(int i = 0; i <11; i++) { // not checking bounding box properly
            if(get_compost_height(i) < 4){ // for tetris functionality
                tetris = false;
            }
            bool x_check = compost_get_info(i).x <= curr->box.topLeft.x && curr->box.topLeft.x <= compost_get_info(i).x + compost_get_info(i).width || compost_get_info(i).x <= curr->box.bottomRight.x && curr->box.bottomRight.x <= compost_get_info(i).x + compost_get_info(i).width ;
            bool y_check = curr->box.bottomRight.y >= compost_get_info(i).y - get_compost_height(i) || compost_get_info(i).y <= curr->box.topLeft.y && curr->box.topLeft.y <= compost_get_info(i).y - get_compost_height(i) ;  
        //check intersection of bounding boxes
            if(y_check && x_check) { //means the knife and fruit meet
            
                if(curr->draw == draw_bomb || curr->draw == draw_bomb_l) {
                } else {
                pc.printf("add to compost");
                    curr->status = FRUIT_SLICED;
                    compost_add(i);
                    continue;
                }
            }
        }
        currNode = getNext(currNode);
        if(currNode != NULL) {
        curr = (FRUIT*) getData(currNode);
        }
    }
    
    if(tetris) {
        pc.printf("tetris pass");
        player_score_dec();
        for(int i = 0; i <11; i++) {
            compost_rem(i);
        }
    }
    draw_compost();
}

//fcn to play a wav
void playSound(char* wav)
{
    //open wav file
    FILE *wave_file;
    wave_file=fopen(wav,"r");
    
    if(wave_file != NULL) 
    {
        printf("File opened successfully\n");

        //play wav file
        printf("Sound playing...\n");
        waver.play(wave_file);
    
        //close wav file
        printf("Sound stopped...\n");
        fclose(wave_file);
        return;
    }
    
    printf("Could not open file for reading - %s\n", wav);
        return;
}

/* Wanna hear some annoying sounds?*/
void playNotes(void)
{
    int i;
// generate a 500Hz tone using PWM hardware output
    speaker.period(1.0/500.0); // 500hz period
    speaker =0.5; //50% duty cycle - max volume
    wait(3);
    speaker=0.0; // turn off audio
    wait(2);
// generate a short 150Hz tone using PWM hardware output
// something like this can be used for a button click effect for feedback
    for (i=0; i<10; i++) {
        speaker.period(1.0/150.0); // 500hz period
        speaker =0.25; //25% duty cycle - mid range volume
        wait(.02);
        speaker=0.0; // turn off audio
        wait(0.5);
    }

// sweep up in frequency by changing the PWM period
    for (i=0; i<8000; i=i+100) {
        speaker.period(1.0/float(i));
        speaker=0.25;
        wait(.1);
    }
    wait(2);

// two tone police siren effect -  two periods or two frequencies
// increase volume - by changing the PWM duty cycle
    for (i=0; i<26; i=i+2) {
        speaker.period(1.0/969.0);
        speaker = float(i)/50.0;
        wait(.5);
        speaker.period(1.0/800.0);
        wait(.5);
    }
    // decrease volume
    for (i=25; i>=0; i=i-2) {
        speaker.period(1.0/969.0);
        speaker = float(i)/50.0;
        wait(.5);
        speaker.period(1.0/800.0);
        wait(.5);
    }
    speaker =0.0;
    wait(2);
}

void set_random_seed(Timer t) {
    GameInputs inputs; 
    t.start();
    uLCD.printf("Push any button to start.\n");
    while(1){
      inputs = read_inputs();
      if (inputs.b1 || inputs.b2 || inputs.b3) break;
      }
    uLCD.cls();
    t.stop();
    int seed = t.read_ms();    
    srand(seed);
    }
// ===User implementations end===
