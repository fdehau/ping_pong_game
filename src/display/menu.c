/**
 * @file menu.c
 * @authors Vegard Stengrundet, Florian Dehau
 * @date 12 Nov 2015
 * @brief Functions to manage menus and draw them to the OLED display
 */

#include "menu.h"

/**
 * @brief Allocate for a new item and set fields to default values
 * @param title String that will be displayed on screen
 */
Menu_t * menu_create(const char* title)
{
    Menu_t* new_item = malloc(sizeof(Menu_t));

    // Set title
    new_item->title = malloc(sizeof(char) * (strlen(title) + 1));
    strcpy(new_item->title, title);

    // Default values for the rest of the fields
	new_item->parent   = NULL;
    new_item->children = NULL;
    new_item->selected = 0;
    new_item->length   = 0;

    return new_item;
}

/**
 * @brief Free the memory associated to a menu item
 * @param menu Menu that needs to be deleted
 */
void menu_free(Menu_t* menu)
{
    free(menu->title);
    free(menu);
}

/**
 * @brief Add a new sub menu to a given menu
 * @param parent An existing menu item that will act as a parent
 * @param child The new sub menu
 */
void menu_add(Menu_t* parent, Menu_t* child)
{
    // Prepare the parent to store new child node
    parent->length++;
    parent->children = realloc(parent->children,
                               sizeof(Menu_t*) * parent->length);
    if (!parent->children)
    {
        printf("Realloc in menu_add() failed !\n");
    }

    // Add the new sub menu
    parent->children[parent->length - 1] = child;
	child->parent = parent;
}

/**
 * @brief Helper function if you need to replace the title of an existing menu
 * item
 * @param menu An existing menu item
 * @param title New title for the menu item
 */
void menu_set_title(Menu_t* menu, char* title)
{
    free(menu->title);
    menu->title = malloc(strlen(title) + 1);
    strcpy(menu->title, title);
}

/**
 * @brief Draw a menu on the OLED display
 * @param menu Menu to be drawn
 * @param line Gap between the main menu title and the submenus titles
 */
void menu_draw(Menu_t* menu, int line)
{
    OLED_goto_line(0);
    OLED_print(menu->title);
    for (int i = 0; i < menu->length; i++)
    {
        if (i == menu->selected)
            OLED_print_arrow(i + line, 0);
        OLED_pos(i + line, 8, 127 - 8);
        OLED_print(menu->children[i]->title);
    }
}

/**
 * @brief Create the main menu for the game
 * @return The root menu with some submenus: "Play Game", "High Scores",
 *         "Settings", "Score"
 */
Menu_t * menu_create_start_menu()
{
    Menu_t* main_menu = menu_create("Main Menu");
    Menu_t* play_menu = menu_create("Play");
	Menu_t* play_status = menu_create("Playing...");
	menu_add(play_menu, play_status);
	Menu_t* play_score = menu_create("Score: 0");
    menu_add(play_menu, play_score);
	menu_add(main_menu, play_menu);
    Menu_t* high_scores_menu = menu_create("High scores");
	for (int i = 0; i < NB_SCORES; i++)
	{
		Menu_t* item = menu_create("- 0");
		menu_add(high_scores_menu, item);
	}
    menu_add(main_menu, high_scores_menu);
    Menu_t* settings_menu = menu_create("Settings");
	Menu_t* speed_option = menu_create("Speed: Medium");
	menu_add(settings_menu, speed_option);
    menu_add(main_menu, settings_menu);
    return main_menu;
}

/**
 * @brief Move the selection from one menu item to another one
 * @param menu The menu where the selection should be moved
 * @param direction Where to search for the next menu item
 * @return Error code
 *  - -1: The given menu item was not selected, therefore the selection
 *        can't move from it
 *  - 0: The change in selection is successful
 */
void menu_move(Menu_t* menu, MenuDirection_t direction)
{
    uint8_t index = menu->selected;
    switch (direction)
    {
    case MENU_UP:
        if (index == 0)
            menu->selected = menu->length - 1;
        else
            menu->selected = index - 1;
        break;
    case MENU_DOWN:
        if (index == (menu->length - 1))
            menu->selected = 0;
        else
            menu->selected = index + 1;
        break;
    }
}

void menu_update_highscores(Menu_t* scores, uint16_t score)
{
	uint16_t current_score = 0;
	uint8_t index = scores->length - 1;
	for (int i = 0; i < scores->length; i++)
	{
		sscanf(scores->children[i]->title, "- %d", &current_score);
		if (current_score < score)
		{
			index = i;
			for (int j = scores->length - 1; j > index; j--)
			{
				char* title = scores->children[j - 1]->title;
				menu_set_title(scores->children[j], title);
			}
			char tmp[10];
			sprintf(tmp, "- %d", score);
			menu_set_title(scores->children[index], tmp);
			break;
		}
	}
}
