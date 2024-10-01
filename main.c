#include <stdio.h>

#include "menu_c.h"

static void cb_1() {
  printf("CB_1\n");
}

static void cb_2() {
  printf("CB_2\n");
}

static void submenu_cb() {
  printf("SubMenu CB\n");
}

int main() {
  MenuItem_t* menu = menu_create("Menu");

  menu_item_add(menu, "Item 1", cb_1);
  menu_item_add(menu, "Item 2", cb_2);

  MenuItem_t* sub = menu_menu_add(menu, "SubMenu", submenu_cb);
  menu_item_add(sub, "Sub - Item 1", cb_1);
  menu_item_add(sub, "Sub - Item 2", cb_2);

  while (CMD_QUIT != menu_show(menu, false)) {}

  return 0;
}
