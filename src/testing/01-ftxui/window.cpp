// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.
#include <stdlib.h>  // for EXIT_SUCCESS
#include <memory>    // for allocator, __shared_ptr_access
#include <string>  // for string, operator+, basic_string, to_string, char_traits
#include <vector>  // for vector, __alloc_traits<>::value_type

#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Menu, Renderer, Horizontal, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, Element, operator|, window, flex, vbox
 
using namespace ftxui;

// create window 
Component Window(std::string title, Component component) {
    return Renderer(component, [component, title] {  //
    return window(text(title), component->Render()) | flex;
  });
}

static int nCaughtEvents = 0;
int nOption;
 
int main() {
    int menu_selected[] = {0, 0, 0};
    std::vector<std::vector<std::string>> menu_entries = {
        {
            "Add/Switch Parts",
            "Display AC",
            "Save Build",
            "Load Build",
        },
        {
            "Display Inventory",
            "Display Shop"
        },
        {
            "Exit",
        },
    };
 
    int menu_selected_global = 0;
    auto menu_global = Container::Vertical(
        {
            Window("AC Design", Menu(&menu_entries[0], &menu_selected[0])),
            Window("Parts Shop", Menu(&menu_entries[1], &menu_selected[1])),
            Window("Options", Menu(&menu_entries[2], &menu_selected[2])),
        },
        &menu_selected_global);
 
    auto info = Renderer([&] {
        int g = menu_selected_global;
        std::string value = menu_entries[g][menu_selected[g]];
        return window(text("GARAGE"),  //
                    vbox({
                        text("menu_selected_global = " + std::to_string(g)),
                        text("menu_selected[0]     = " +
                            std::to_string(menu_selected[0])),
                        text("menu_selected[1]     = " +
                            std::to_string(menu_selected[1])),
                        text("menu_selected[2]     = " +
                            std::to_string(menu_selected[2])),
                        text("Value                = " + value),
                        text("Caught Events        = " + std::to_string(nCaughtEvents)),
                        text("Option Chosen        = " + std::to_string(nOption)),
                    })) |
            flex;
    });
    
    menu_global |= CatchEvent([&](Event event) {
        if(event == Event::Character('e'))
        {
            switch(menu_selected_global)
            {
                case 0:
                {
                   nOption = 1;
                   ++nCaughtEvents;
                   return true;
                   break; 
                }
                case 1:
                {
                   nOption = 2;
                    ++nCaughtEvents;
                    return true;
                   break; 
                }
                case 2:
                {
                   nOption = 3;
                    ++nCaughtEvents;
                    return true;
                   break; 
                }
                case 3:
                {
                   nOption = 4;
                    ++nCaughtEvents;
                    return true;
                   break; 
                }
                case 4:
                {
                   nOption = 5;
                    ++nCaughtEvents;
                    return true;
                   break; 
                }
                case 5:
                {
                   nOption = 6;
                    ++nCaughtEvents;
                    return true;
                   break; 
                }
            }
            ++nCaughtEvents;
            return true;
        }
        return false;
    });

    auto global = Container::Horizontal({
        menu_global,
        info,
    });
 
    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(global);
    return EXIT_SUCCESS;
}