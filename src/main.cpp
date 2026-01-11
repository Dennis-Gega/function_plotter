#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
  auto window = sf::RenderWindow(sf::VideoMode({500u, 500u}), "function plotter");
  window.setFramerateLimit(144);

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

    std::array x_axis =
    {
      sf::Vertex{sf::Vector2f(250.f, 0.f)},
      sf::Vertex{sf::Vector2f(250.f, 500.f)}
    };

    window.draw(x_axis.data(), x_axis.size(), sf::PrimitiveType::Lines);
    
    std::array y_axis =
    {
      sf::Vertex{sf::Vector2f(0.f, 250.f)},
      sf::Vertex{sf::Vector2f(500.f, 250.f)}
    };

    window.draw(y_axis.data(), y_axis.size(), sf::PrimitiveType::Lines);

    window.display();
  }
}
