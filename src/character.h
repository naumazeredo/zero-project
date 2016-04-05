#ifndef ZERO_CHARACTER_H
#define ZERO_CHARACTER_H

#include <SFML/Graphics.hpp>

struct Character {
  sf::Vector2f position;
  sf::Sprite sprite;
  sf::Texture texture; // TODO(naum): Refactor

  Character() {
    // FIXME(naum)
    texture.loadFromFile("assets/blank.png");
    sprite.setTexture(texture);
  }

  void draw(sf::RenderWindow& window) {
    sprite.setPosition(position);
    window.draw(sprite);
  }

  void handleInputs() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      position.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      position.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      position.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      position.y += 1;
  }
};

#endif
