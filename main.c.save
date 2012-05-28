#include <curses.h>
#include <stdlib.h>
#include <menu.h>
#include <form.h>

ITEM **it;
MENU *me;
FIELD  **fi;
FORM   *fo;

//quit function. Dealocate memory of win and exit.
void quit(void)
{
  int i;

  unpost_form(fo);
  free_form(fo);

  unpost_menu(me);
  free_menu(me);

  for(i=0; i<=3; i++)
  {
    free_field(fi[i]);
  }

  for(i=0; i<=3; i++)
  {
    free_item(it[i]);
  }

  free(fi);
  free(it);
  endwin();
}

int main(void)
{
  int ch;
  int i;
  //initialize window
  initscr();
  atexit(quit);
  //clear screen
  clear();
  //don't print characters, when typing
  noecho();
  //show cursor
  curs_set(1);
  //turn on cbreak-mode
  cbreak();
  nl();
  //activate ncurses-escape-sequences (e.g. KEY_DOWN)
  keypad(stdscr, TRUE);
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);
  bkgd(COLOR_PAIR(1));

  fi = (FIELD **)calloc(4, sizeof(FIELD *));
  fi[0] = new_field(1, 10, 2, 3, 0, 0);
  fi[1] = new_field(1, 10, 2, 18, 0, 0);
  fi[2] = new_field(1, 15, 2, 33, 0, 0);
  fi[3] = 0;

  for(i=0; i<3; i++)
  {
    set_field_fore(fi[i], COLOR_PAIR(2));
    set_field_back(fi[i], COLOR_PAIR(2));
  }
 
  fo = new_form(fi);

  set_menu_fore(me, COLOR_PAIR(1)|A_REVERSE);
  set_menu_back(me, COLOR_PAIR(1));

  it = (ITEM **)calloc(4, sizeof(ITEM *));
  it[0] = new_item("Neue Lektion","");
  it[1] = new_item("Lektion lernen", "");
  it[2] = new_item("Beenden", "");
  it[3] = 0;
  me = new_menu(it);
  post_menu(me);  
  refresh();

  while(ch=getch())
  {
    switch(ch)
    {      
      case KEY_LEFT:
        form_driver(fo, REQ_PREV_FIELD);
        break;
      case KEY_RIGHT:
        form_driver(fo, REQ_NEXT_FIELD);
        break;
      case KEY_DOWN:
        menu_driver(me, REQ_DOWN_ITEM);
        break;
      case KEY_UP:
        menu_driver(me, REQ_UP_ITEM);
        break;
      case 0xA://ASCII-Code return-button 
        if(item_index(current_item(me)) == 2)
          exit(0);      
        else if(item_index(current_item(me)) == 0){
          unpost_menu(me);
          post_form(fo);
        }
      default: /* Feldeingabe */ 
        form_driver(fo, ch); 
   }

    refresh();
  }

  return(0);
}
