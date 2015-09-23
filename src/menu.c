/*
 * menu.c
 *
 * Created: 23.09.2015 11:29:07
 *  Author: vegasten
 */ 

#include "menu.h"


Menu_t* menu_create(const char* title)
{
	int title_length = strlen(title);
	Menu_t* new_item = malloc(sizeof(Menu_t));
	new_item->title = malloc(sizeof(char) * (title_length+1));
	strcpy(new_item->title, title);
	new_item->parent = NULL;
	new_item->children = NULL;
	new_item->selected = NULL;
	new_item->length = 0;
	return new_item;
}

void menu_free(Menu_t* menu)
{
	free(menu->title);
	free(menu);
}

void menu_add(Menu_t* parent, Menu_t* child)
{
	parent->length++;
	
	parent->children = realloc(parent->children, sizeof(Menu_t*) * parent->length);
	if(!parent->children)
	{
		printf("Realloc in menu_add() failed !");
	}

	parent->children[parent->length - 1] = child;
	if(!parent->selected)
	{
		parent->selected = child;
	}
	child->parent = parent;
}

void menu_draw(Menu_t* menu, int line)
{
	OLED_goto_line(0);
	OLED_print(menu->title);
	for(int i = 0; i < menu->length; i++)
	{
		if(menu->children[i] == menu->selected)
			OLED_print_arrow(i + line, 0);
		OLED_pos(i + line, 8, 127 - 8);
		OLED_print(menu->children[i]->title);
	}
}

Menu_t* menu_create_start_menu()
{
	Menu_t* main_menu = menu_create("Main Menu");
	Menu_t* play_menu = menu_create("Play Game");
	menu_add(main_menu, play_menu);
	Menu_t* high_scores_menu = menu_create("High scores");
	menu_add(main_menu, high_scores_menu);
	Menu_t* settings_menu = menu_create("Settings");
	menu_add(main_menu, settings_menu);
	return main_menu;
}

int menu_get_selected_index(Menu_t* menu)
{
	for(int i = 0; i < menu->length; i++)
	{
		if(menu->children[i] == menu->selected)
			return i;
	}
	return -1;
}

int menu_move(Menu_t* menu, MenuDirection_t direction)
{
	if(!menu->selected)
		return -1;
	else
	{
		int index = menu_get_selected_index(menu);
		switch(direction)
		{
			case MENU_UP:
				if(index == 0)
					menu->selected = menu->children[menu->length - 1];
				else
					menu->selected = menu->children[index-1];
				break;
			case MENU_DOWN:
				if(index == (menu->length - 1))
					menu->selected = menu->children[0];
				else
					menu->selected = menu->children[index+1];
				break;
		}
		return 0;
	}
}