/*
 * menu.h
 *
 * Created: 23.09.2015 11:28:52
 *  Author: vegasten
 */ 


#ifndef MENU_H_
#define MENU_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "OLED_driver.h"

struct Menu {
	char* title;
	struct Menu* parent;
	struct Menu** children;
	struct Menu* selected;
	int length;
};
typedef struct Menu Menu_t;

enum MenuDirection {
	MENU_UP,
	MENU_DOWN,
};
typedef enum MenuDirection MenuDirection_t;

Menu_t* menu_create(const char* content);
void menu_free(Menu_t* menu);
void menu_add(Menu_t* prev, Menu_t* new_item);
void menu_draw(Menu_t* item, int line);

Menu_t* menu_create_start_menu();
int menu_move(Menu_t* item, MenuDirection_t direction);

#endif /* MENU_H_ */