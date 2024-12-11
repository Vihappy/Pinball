#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

class Paleta {
private:
    b2Body* cuerpoPaleta;
    sf::RectangleShape graficoPaleta;
    b2RevoluteJoint* joint;
    float angulo = 0;

public:
    Paleta(b2World& mundo, float ancho, float alto, float friccion, float x, float y, float angulo) {
        // Crear el cuerpo de la paleta
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody; // La paleta debe ser dinámica para que se mueva
        bodyDef.position.Set(x, y);
        bodyDef.angle = angulo * b2_pi / 180.0f;
        cuerpoPaleta = mundo.CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(ancho / 2.0f, alto / 2.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = friccion;
        cuerpoPaleta->CreateFixture(&fixtureDef);

        // Configurar el gráfico
        graficoPaleta.setSize(sf::Vector2f(ancho, alto));
        graficoPaleta.setOrigin(ancho / 2.0f, alto / 2.0f);
        graficoPaleta.setRotation(angulo);
        this->angulo = angulo;

        // Crear un cuerpo fijo como punto de pivote
        b2BodyDef pivoteDef;
        pivoteDef.type = b2_staticBody;
        pivoteDef.position.Set(x, y);
        b2Body* cuerpoPivote = mundo.CreateBody(&pivoteDef);

        // Crear el RevoluteJoint para permitir la rotación
        b2RevoluteJointDef jointDef;
        jointDef.Initialize(cuerpoPivote, cuerpoPaleta, cuerpoPivote->GetWorldCenter());
        //jointDef.enableLimit = true; // Activar límites de rotación
        //jointDef.lowerAngle = -30.0f * b2_pi / 180.0f; // Límite inferior en radianes
        //jointDef.upperAngle = 30.0f * b2_pi / 180.0f;  // Límite superior en radianes
        jointDef.enableMotor = true; // Activar motor
       // jointDef.maxMotorTorque = 100.0f; // Torque máximo
        joint = static_cast<b2RevoluteJoint*>(mundo.CreateJoint(&jointDef));
    }

    void Presionar() {
        // Activar el motor para mover la paleta hacia arriba
        joint->SetMotorSpeed(50.0f); // Velocidad angular positiva
    }

    void Soltar() {
        // Mover la paleta hacia abajo al soltar
        joint->SetMotorSpeed(-50.0f); // Velocidad angular negativa
    }

    void Dibujar(sf::RenderWindow& window) {
        graficoPaleta.setFillColor(sf::Color::Blue);
        graficoPaleta.setPosition(
            cuerpoPaleta->GetPosition().x,
            cuerpoPaleta->GetPosition().y
        );
        // std::cout<<"Algo"<<joint->GetJointAngle()<<std::endl;

        this->angulo += 1;
        // graficoPaleta.setRotation(joint->GetJointAngle() * 180.0f / b2_pi);
        graficoPaleta.setRotation(angulo);
        window.draw(graficoPaleta);
    }

    ~Paleta() {}
};
