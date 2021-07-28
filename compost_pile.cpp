//=================================================================
// The file is for module "compost pile"
//
// Copyright 2020 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

#include "compost_pile_private.h"

COMPOST compost_record[NUM_PILE];
int tallest_pile_height;


// See the comments in compost_pile_public.h
void compost_pile_init() {
    for(int i = 0; i < NUM_PILE; i++) {
        compost_record[i].x = i * 11;
        compost_record[i].y = 127;
        compost_record[i].width = PILE_WIDTH;
        if(i ==6){
        compost_record[i].height = 0;
        } else if(i==7){
        compost_record[i].height = 0;
        }else {
            compost_record[i].height = 5;
        }
    }
    tallest_pile_height = 5;

}

COMPOST compost_get_info(int index){
    
    if (index > 10) {
        printf("error in compst_get_info index");
    }
    return compost_record[index];

}

void compost_add(int index) {
    compost_record[index].height += 5;

}

void compost_rem(int index) {
    if(compost_record[index].height > 2){
    compost_record[index].height = compost_record[index].height - 5;
    }
    tallest_pile_height = tallest_pile_height-5;

}

void draw_compost(void){
    // bounding box look at fruit
    for(int i = 0; i < NUM_PILE; i++) {
        uLCD.filled_rectangle(compost_record[i].x, compost_record[i].y-8, compost_record[i].x + compost_record[i].width, compost_record[i].y - compost_record[i].height-8, BLACK);
        uLCD.filled_rectangle(compost_record[i].x, compost_record[i].y, compost_record[i].x + compost_record[i].width, compost_record[i].y - compost_record[i].height, GREEN);
    }

}

int get_compost_tallest_height() {
    int max = -1;
    for(int i = 0; i < NUM_PILE; i++) {
        
        if(compost_record[i].height > max) {
         max = compost_record[i].height;   
        }
    }

    return tallest_pile_height;

}

int get_compost_tallest_height_index() {
    int max = -1;
    int index = 0;
    for(int i = 0; i < NUM_PILE; i++) {
        
        if(compost_record[i].height > max) {
         max = compost_record[i].height;  
         index = i;  
        }
    }
    return index;

}


int get_compost_height(int index) {
    return compost_record[index].height;

}