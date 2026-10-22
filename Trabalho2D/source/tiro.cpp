#include "tiro.h"
#include <math.h>
#include <stdio.h>
#define DISTANCIA_MAX 400

void Tiro::DesenhaCirc(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f (R, G, B); 
    glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i+=20){
            float radiano = i * M_PI / 180.;
            int x = radius*cos(radiano);
            int y = radius*sin(radiano);
            glVertex3f (x, y, 0.0);
        }
    glEnd();   
}

void Tiro::DesenhaTiro(GLfloat x, GLfloat y)
{
    glPushMatrix();

    glTranslatef(x, y, .0);
    DesenhaCirc(radiusTiro, 0, 0, 0);

    glPopMatrix();
}

void Tiro::Move(GLfloat time)
{
    float radiano = gDirectionAng * M_PI / 180.;
    gX += cos(gDirectionAng)*gVel*time;
    gY += sin(gDirectionAng)*gVel*time;
}

bool Tiro::Valido(int distanciaMax)
{
    float distancia = sqrt(pow(gX - gXInit, 2) + pow(gY - gYInit, 2));
    
    if(distancia > distanciaMax){
        return false;
    }
    return true;
}
