#ifndef INIMIGO_H
#define INIMIGO_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "../configuracoes.h"
#include "tiro.h"

class Inimigo
{
    GLfloat gX;
    GLfloat gY;
    GLfloat gThetaArma;
    GLfloat origem_pes;
    GLfloat raioCabeca;
    GLfloat tirosPorSegundo;
    GLfloat ultimoTiro;
    GLfloat velocidadeTiro;
    GLfloat velocidade;
    GLint passo;
    Tiro *tiro;
    Cor cor;

private:
    void Desenha_rect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B);
    void Desenha_circ(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void Desenha_partes(GLfloat x, GLfloat y, GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
    void Desenha_arma(GLfloat x, GLfloat y, GLfloat height, GLfloat width, GLfloat theta, GLfloat R, GLfloat G, GLfloat B);
    void Desenha_inimigo(GLfloat x, GLfloat y, GLfloat thetaArma, GLfloat raioCabeca);

public:
    Inimigo(Inimigo_ *inimigo, GLfloat x, GLfloat y, GLfloat velocidade)
    {
        gX = x;
        gY = y;
        gThetaArma = 180;
        origem_pes = 0;
        passo = 1;
        ultimoTiro = 0;
        this->raioCabeca = inimigo->raioCabeca;
        this->tirosPorSegundo = inimigo->tirosPorSegundo;
        this->velocidadeTiro = inimigo->velocidadeTiro;
        this->velocidade = velocidade;
        this->tiro = nullptr;
        this->cor = inimigo->cor;
    };

    void Desenha()
    {
        Desenha_inimigo(gX, gY, gThetaArma, raioCabeca);
    };

    float Obtem_ultimoTiro();
    void Move(GLfloat time);
    void Move_pes(GLfloat time);
    void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut);
    void Mira(GLfloat x, GLfloat y);
    void altera_ultimoTiro(GLfloat tempo);
    Tiro *Atira();
};

#endif