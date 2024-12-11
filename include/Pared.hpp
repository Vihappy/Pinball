#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
class Pared
{
private:
    b2PolygonShape formaLimite;
    b2Body *cuerpoLimite;
    sf::RectangleShape Limite;

public:
    Pared(b2World& mundo,float boxWidth,float boxHeight,float friccion,float x, float y,float angulo)
    {
        // Crear el limite.
        b2BodyDef cuerpoLimitedef;
        cuerpoLimitedef.position.Set(x, y);
        constexpr float DEG2RAD = 3.14159f / 180.0f;
        cuerpoLimitedef.angle = angulo * DEG2RAD;
        cuerpoLimite = mundo.CreateBody(&cuerpoLimitedef);
        // Crear una forma rectangular
        formaLimite.SetAsBox(boxWidth / 2.0f, boxHeight/ 2.0f);
        // Agregar la forma al cuerpo
        b2FixtureDef fixtureLimite;
        fixtureLimite.shape = &formaLimite;
    
        cuerpoLimite->CreateFixture(&fixtureLimite);
        Limite.setSize(sf::Vector2f(boxWidth, boxHeight));
        Limite.setOrigin(Limite.getSize().x / 2.0f, Limite.getSize().y / 2.0f);
        Limite.setRotation(angulo);
        
    }
    ~Pared() {}
    void Dibujar(sf::RenderWindow& window)
    {
        Limite.setFillColor(sf::Color::Blue);
        Limite.setPosition(		
        cuerpoLimite->GetPosition().x, 
        cuerpoLimite->GetPosition().y);
        window.draw(Limite);
    }
};