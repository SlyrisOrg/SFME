#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFME/timer/timestep.hpp>

void update()
{
    static unsigned int frames = 0;
    std::cout << "update -> " << frames++ << std::endl;
}

void render()
{
    static unsigned int frames = 0;
    std::cout << "render -> " << frames++ << std::endl;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sfme::timer::TimeStep timestep;
    timestep.start();
    bool repaint = false;
    while (true) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        timestep.startFrame();
        repaint = false;
        while (timestep.isUpdateRequired()) {
            repaint = true;
            timestep.performUpdate();
            update();
        }
        [[maybe_unused]] float alpha = timestep.getInterpolation();
        if (repaint)
            render();
    }
}
