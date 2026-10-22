#ifndef JOGADOR_H
#define JOGADOR_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "tiro.h"
#include "../configuracoes.h"
#include "tiro.h"

class Jogador
{
    GLfloat gX;
    GLfloat gY;
    GLfloat gThetaArma;
    GLfloat gThetaJogador;
    GLfloat raioCabeca;
    GLfloat velocidade;
    GLfloat origem_pes;
    GLint passo;
    Cor cor;

private:
    void Desenha_rect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B);
    void Desenha_circ(GLint radius, GLfloat R, GLfloat G, GLfloat B);
    void Desenha_partes(GLfloat x, GLfloat y, GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B);
    void Desenha_arma(GLfloat x, GLfloat y, GLfloat height, GLfloat width, GLfloat theta, GLfloat R, GLfloat G, GLfloat B);
    void Desenha_jogador(GLfloat x, GLfloat y, GLfloat thetaArma, GLfloat thetaJogador, GLfloat raioCabeca, Cor cor);

public:
    Jogador(Jogador_ jogador)
    {
        gX = 100;
        gY = 100;
        gThetaArma = 0;
        gThetaJogador = 0;
        origem_pes = 0;
        passo = 1;
        this->raioCabeca = jogador.raioCabeca;
        this->velocidade = jogador.velocidade;
        this->cor.r = jogador.cor.r;
        this->cor.g = jogador.cor.g;
        this->cor.b = jogador.cor.b;
    };

    void Desenha()
    {
        Desenha_jogador(gX, gY, gThetaArma, gThetaJogador, raioCabeca, cor);
    };
    void Mira(float x_mouse, float y_mouse);
    Tiro *Atira();
    void Roda_arma(GLfloat theta);
    void Roda_jogador(GLfloat theta, GLfloat time);
    void Move(int dir, GLfloat time, GLfloat limite_largura, GLfloat limite_altura);
    void Move_pes(GLfloat time);
    bool Atingido(Tiro *tiro);
    GLfloat Obtem_x()
    {
        return gX;
    };
    GLfloat Obtem_y()
    {
        return gY;
    };
    GLfloat Obtem_raioCabeca()
    {
        return raioCabeca;
    };
};

#endif