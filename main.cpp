#include "menu.h"

#include <iostream>
#include <string>

int main() {
  MenuItem menu("Menu");
           menu.AddItem("Item 1")
               .AddItem("Item 2");

           menu.AddSubMenu("SubMenu 1")
               .AddItem("S1 - Item 1")
               .AddItem("S1 - Item 2")
               .AddSubMenu("SS1 - SubMenu")
                 .AddItem("SS1 - Item 1")
                 .AddItem("SS1 - Item 2");

           menu.AddSubMenu("SubMenu 2", [] { std::cout << __PRETTY_FUNCTION__ << '\n'; } )
               .AddItem("S2 - Item 1",  [] { std::cout << __PRETTY_FUNCTION__ << '\n'; } )
               .AddItem("S2 - Item 2",  [] { std::cout << __PRETTY_FUNCTION__ << '\n'; } );

           menu.AddItem("Item 3")
               .AddItem("Item 4");


           while (MenuItem::QUIT != menu.Show(false)) {}

  return 0;
}
