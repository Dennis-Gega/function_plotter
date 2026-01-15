#include "tinyexpr.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#define WIDTH 500
#define HEIGHT 500

te_expr *expr;
double x;
te_variable vars[] = {{"x", &x}};
int err;

void drawGrid(sf::RenderWindow& window) {
    std::array x_axis =
    {
      sf::Vertex{sf::Vector2f(0, HEIGHT / 2.0f)},
      sf::Vertex{sf::Vector2f(WIDTH, HEIGHT / 2.0f)},
    };

    std::array y_axis =
    {
      sf::Vertex{sf::Vector2f(WIDTH / 2.0f, 0)},
      sf::Vertex{sf::Vector2f(WIDTH / 2.0f, WIDTH)},
    };

    window.draw(x_axis.data(), x_axis.size(), sf::PrimitiveType::Lines);
    window.draw(y_axis.data(), y_axis.size(), sf::PrimitiveType::Lines);
}

void testExpr(sf::RenderWindow &window) {


  if (expr != nullptr) {
    for (double i = -WIDTH; i < WIDTH; i += 0.01) {
      x = i;
      const double h1 = te_eval(expr);
      sf::CircleShape shape(1.f);
      shape.setFillColor(sf::Color(100, 250, 50));
      shape.setPosition({WIDTH / 2.0f + static_cast<float>(10 * x), HEIGHT / 2.0f - static_cast<float>(10 * h1)});
      window.draw(shape);
    }
  } else {
    printf("Parse error at %d\n", err);
  }
}

int main()
{
  // process user input
  std::string s;
  std::getline(std::cin, s);

  expr = te_compile(s.c_str(), vars, 1, &err);


  auto window = sf::RenderWindow(sf::VideoMode({WIDTH, HEIGHT}), "function plotter");
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
    drawGrid(window);
    testExpr(window);
    window.display();

  }
  te_free(expr);
}
