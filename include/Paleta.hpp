#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

class Paleta {
private:
    b2Body* cuerpoPaleta;
    sf::RectangleShape graficoPaleta;
    b2RevoluteJoint* joint;

public:
    Paleta(b2World& mundo, float ancho, float alto, float friccion, float x, float y, float angulo) {
        const float SCALE = 30.0f;

        // Crear el cuerpo de la paleta
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody; // La paleta debe ser dinámica para que se mueva
        bodyDef.position.Set(x/SCALE, y/SCALE);
        bodyDef.angle = angulo * b2_pi / 180.0f;
        cuerpoPaleta = mundo.CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox((ancho/SCALE)/2, (alto/SCALE)/2);
        std::cout<<"Algo"<<(ancho/2)<<std::endl;


        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 0.5f;
        fixtureDef.friction = friccion;
        cuerpoPaleta->CreateFixture(&fixtureDef);

        // Configurar el gráfico
        graficoPaleta.setSize(sf::Vector2f(ancho, alto));
        graficoPaleta.setOrigin((ancho) / 2.0f, (alto) / 2.0f);
        graficoPaleta.setRotation(angulo);

        // Crear un cuerpo fijo como punto de pivote
        b2BodyDef pivoteDef;
        pivoteDef.type = b2_staticBody;
        pivoteDef.position.Set(x/SCALE, y/SCALE);
        b2Body* cuerpoPivote = mundo.CreateBody(&pivoteDef);

        // Crear el RevoluteJoint para permitir la rotación
        b2RevoluteJointDef jointDef;
        jointDef.Initialize(cuerpoPivote, cuerpoPaleta, cuerpoPivote->GetWorldCenter());
        jointDef.enableLimit = true; // Activar límites de rotación
        jointDef.lowerAngle = -30.0f * b2_pi / 180.0f; // Límite inferior en radianes
        jointDef.upperAngle = 30.0f * b2_pi / 180.0f;  // Límite superior en radianes
        jointDef.enableMotor = true; // Activar motor
        jointDef.maxMotorTorque = 1000.0f; // Torque máximo
        joint = static_cast<b2RevoluteJoint*>(mundo.CreateJoint(&jointDef));
    }

    void Presionar() {
        // Activar el motor para mover la paleta hacia arriba
        joint->SetMotorSpeed(20.0f); // Velocidad angular positiva
    }

    void Soltar() {
        // Mover la paleta hacia abajo al soltar
        joint->SetMotorSpeed(-20.0f); // Velocidad angular negativa
    }

    void Dibujar(sf::RenderWindow& window) {
        const float SCALE = 30.0f;
        std::cout<<"Algo"<<joint->GetJointAngle() * 180.0f / b2_pi<<std::endl;
        graficoPaleta.setFillColor(sf::Color::Blue);
        graficoPaleta.setPosition(
            cuerpoPaleta->GetPosition().x*SCALE,
            cuerpoPaleta->GetPosition().y*SCALE
        );
        graficoPaleta.setRotation(joint->GetJointAngle() * 180.0f / b2_pi);
        window.draw(graficoPaleta);
    }

    ~Paleta() {}
};