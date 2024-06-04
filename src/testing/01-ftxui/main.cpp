// main.cpp
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>

int main()
{
  ftxui::Element fDocument =
  ftxui::hbox({ftxui::text("left") | ftxui::border,
              ftxui::text("middle")| ftxui::border | ftxui::flex,
              ftxui::text("right") | ftxui::border});

  auto fScreen = ftxui::Screen::Create(
    ftxui::Dimension::Full(),
    ftxui::Dimension::Fit(fDocument)
  );

  ftxui::Render(fScreen, fDocument);
  fScreen.Print();

  return EXIT_SUCCESS;
}
