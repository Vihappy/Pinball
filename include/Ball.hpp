#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
using namespace std;
class Ball
{
private:
    b2CircleShape formaBola;
    b2Body *cuerpoBola;
public:
    Ball(b2World& mundo,float radio,float friccion,float densidad,float x, float y) {
        // Crear un cuerpo dinámico
        b2BodyDef cuerpoBolaDef;
        cuerpoBolaDef.type = b2_dynamicBody;
        cuerpoBolaDef.position.Set(x,y);
        cuerpoBola = mundo.CreateBody(&cuerpoBolaDef);

        // Crear una forma circular
        formaBola.m_radius = radio;

        // Agregar la forma al cuerpo
        b2FixtureDef fixtureBolaDef;
        fixtureBolaDef.shape = &formaBola;
        fixtureBolaDef.density = densidad;//0.1
        fixtureBolaDef.friction = friccion;//0.7
        cuerpoBola->CreateFixture(&fixtureBolaDef);
    }
    ~Ball() {}
    void Dibujar(sf::RenderWindow &window)
    {
        //cout << "Posicion de la bola: " << cuerpoBola->GetPosition().x << ", " << cuerpoBola->GetPosition().y << endl;
        // Dibujar la bola
        sf::CircleShape bola(formaBola.m_radius);
        bola.setOrigin(formaBola.m_radius, formaBola.m_radius);
        bola.setFillColor(sf::Color::Red);
        bola.setPosition(
            cuerpoBola->GetPosition().x, 
            cuerpoBola->GetPosition().y);
        window.draw(bola);
    }
        int Posicion(sf::RenderWindow &window)
    {
        cout << "Posicion de la bola: " << cuerpoBola->GetPosition().x << ", " << cuerpoBola->GetPosition().y << endl;
        return cuerpoBola->GetPosition().y;
    }
};