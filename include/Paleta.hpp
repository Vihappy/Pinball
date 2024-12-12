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
        //Trabajo con 30 pixeles por metro.
        // Transformar coordenadas iniciales de píxeles a metros
        float xFisico = x / SCALE;
        float yFisico = y / SCALE;

        // Crear cuerpo físico
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(xFisico, yFisico);
        bodyDef.angle = angulo * b2_pi / 180.0f;
        cuerpoPaleta = mundo.CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox((ancho / SCALE)/2 , (alto / SCALE)/2);//Cambie el /2

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 0.5f;
        fixtureDef.friction = friccion;
        cuerpoPaleta->CreateFixture(&fixtureDef);

        // Configurar gráfico
        graficoPaleta.setSize(sf::Vector2f(ancho, alto));
        graficoPaleta.setOrigin(ancho / 2.0f, alto / 2.0f); // Centrar el gráfico
        graficoPaleta.setPosition(x, y); // Posición inicial en píxeles
        graficoPaleta.setRotation(angulo);

        // Crear pivote estático
        b2BodyDef pivoteDef;
        pivoteDef.type = b2_staticBody;
        pivoteDef.position.Set(xFisico, yFisico);
        b2Body* cuerpoPivote = mundo.CreateBody(&pivoteDef);

        // Configurar RevoluteJoint
        b2RevoluteJointDef jointDef;
        jointDef.Initialize(cuerpoPivote, cuerpoPaleta, cuerpoPivote->GetWorldCenter());
        jointDef.enableLimit = true;
        jointDef.lowerAngle = -0.0f * b2_pi / 180.0f;
        jointDef.upperAngle = 60.0f * b2_pi / 180.0f;
        jointDef.enableMotor = true;
        jointDef.maxMotorTorque = 1000.0f;
        joint = static_cast<b2RevoluteJoint*>(mundo.CreateJoint(&jointDef));
    }

    void Presionar() {
        joint->SetMotorSpeed(20.0f); // Rotar hacia arriba
    }

    void Soltar() {
        joint->SetMotorSpeed(-20.0f); // Rotar hacia abajo
    }

    void Dibujar(sf::RenderWindow& window) {
        const float SCALE = 30.0f;

        // Obtener posición física y convertir a gráfica
        float posXGrafico = cuerpoPaleta->GetPosition().x * SCALE;
        float posYGrafico = cuerpoPaleta->GetPosition().y * SCALE;

        // Actualizar gráfico
        graficoPaleta.setPosition(posXGrafico, posYGrafico);
        graficoPaleta.setRotation(cuerpoPaleta->GetAngle() * 180.0f / b2_pi);

        // Dibujar gráfico
        window.draw(graficoPaleta);

        // Depuración
        std::cout << "Posición física: (" << cuerpoPaleta->GetPosition().x << ", "
                  << cuerpoPaleta->GetPosition().y << ") metros\n";
        std::cout << "Posición gráfica: (" << posXGrafico << ", "
                  << posYGrafico << ") píxeles\n";
       // std::cout << "Angulo: (" << cuerpoPaleta->GetAngle() * 180.0f / b2_pi\n";
    }

    ~Paleta() {}
};