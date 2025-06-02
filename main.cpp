/*
    Conways Game of Life

    This Project will be 100% complete when I have a screen,
    play/stop, next, restart

    Compile: Use Make file
    Run : ./main,

*/

// Imports 
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Button.h"


// Globals 
int SWIDTH = 1400;
int SHEIGHT = 750;

int ROWS = 53;
int COLS = 138;
float SIZE = 10.f;
int HEIGHTOFFSET = 110;
int WIDTHOFFSET = 10;

bool game = false;



// Helper Functions


void upperTitelDraw(sf::RenderWindow& window, sf::Font font) {
    sf::RectangleShape rectangle({ 1400.f, 100.f });
    rectangle.setPosition(0, 0);
    rectangle.setFillColor(sf::Color(33, 52, 72));

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(75);
    text.setString("Conway's Game of Life");
    text.setPosition(260, 0);

    window.draw(rectangle);
    window.draw(text);
}

void drawGrid(sf::RenderWindow& window, std::vector<std::vector<bool>>& grid) {


    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {

            sf::RectangleShape rectangle({ SIZE, SIZE });
            rectangle.setPosition({ WIDTHOFFSET + j * SIZE, HEIGHTOFFSET + i * SIZE });

            grid[i][j] == true ? rectangle.setFillColor(sf::Color(130, 150, 180)) : rectangle.setFillColor(sf::Color(34, 40, 49));

            rectangle.setOutlineThickness(1.0f);
            rectangle.setOutlineColor(sf::Color(67, 72, 80));

            window.draw(rectangle);

        }
    }
}

std::vector<std::vector<bool>> getNextGrid(std::vector<std::vector<bool>> currentGrid) {
    std::vector<std::vector<bool>> next(ROWS, std::vector<bool>(COLS, false));

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int sum = 0;

            // loping through the 3x3 square around self
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0) continue;
                    int ni = (i + di + ROWS) % ROWS;
                    int nj = (j + dj + COLS) % COLS;
                    sum += currentGrid[ni][nj];
                }
            }

            if (currentGrid[i][j]) {
                next[i][j] = (sum == 2 || sum == 3);
            }
            else {
                next[i][j] = (sum == 3);
            }

        }
    }
    return next;

}



// Main Function
int main() {
    sf::RenderWindow window(sf::VideoMode(SWIDTH, SHEIGHT), "Conway's Game of Life", sf::Style::Close);

    sf::Font font;
    if (!font.loadFromFile("Quicksand-Medium.ttf")) {
        std::cerr << "Failed to load font\n";
        return 1;
    }

    // Main Grid layed in matrix 
    std::vector<std::vector<bool>> grid(ROWS, std::vector<bool>(COLS, false));
    std::vector<std::vector<bool>> nextGrid(ROWS, std::vector<bool>(COLS, false));



    // Buttons  
    Button Stop({ 200, 50 }, { 1090, 675 }, "STOP", font);
    Button Start({ 200, 50 }, { 750, 675 }, "START", font);
    Button Next({ 200, 50 }, { 410, 675 }, "NEXT", font);
    Button Restart({ 200, 50 }, { 90, 675 }, "RESTART", font);


    // Main window loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // closes the window with x or escape
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                auto mousePos = sf::Mouse::getPosition(window);
                if (10 < mousePos.x && mousePos.x < 1390 && 110 < mousePos.y && mousePos.y < 640) {
                    int col = (mousePos.x - 10) / SIZE;
                    int row = (mousePos.y - 110) / SIZE;

                    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
                        // just flip the bool 
                        grid[row][col] = !grid[row][col];
                    }
                }
            }

            if (Start.isClicked(event, window)) {
                game = true;
            }

            if (Stop.isClicked(event, window)) {
                game = false;
            }

            if (Next.isClicked(event, window)) {
                grid = getNextGrid(grid);
            }

            if (Restart.isClicked(event, window)) {
                grid = std::vector<std::vector<bool>>(ROWS, std::vector<bool>(COLS, false));
                std::vector<std::vector<bool>> nextGrid(ROWS, std::vector<bool>(COLS, false));
                game = false;
            }

        }
        window.clear(sf::Color(33, 52, 72));
        int sum = 0;
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (grid[i][j]) {
                    sum += 1;
                }
            }
        }

        if (sum == 0) {
            grid = std::vector<std::vector<bool>>(ROWS, std::vector<bool>(COLS, false));
            std::vector<std::vector<bool>> nextGrid(ROWS, std::vector<bool>(COLS, false));
            game = false;
        }



        if (game) {
            grid = getNextGrid(grid);

            sf::sleep(sf::milliseconds(50));

            Stop.render(window);
            Stop.update(window);

        }


        upperTitelDraw(window, font);

        drawGrid(window, grid);
        if (!game) {
            Start.render(window);
            Start.update(window);
        }

        Next.render(window);
        Next.update(window);
        Restart.render(window);
        Restart.update(window);
        window.display();

    }

    return 1;
}