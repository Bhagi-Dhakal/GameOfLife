#include "Button.h"

// Generated! 
Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, const sf::Font& font)
    : idleColor(sf::Color(84, 89, 172)), hoverColor(sf::Color(100, 141, 179)), pressedColor(sf::Color(178, 216, 206)) {

    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(idleColor);

    label.setFont(font);
    label.setString(text);
    label.setCharacterSize(30);
    label.setFillColor(sf::Color::White);

    sf::FloatRect textRect = label.getLocalBounds();
    label.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    label.setPosition(position + size / 2.0f);
}

void Button::setText(const std::string& text) {
    label.setString(text);
    sf::FloatRect textRect = label.getLocalBounds();
    label.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
}

void Button::setPosition(const sf::Vector2f& position) {
    shape.setPosition(position);
    label.setPosition(position + shape.getSize() / 2.0f);
}

void Button::setColors(const sf::Color& idle, const sf::Color& hover, const sf::Color& pressed) {
    idleColor = idle;
    hoverColor = hover;
    pressedColor = pressed;
}

bool Button::isMouseOver(const sf::RenderWindow& window) const {
    auto mousePos = sf::Mouse::getPosition(window);
    return shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void Button::update(const sf::RenderWindow& window) {
    if (isMouseOver(window)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            shape.setFillColor(pressedColor);
        }
        else {
            shape.setFillColor(hoverColor);
        }
    }
    else {
        shape.setFillColor(idleColor);
    }
}

bool Button::isClicked(const sf::Event& event, const sf::RenderWindow& window) const {
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        if (isMouseOver(window)) {
            return true;
        }
    }
    return false;
}

void Button::render(sf::RenderTarget& target) {
    target.draw(shape);
    target.draw(label);
}
