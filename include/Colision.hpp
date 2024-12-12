// Colision.hpp
#pragma once
#include <Box2D/Box2D.h>
#include <iostream>
#include <string> // Asegúrate de incluir <string>
#include <memory>
#include <SFML/Audio.hpp>

class Colision : public b2ContactListener
{
    private:
    sf::Music music;

public:
    // Este método se llama cuando dos cuerpos comienzan a colisionar
void BeginContact(b2Contact* contact) override
{
    if (!music.openFromFile("./assets/music/Hit.ogg"))
    {
        // Error al cargar el archivo de música
       // return -1;
    }
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    // Verificamos que los UserData no sean nulos
    if (bodyA->GetUserData().pointer != 0 && bodyB->GetUserData().pointer != 0)
    {
        auto bodyAName = reinterpret_cast<std::string*>(bodyA->GetUserData().pointer);
        auto bodyBName = reinterpret_cast<std::string*>(bodyB->GetUserData().pointer);

        // Verificamos los tipos de los objetos en contacto
        if (*bodyAName == "bola" && *bodyBName == "bumper")
        {
            std::cout << "¡Colisión entre la bola y el bumper!" << std::endl;
        }
        else if (*bodyAName == "bumper" && *bodyBName == "bola")
        {
            std::cout << "¡Colisión entre el bumper y la bola!" << std::endl;
        }
        music.play();
    }
}

    // Este método se llama cuando dos cuerpos dejan de colisionar
    void EndContact(b2Contact* contact) override {}

    // Métodos opcionales para realizar alguna acción antes o después de la resolución de la colisión
    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override {}
    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override {}
};