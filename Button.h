#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

// Not 
class Button {
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, const sf::Font& font);

    void setText(const std::string& text);
    void setPosition(const sf::Vector2f& position);
    void setColors(const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& pressedColor);

    void update(const sf::RenderWindow& window);
    void render(sf::RenderTarget& target);

    bool isClicked(const sf::Event& event, const sf::RenderWindow& window) const;

private:
    sf::RectangleShape shape;
    sf::Text label;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color pressedColor;

    mutable bool pressed = false;

    bool isMouseOver(const sf::RenderWindow& window) const;
};

#endif // BUTTON_H
