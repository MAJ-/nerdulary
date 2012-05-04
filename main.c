#include <curses.h>
#include <stdlib.h>
#include <menu.h>
#include <form.h>

void quit(void);

ITEM **it;
MENU *me;
FIELD **fi;
FORM *fo;

//init function. Initialize curses
void init(void)
{
	//initialize window
	initscr();
	//execute quit-function on exit
	atexit(quit);
	//clear screen
	clear();
	//don't print characters, when typing
	noecho();
	//show cursor
	curs_set(1);
	//turn on cbreak-mode
	cbreak();
	//return-button = 0xA
	nl();
	//activate ncurses-escape-sequences (e.g. KEY_DOWN)
	keypad(stdscr, TRUE);
	//use colors
	start_color();
	//define color-pairs
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLACK, COLOR_WHITE);
	//use first color pair for background
	bkgd(COLOR_PAIR(1));
}

//quit function. Dealocate memory of win and exit.
void quit(void)
{
	int i;

	//remove form
	unpost_form(fo);
	free_form(fo);

	for(i=0; i<=3; i++){
		free_field(fi[i]);
	}

	free(fi);

	//remove menue
	unpost_menu(me);
	free_menu(me);

	for(i=0; i<=3; i++){
		free_item(it[i]);
	}

	free(it);
	endwin();
}

int main(void)
{
	int ch;
	int i;

	//initializing
	init();
	//create 4 fields, the last element have to be NULL
	fi = (FIELD **)calloc(4, sizeof(FIELD *));
	fi[0] = new_field(1, 10, 2, 3, 0, 0);
	fi[1] = new_field(1, 10, 2, 18, 0, 0);
	fi[2] = new_field(1, 15, 2, 33, 0, 0);
	fi[3] = NULL;

	//color fields
	for(i=0; i<3; i++){
		set_field_fore(fi[i], COLOR_PAIR(2));
		set_field_back(fi[i], COLOR_PAIR(2));
  	}

	//bind fields to form
	fo = new_form(fi);

	//color menu
	set_menu_fore(me, COLOR_PAIR(1)|A_REVERSE);
	set_menu_back(me, COLOR_PAIR(1));

	//create 4 items, the last element have to be NULL
	it = (ITEM **)calloc(4, sizeof(ITEM *));
	it[0] = new_item("Create lesson","");
	it[1] = new_item("Learn lesson", "");
	it[2] = new_item("Exit", "");
	it[3] = NULL;

	//bind items to menue
	me = new_menu(it);

	//post menu (after refreshing, it will be showed)
	post_menu(me);

	//refresh window and show posted elements
	refresh();

	//input processing
	while(ch=getch()){
		switch(ch){
			//use arrow keys to switch between items/fields
			case KEY_LEFT:	form_driver(fo, REQ_PREV_FIELD);
					break;
			case KEY_RIGHT:	form_driver(fo, REQ_NEXT_FIELD);
					break;
			case KEY_DOWN:	menu_driver(me, REQ_DOWN_ITEM);
					break;
			case KEY_UP:	menu_driver(me, REQ_UP_ITEM);
					break;
			//if return-button is pressed
			case 0xA:
					//exit on "Exit"
					if(item_index(current_item(me)) == 2)
						exit(0);
					//hide menu and show form on "Learn lesson"
					else if(item_index(current_item(me)) == 0){
						unpost_menu(me);
						post_form(fo);
					}
					break;
			default:	form_driver(fo, ch);
		}

		refresh();
	}

	return(0);
}
