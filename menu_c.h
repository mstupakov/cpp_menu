#ifndef __MENU_H__
#define __MENU_H__

#include <stdbool.h>

#define CMD_QUIT -1
#define CMD_UP   -2

typedef int Command_t;
typedef void (*CB_t)(void);

typedef struct MenuItem {
  const char*  name;
  struct Node* head;
} MenuItem_t;

typedef struct Node {
  const char*  name;
  MenuItem_t*  sub_menu;
  CB_t         callback;

  struct Node* next;
} Node_t;

MenuItem_t* menu_create(const char* name);
MenuItem_t* menu_remove(MenuItem_t* menu);
MenuItem_t* menu_item_add(MenuItem_t* menu, const char* name, CB_t callback);
MenuItem_t* menu_menu_add(MenuItem_t* menu, const char* name, CB_t callback);

Command_t menu_show(MenuItem_t* menu, bool one_time);

#endif /* __MENU_H__ */
