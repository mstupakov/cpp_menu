#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "menu_c.h"

static Command_t menu_input_get(MenuItem_t* menu) {
  printf("\n Input: ");

  Command_t cmd = getchar();
  while (getchar() != '\n') continue;

  printf("\n");
  return cmd;
}

static void menu_usage_print(void) {
  printf("Usage:\n"
         "  * - Up\n"
         "  ? - Help\n"
         "  q - Exit\n\n"
  );
}

MenuItem_t* menu_create(const char* name) {
  MenuItem_t* menu = malloc(sizeof(MenuItem_t));
  assert(menu);

  menu->name = name;
  menu->head = NULL;

  return menu;
}

MenuItem_t* menu_remove(MenuItem_t* menu) {
  return 0;
}

MenuItem_t* menu_item_add(MenuItem_t* menu, const char* name, CB_t callback) {
  Node_t* node = malloc(sizeof(Node_t));
  assert(node);

  node->name     = name;
  node->next     = NULL;
  node->sub_menu = NULL;
  node->callback = callback;

  Node_t* head = menu->head;
  if (head) {

    Node_t* next = head;
    Node_t* curr;

    do {
      curr = next;
    } while((next = next->next));

    curr->next = node;

  } else {
     menu->head = node;
  }

  return menu;
}

MenuItem_t* menu_menu_add(MenuItem_t* menu, const char* name, CB_t callback) {
  MenuItem_t* sub_menu = menu_create(name);

  Node_t* node = malloc(sizeof(Node_t));
  assert(node);

  node->name     = name;
  node->next     = NULL;
  node->sub_menu = sub_menu;
  node->callback = callback;

  Node_t* head = menu->head;
  if (head) {

    Node_t* next = head;
    Node_t* curr;

    do {
      curr = next;
    } while((next = next->next));

    curr->next = node;

  } else {
    menu->head = node;
  }

  return node->sub_menu;
}

Command_t menu_show(MenuItem_t* menu, bool one_time) {
begin:
  unsigned num = 0, order = 0, item_num = 0;

  do {
    printf("%s:\n", menu->name);

    num = 0;
    Node_t* item = menu->head;
    while (item) {
      printf("  %d. %s\n", num++, item->name);
      item = item->next;
    }

    Command_t command = menu_input_get(0);

    if (command == 'q' || command == 'Q') {
      return CMD_QUIT;
    } else if (command == '*') {
      return CMD_UP;
    } else if (command == '?') {
      menu_usage_print(); goto begin;
    }

    item_num = order = command - '0';
  } while (order >= num);

  Node_t* item = menu->head;
  while (item && item_num--) {
    item = item->next;
  }

  if (item->sub_menu) {
    if (item->callback) {
      item->callback();
    }

    Command_t rc = menu_show(item->sub_menu, one_time);
    if (rc == CMD_UP) goto begin; order = rc;

  } else if (item->callback) {
    item->callback(); if (!one_time) goto begin;
  }

  return order;
}

