#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

#define Colour Color

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    // Shapes
    sf::CircleShape krog(15);
    krog.setPosition(600, 300);
    krog.setFillColor(sf::Color::White);

    sf::RectangleShape leviPad({ 30, 100 });
    leviPad.setPosition(10, 360);

    sf::RectangleShape desniPad({ 30, 100 });
    desniPad.setPosition(1240, 360);

    // Text
    sf::Text score;
    sf::Font font;
    font.loadFromFile("C:/Users/nocti/source/repos/igrca/x64/Release/Roboto-Regular.ttf");
    score.setFont(font);
    score.setPosition(630, 50);

    float leviy = 360;
    float speedy = 5;
    float speedx = 5;
    int scoreLevi = 0, scoreDesni = 0;

    bool moveUp = false, moveDown = false;

    //window.setFramerateLimit(145);
    window.setVerticalSyncEnabled(1);

    bool pause = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::LostFocus)
                pause = true;

            if (event.type == sf::Event::GainedFocus)
                pause = false;


        }

        if (pause) {
            window.clear();
            score.setString("PAUSE");
            window.draw(score);
            window.display();


            continue;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (leviy >= 0) {
                leviy -= 5;
                leviPad.setPosition(10, leviy);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (leviy < 620) {
                leviy += 5;
                leviPad.setPosition(10, leviy);
            }
        }



        if (krog.getGlobalBounds().intersects(leviPad.getGlobalBounds()))
            speedx *= -1;

        if (krog.getGlobalBounds().intersects(desniPad.getGlobalBounds()))
            speedx *= -1;

        if (krog.getPosition().y >= 705 || krog.getPosition().y <= 0)
            speedy *= -1;

        if (krog.getPosition().x >= 1265) {
            krog.setPosition(600, 300);
            scoreLevi++;
        }

        if (krog.getPosition().x <= 0) {
            krog.setPosition(600, 300);
            scoreDesni++;
        }

        // OpenAI
        if (krog.getPosition().y > desniPad.getPosition().y)
            desniPad.setPosition(desniPad.getPosition().x, desniPad.getPosition().y + 1);

        if(krog.getPosition().y < desniPad.getPosition().y)
            desniPad.setPosition(desniPad.getPosition().x, desniPad.getPosition().y - 1);

        krog.setPosition(krog.getPosition().x + speedx, krog.getPosition().y + speedy);

        score.setString(std::to_string(scoreLevi) + ':' + std::to_string(scoreDesni));


        window.clear(sf::Colour(25, 25, 25, 0));
        window.draw(krog);
        window.draw(leviPad);
        window.draw(desniPad);
        window.draw(score);
        window.display();
    }
}
