#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <memory>
using namespace std;
class Ball
{
private:
    b2CircleShape formaBola;
    b2Body *cuerpoBola;
    b2Vec2 posicionInicial; // Para guardar la posición inicial
public:
    Ball(b2World &mundo, float radio, float friccion, float densidad, float x, float y)
    {
        const float SCALE = 30.0f;
        // Crear un cuerpo dinámico
        posicionInicial.Set(x / SCALE, y / SCALE); // Guardamos la posición inicial
        b2BodyDef cuerpoBolaDef;
        cuerpoBolaDef.type = b2_dynamicBody;
        cuerpoBolaDef.position.Set(x / SCALE, y / SCALE);
        cuerpoBola = mundo.CreateBody(&cuerpoBolaDef);
        // Crear una forma circular
        formaBola.m_radius = radio / SCALE;
        cuerpoBola->GetUserData().pointer = reinterpret_cast<uintptr_t>(new std::string("bola"));
        // Agregar la forma al cuerpo
        b2FixtureDef fixtureBolaDef;
        fixtureBolaDef.shape = &formaBola;
        fixtureBolaDef.density = densidad;  // 0.1
        fixtureBolaDef.friction = friccion; // 0.7
        cuerpoBola->CreateFixture(&fixtureBolaDef);
    }
    ~Ball() {}

    // Método para reiniciar la posición de la bola
    void ReiniciarPosicion(b2World &mundo)
    {

        const float SCALE = 30.0f;
        cuerpoBola->SetTransform(posicionInicial, 0); // Reinicia la posición al valor inicial
        cuerpoBola->SetLinearVelocity(b2Vec2(0, 0));  // Reinicia la velocidad a cero
    }
    void Dibujar(sf::RenderWindow &window)
    {
        // cout << "Posicion de la bola: " << cuerpoBola->GetPosition().x << ", " << cuerpoBola->GetPosition().y << endl;
        //  Dibujar la bola
        const float SCALE = 30.0f;
        sf::CircleShape bola(formaBola.m_radius * SCALE);
        bola.setOrigin(formaBola.m_radius * SCALE, formaBola.m_radius * SCALE);
        bola.setFillColor(sf::Color::Red);
        bola.setPosition(
            cuerpoBola->GetPosition().x * SCALE,
            cuerpoBola->GetPosition().y * SCALE);
        window.draw(bola);
    }
    int Posicion(sf::RenderWindow &window)
    {
        //cout << "Posicion de la bola: " << cuerpoBola->GetPosition().x << ", " << cuerpoBola->GetPosition().y << endl;
        return cuerpoBola->GetPosition().y;
    }
};