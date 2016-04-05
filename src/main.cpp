#include <SFML/Graphics.hpp>
#include "character.h"

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Project Zero");

  Character character;

  while (window.isOpen()) {
    // Input handling
    sf::Event event;
    if (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    character.handleInputs();

    // Drawing
    window.clear();

    character.draw(window);

    window.display();
  }

  return 0;
}
