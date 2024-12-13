#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
class Rebotador
{
private:
    b2PolygonShape formaLimite;
    b2Body *cuerpoLimite;
    sf::RectangleShape Limite;

public:
    Rebotador(b2World &mundo, float boxWidth, float boxHeight, float friccion, float x, float y, float angulo, float restitucion)
    {
        const float SCALE = 30.0f;
        // Crear el limite.
        b2BodyDef cuerpoLimitedef;
        cuerpoLimitedef.position.Set(x / SCALE, y / SCALE);
        constexpr float DEG2RAD = 3.14159f / 180.0f;
        cuerpoLimitedef.angle = angulo * DEG2RAD;
        cuerpoLimite = mundo.CreateBody(&cuerpoLimitedef);
        cuerpoLimite->GetUserData().pointer = reinterpret_cast<uintptr_t>(new std::string("rebotador"));
        // Crear una forma rectangular
        formaLimite.SetAsBox((boxWidth / SCALE) / 2.0f, (boxHeight / SCALE) / 2.0f);
        // Agregar la forma al cuerpo
        b2FixtureDef fixtureLimite;
        fixtureLimite.shape = &formaLimite;
        fixtureLimite.restitution = restitucion;
        cuerpoLimite->CreateFixture(&fixtureLimite);
        Limite.setSize(sf::Vector2f(boxWidth, boxHeight));
        Limite.setOrigin(Limite.getSize().x / 2.0f, Limite.getSize().y / 2.0f);
        Limite.setRotation(angulo);
    }
    ~Rebotador() {}
    void Dibujar(sf::RenderWindow &window)
    {
        const float SCALE = 30.0f;
        Limite.setFillColor(sf::Color::Blue);
        Limite.setPosition(
            cuerpoLimite->GetPosition().x * SCALE,
            cuerpoLimite->GetPosition().y * SCALE);
        window.draw(Limite);
    }
};