#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Bumper
{
private:
    b2CircleShape formaSuelo;
    b2Body *cuerpoSuelo;

public:
    Bumper(b2World& mundo,float radio,float friccion,float x, float y)
    {
        // Crear un ostaculo estático
        b2BodyDef cuerpoSueloDef;
        cuerpoSueloDef.position.Set(x, y); // Posición del centro del cuerpo

        // Construir el objeto fisico
        cuerpoSuelo = mundo.CreateBody(&cuerpoSueloDef);

        // Crear una forma circular
        formaSuelo.m_radius = radio;
        // Agregar la forma al cuerpo
        b2FixtureDef fixtureSueloDef;
        fixtureSueloDef.shape = &formaSuelo;
        fixtureSueloDef.friction = friccion;
        fixtureSueloDef.restitution=1;
        cuerpoSuelo->CreateFixture(&fixtureSueloDef);
    }
    ~Bumper() {}
    void Dibujar(sf::RenderWindow& window){
        // Dibujar el obstaculo
        sf::CircleShape suelo(formaSuelo.m_radius);
        suelo.setOrigin(formaSuelo.m_radius, formaSuelo.m_radius);// El origen x,y está en el centro de la forma
        suelo.setFillColor(sf::Color::Green);
        suelo.setPosition(
            cuerpoSuelo->GetPosition().x, 
            cuerpoSuelo->GetPosition().y);

        window.draw(suelo);
    }
};