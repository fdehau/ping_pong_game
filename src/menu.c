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
    new_item->selected = NULL;
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
 * @brief Add a new submenu to a given menu
 * @param parent An existing menu item that will act as a parent
 * @param child The new submenu
 */
void menu_add(Menu_t* parent, Menu_t* child)
{
    // Prepare the parent to store new child node
    parent->length++;
    parent->children = realloc(parent->children,
                               sizeof(Menu_t*) * parent->length);
    if (!parent->children)
    {
        printf("Realloc in menu_add() failed !");
    }

    // Add the new submenu
    parent->children[parent->length - 1] = child;
    if (!parent->selected)
    {
        parent->selected = child;
    }
    child->parent = parent;
}

/**
 * @brief Util function if you need to replace the title of an existing menu
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
        if (menu->children[i] == menu->selected)
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
    Menu_t* play_menu = menu_create("Play Game");
    menu_add(main_menu, play_menu);
    Menu_t* high_scores_menu = menu_create("High scores");
    menu_add(main_menu, high_scores_menu);
    Menu_t* settings_menu = menu_create("Settings");
    menu_add(main_menu, settings_menu);
    Menu_t* scores_menu = menu_create("Score: 0");
    menu_add(main_menu, scores_menu);
    return main_menu;
}

/**
 * @brief Retrieve the selected menu item
 * @param menu The active menu
 * @return Index of the selected menu among children of the given menu
 */
int menu_get_selected_index(Menu_t* menu)
{
    for (int i = 0; i < menu->length; i++)
    {
        if (menu->children[i] == menu->selected)
            return i;
    }
    return -1;
}

/**
 * @brief Move the selection from one menu item to another one
 * @param menu The menu where the selection should be moved
 * @param direction Where to search for the next menu item
 * @return Error code
 *  - -1: The given menu item was not selected, therefore the selection
 *        can't move from it
 *  - 0: The change in selection is succcessful
 */
int menu_move(Menu_t* menu, MenuDirection_t direction)
{
    if (!menu->selected)
        return -1;
    else
    {
        int index = menu_get_selected_index(menu);
        switch (direction)
        {
        case MENU_UP:
            if (index == 0)
                menu->selected = menu->children[menu->length - 1];
            else
                menu->selected = menu->children[index - 1];
            break;
        case MENU_DOWN:
            if (index == (menu->length - 1))
                menu->selected = menu->children[0];
            else
                menu->selected = menu->children[index + 1];
            break;
        }
        return 0;
    }
}
