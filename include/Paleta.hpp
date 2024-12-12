#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

class Paleta {
private:
    b2Body* cuerpoPaleta;
    sf::RectangleShape graficoPaleta;
    b2RevoluteJoint* joint;
    float pivoteX;
    float pivoteY;

public:
    Paleta(b2World& mundo, float ancho, float alto, float friccion, float x, float y, float angulo,float anguloInferior,float anguloSuperior,bool sentido) {
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
        if(sentido==true)
        {
            pivoteX = xFisico - (ancho / SCALE) / 2 * cos(angulo * b2_pi / 180.0f) + (alto / SCALE) / 2 * sin(angulo * b2_pi / 180.0f);
            pivoteY = yFisico - (ancho / SCALE) / 2 * sin(angulo * b2_pi / 180.0f) - (alto / SCALE) / 2 * cos(angulo * b2_pi / 180.0f);
        }
        else
        {
            pivoteX = xFisico + (ancho / SCALE) / 2 * cos(angulo * b2_pi / 180.0f) - (alto / SCALE) / 2 * sin(angulo * b2_pi / 180.0f);
            pivoteY = yFisico + (ancho / SCALE) / 2 * sin(angulo * b2_pi / 180.0f) + (alto / SCALE) / 2 * cos(angulo * b2_pi / 180.0f);            
        }


        // Crear cuerpo estático (pivote)
        b2BodyDef pivoteDef;
        pivoteDef.type = b2_staticBody;
        pivoteDef.position.Set(pivoteX, pivoteY);
        b2Body* cuerpoPivote = mundo.CreateBody(&pivoteDef);

        // Configurar RevoluteJoint
        b2RevoluteJointDef jointDef;
        jointDef.Initialize(cuerpoPivote, cuerpoPaleta, b2Vec2(pivoteX, pivoteY));
        jointDef.enableLimit = true;
        jointDef.lowerAngle = anguloInferior * b2_pi / 180.0f;
        jointDef.upperAngle = anguloSuperior * b2_pi / 180.0f;
        jointDef.enableMotor = true;
        jointDef.maxMotorTorque = 1000.0f;
        joint = static_cast<b2RevoluteJoint*>(mundo.CreateJoint(&jointDef));
    }

    void PresionarDerecho() {
        joint->SetMotorSpeed(20.0f); // Rotar hacia arriba
    }

    void SoltarDerecho() {
        joint->SetMotorSpeed(-20.0f); // Rotar hacia abajo
    }
        void PresionarIzquierdo() {
        joint->SetMotorSpeed(-20.0f); // Rotar hacia arriba
    }

    void SoltarIzquierdo() {
        joint->SetMotorSpeed(20.0f); // Rotar hacia abajo
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
    }

    ~Paleta() {}
};