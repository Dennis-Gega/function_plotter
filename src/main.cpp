#include "tinyexpr.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

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

void testExpr(std::string s,float width, float height, sf::RenderWindow &window) {
  double x;
  te_variable vars[] = {{"x", &x}};

  int err;

  te_expr *expr = te_compile(s.c_str(), vars, 1, &err);

  if (expr) {
    for (double i = -width; i < width; i += 0.01) {
      x = i;
      const double h1 = te_eval(expr);
      sf::CircleShape shape(1.f);
      shape.setFillColor(sf::Color(100, 250, 50));
      shape.setPosition({width / 2.0f + static_cast<float>(10 * x), height / 2.0f - static_cast<float>(10 * h1)});
      window.draw(shape);
    }
    te_free(expr);
  } else {
    printf("Parse error at %d\n", err);
  }
}

int main()
{
  std::string s;
  std::getline(std::cin, s);
  auto window = sf::RenderWindow(sf::VideoMode({1000u, 1000u}), "function plotter");
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
    testExpr(s, width, height, window);
    window.display();
  }
}
