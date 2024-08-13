#include <iostream>
#include <memory>
#include <sstream>
#include "SFML/Graphics.hpp"
#include "Vec2.h"
#include "EntityManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Steering");
    window.setFramerateLimit(60);

    sf::CircleShape mark;
    mark.setPointCount(20);
    mark.setFillColor(sf::Color(179, 65, 159));
    mark.setRadius(5);

    Vec2 markPos(window.getSize().x / 2, window.getSize().y / 2);
    float maxSpeed = 10.0f;
    float steeringFactor = 0.1f;
    float stopDistance = 5.0f;

    EntityManager entityManager;
    auto e = entityManager.addEntity("shapeToMove");
    e->cTransform = std::make_shared<CTransform>(Vec2(window.getSize().x / 2, window.getSize().y / 2), Vec2(0, 0), 0.0);
    e->cShape = std::make_shared<CShape>(20, 4, sf::Color(133, 127, 241), sf::Color(147, 112, 219), 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                markPos.x = event.mouseButton.x;
                markPos.y = event.mouseButton.y;
                mark.setFillColor(sf::Color(179, 65, 159));
            }
        }

        Vec2 toTarget = markPos - e->cTransform->pos;
        float distance = toTarget.length();

        if (distance > stopDistance)
        {
            Vec2 desiredVelocity (toTarget.normalize().x * maxSpeed, toTarget.normalize().y * maxSpeed);

            Vec2 steering ((desiredVelocity - e->cTransform->velocity).x * steeringFactor, (desiredVelocity - e->cTransform->velocity).y * steeringFactor);

            e->cTransform->velocity += steering;
            if (e->cTransform->velocity.length() > maxSpeed)
            {
                e->cTransform->velocity = Vec2(e->cTransform->velocity.normalize().x * maxSpeed, e->cTransform->velocity.normalize().y * maxSpeed);
            }

            e->cTransform->pos += e->cTransform->velocity ;
        }
        else
        {
            e->cTransform->velocity = Vec2(0, 0);
            mark.setFillColor(sf::Color(133, 127, 241));
        }

        window.clear(sf::Color(218, 155, 218));
        mark.setPosition(markPos.x, markPos.y);
        e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
        window.draw(e->cShape->circle);
        window.draw(mark);
        window.display();
    }

    return 0;
}
