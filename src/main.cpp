#include "tinyexpr.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void drawGrid(float width, float height, sf::RenderWindow& window) {
    std::array x_axis =
    {
      sf::Vertex{sf::Vector2f(0, height / 2.0f)},
      sf::Vertex{sf::Vector2f(width, height / 2.0f)},
    };

    std::array y_axis =
    {
      sf::Vertex{sf::Vector2f(width / 2.0f, 0)},
      sf::Vertex{sf::Vector2f(width / 2.0f, width)},
    };

    window.draw(x_axis.data(), x_axis.size(), sf::PrimitiveType::Lines);
    window.draw(y_axis.data(), y_axis.size(), sf::PrimitiveType::Lines);
}

int main()
{

  auto window = sf::RenderWindow(sf::VideoMode({500u, 500u}), "function plotter");
  window.setFramerateLimit(144);

  sf::Vector2u size = window.getSize();
  auto [width, height] = size;

  while (window.isOpen())
  {
    while (const std::optional event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>())
      {
        window.close();
      }

    }

    window.clear();
    drawGrid(width, height, window);
    window.display();
  }
}
