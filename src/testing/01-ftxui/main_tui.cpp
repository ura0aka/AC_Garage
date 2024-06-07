// Copyright 2021 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSED file.
#include <cmath>                   // for sin, cos
#include <ftxui/dom/elements.hpp>  // for canvas, Element, separator, hbox, operator|, border
#include <ftxui/screen/screen.hpp>  // for Pixel
#include <memory>   // for allocator, shared_ptr, __shared_ptr_access
#include <string>   // for string, basic_string
#include <utility>  // for move
#include <vector>   // for vector, __alloc_traits<>::value_type
 
#include "ftxui/component/component.hpp"  // for Renderer, CatchEvent, Horizontal, Menu, Tab
#include "ftxui/component/component_base.hpp"      // for ComponentBase
#include "ftxui/component/event.hpp"               // for Event
#include "ftxui/component/mouse.hpp"               // for Mouse
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive
#include "ftxui/dom/canvas.hpp"                    // for Canvas
#include "ftxui/screen/color.hpp"  // for Color, Color::Red, Color::Blue, Color::Green, ftxui
 
using namespace ftxui;



int main() {
 
  int mouse_x = 0;
  int mouse_y = 0;
 
  // -- display text in canvas box --
  std::string sText = "Test !@#$&@#*()!";
  auto render_display_ac = Renderer([&] {
    auto c = Canvas(100,100);
    c.DrawText(0, 0, "Display AC");
    c.DrawText(0, 4, sText);
    return canvas(std::move(c));
  });
 
  auto render_add_switch_parts = Renderer([&] {
    auto c = Canvas(100,100);
    c.DrawText(0, 0, "Add or switch parts");
    return canvas(std::move(c));
  });

  auto render_save_build = Renderer([&] {
    auto c = Canvas(100,100);
    c.DrawText(0, 0, "Save build");
    return canvas(std::move(c));
  });

  auto render_load_build = Renderer([&] {
    auto c = Canvas(100,100);
    c.DrawText(0, 0, "Load build");
    return canvas(std::move(c));
  });
 
  auto render_display_inventory = Renderer([&] {
    auto c = Canvas(100,100);
    c.DrawText(0, 0, "Display inventory");
    return canvas(std::move(c));
  });

  auto render_exit = Renderer([&] {
    auto c = Canvas(100,100);
    c.DrawText(0, 0, "Exit");
    return canvas(std::move(c));
  });


  int selected_tab = 0;
  auto tab = Container::Tab(
      { 
          render_display_ac,
          render_add_switch_parts,
          render_save_build,
          render_load_build,
          render_display_inventory,
          render_exit,
      },
      &selected_tab);
 
  
  // This capture the last mouse position.
  auto tab_with_mouse = CatchEvent(tab, [&](Event e) {
    if (e.is_mouse()) {
      mouse_x = (e.mouse().x - 1) * 2;
      mouse_y = (e.mouse().y - 1) * 4;
    }
    return false;
  });
 

  std::vector<std::string> tab_titles = {
      "Display AC",
      "Add/Switch Parts",
      "Save Build",
      "Load Build",
      "Display Inventory",
      "Exit" 
  };
  auto tab_toggle = Menu(&tab_titles, &selected_tab);

 
  auto component = Container::Horizontal({
      tab_with_mouse,
      tab_toggle,
  });
 

  // == MAIN RENDERER ==
  // Add some separator to decorate the whole component:
  auto component_renderer = Renderer(component, [&] {
    return vbox({
      text("GARAGE") | bold | hcenter,
        hbox({
               tab_with_mouse->Render(),
               separator(),
               tab_toggle->Render(),
           }) |
           border,
    });
  });
 
  auto screen = ScreenInteractive::FitComponent();
  screen.Loop(component_renderer);
 
  return 0;
}