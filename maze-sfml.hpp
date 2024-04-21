#include <SFML/Graphics.hpp>
#include "maze.hpp"
#include <vector>


class Visualizer {

private:

    const int CELL_SIZE = 30; // Size of each cell

    int ROWS = 50; // Number of rows in the grid
    int COLS = 50; // Number of columns in the grid
    float SPEED = 0.05f; // Speed of navigation value


    enum cellState
    {
        BLOCKED = 0,
        PASSAGE = 1,
        START = 10,
        FINISH = 20,
        VISITED = 30
    };

    // Function to draw the grid
    void drawGrid(sf::RenderWindow& window, const vector<vector<int>>& grid) {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                rect.setPosition(j * CELL_SIZE, i * CELL_SIZE);

                switch (grid[i][j]) {
                    case START:
                        rect.setFillColor(sf::Color::Green);
                        break;
                    case FINISH:
                        rect.setFillColor(sf::Color::Red);
                        break;
                    case BLOCKED:
                        rect.setFillColor(sf::Color::Black);
                        break;
                    case PASSAGE:
                        rect.setFillColor(sf::Color::White);
                        break;
                    case VISITED:
                        rect.setFillColor(sf::Color::Blue);
                        break;
                }

                window.draw(rect);
            }
        }
    }

    // Function to navigate the grid
    void drawNavigation(sf::RenderWindow& window, Maze& maze) {
        sf::Clock clock;
        float elapsedTime = 0;

        for (int i = 1; i < maze.path.size() -1; ++i) {
            maze.arr[maze.path[i].first][maze.path[i].second] = PASSAGE;
        }

        int i = 1;
        while (i < maze.path.size()) { // Loop until reaching the second-to-last element, skipping the start and finish position
            elapsedTime += clock.restart().asSeconds();

            if (elapsedTime >= SPEED) { // Adjust the duration as needed
                window.clear(); // Clear the window before drawing each frame

                // Draw the maze
                drawGrid(window, maze.arr);

                // Draw the current cell in the path
                sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                rect.setPosition(maze.path[i].second * CELL_SIZE, maze.path[i].first * CELL_SIZE);
                rect.setFillColor(sf::Color::Yellow);
                window.draw(rect);
                window.display();

                // Trace the visited cells
                if (maze.arr[maze.path[i].first][maze.path[i].second] != FINISH)
                    maze.arr[maze.path[i].first][maze.path[i].second] = VISITED;

                i++;
                elapsedTime = 0; // Reset the timer
            }
        }
    }

    void visualize() {
        Maze genMaze(ROWS, COLS);
        genMaze.generateMaze();
        genMaze.navigateMaze();

        sf::RenderWindow window(sf::VideoMode(CELL_SIZE * COLS, CELL_SIZE * ROWS), "Maze Generator & Navigator Visualizer");
        sf::Event event;
        window.requestFocus();

        while (window.isOpen()) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) drawNavigation(window, genMaze);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                    genMaze.generateMaze();
                    genMaze.navigateMaze();
                }
            }

            window.clear();

            drawGrid(window, genMaze.arr);
            window.display();
        }
    }

public:

    Visualizer() {
        visualize();
    }

    Visualizer(int r, int c, float s) {

        if (r > 10) {
            ROWS = r;
        }

        if (c > 10) {
            COLS = c;
        }

        if (s >= 1 || s <= 10) {
            SPEED = s * 0.01f;
        }

        visualize();
    }

};