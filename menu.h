/*
The MIT License

Copyright (c) 2017 Maksym Stupakov 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef __MENU_ITEM__
#define __MENU_ITEM__

#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <list>

class MenuItem {
  std::string m_menu_name;

  using Command = int;
  using Function = std::function<void()>;

  struct Node {
    std::string m_name;
    std::unique_ptr<MenuItem> m_submenu;
    Function m_callback;
  };

  std::list<std::unique_ptr<Node>> m_head;

  public:
    enum {
      QUIT = -1,
      UP   = -2,
    };

    MenuItem(const std::string &menu)
    : m_menu_name(menu) {}

    MenuItem& AddItem(const std::string &item, Function cb = []{}) {
      m_head.push_back(std::make_unique<Node>(Node{item, nullptr, cb}));
      return *this;
    }

    MenuItem& AddSubMenu(const std::string &menu, Function cb = []{}) {
      m_head.push_back(std::make_unique<Node>(
            Node{menu, std::make_unique<MenuItem>(menu), cb}));
      return *m_head.back()->m_submenu;
    }

    Command Show(bool one_time = false) {
begin:
      unsigned num = 0, order = 0;

      do {
        std::cout << m_menu_name << ":\n";

        num = 0;
        for (auto &&e : m_head) {
          std::cout << "  " << num++ << ". " << e->m_name << '\n';
        }

        Command cmd = GetInput();

        if (cmd == 'q' || cmd == 'Q') {
          return QUIT;
        } else if (cmd == '*') {
          return UP;
        } else if (cmd == '?') {
          Usage(); goto begin;
        }

        order = cmd - '0';
      } while (order >= num);

      auto it = std::begin(m_head);
      std::advance(it, order);

      auto &node = *it;
      if (node->m_submenu) {
        if (node->m_callback) {
          node->m_callback();
        }

        Command rc = node->m_submenu->Show(one_time);
        if (rc == UP) goto begin; order = rc;

      } else if (node->m_callback) {
        node->m_callback(); if (!one_time) goto begin;
      }

      return order;
    }

    void Usage() {
      std::cout << "Usage:\n";
      std::cout << "  * - Up\n";
      std::cout << "  ? - Help\n";
      std::cout << "  q - Exit\n\n";
    }

  private:
    Command GetInput() {
      char cmd = 0;
      std::cout << "\n Input: ";
      std::cin >> cmd;
      std::cout << '\n';
      return cmd;
    }
};

#endif /* __MENU_ITEM__ */
