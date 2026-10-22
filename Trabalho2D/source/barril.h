#ifndef BARRIL_H
#define BARRIL_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include "../configuracoes.h"
#include "tiro.h"
#include "jogador.h"
#include "inimigo.h"

class Barril
{   
    GLfloat gX;
    GLfloat gY;
    GLfloat altura;
    GLfloat largura;
    GLint numeroTiros;   
    GLint nParaGanhar;   
    GLfloat velocidade;
    Inimigo* inimigo;
    Cor cor;

private:
    void Desenha_rect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B);
    void Desenha_texto(const char* text, GLint x, GLint y, GLfloat R, GLfloat G, GLfloat B);
    void Desenha_barril(GLfloat x, GLfloat y, GLint height, GLint width, Cor cor);

public:
    Barril(Barril_ barril, GLfloat x, GLfloat y, Inimigo_ *inimigo)
    {
        this->gX = x;
        this->gY = y;
        this->altura = barril.altura;
        this->largura = barril.largura;
        this->numeroTiros = barril.numeroTiros;
        this->nParaGanhar = barril.nParaGanhar;
        this->velocidade = barril.velocidade;
        this->cor.r = barril.cor.r;
        this->cor.g = barril.cor.g;
        this->cor.b = barril.cor.b;
        if(inimigo != nullptr)
        {
            this->inimigo = new Inimigo(inimigo, x - (barril.largura/4), y + (barril.altura/2), barril.velocidade);
        }
        else
        {
            this->inimigo = nullptr;
        }
    };

    void Desenha()
    {
        Desenha_barril(gX, gY, altura, largura, cor);
        if(inimigo != nullptr)
        {
            inimigo->Desenha();
        }
    };

    void Move(GLfloat time)
    {
        gY -= velocidade*time;
        if(inimigo != nullptr)
        {
            inimigo->Move(time);
        }
    };

    bool Atingido(Tiro* tiro);

    int Obtem_numeroTiros()
    {
        return numeroTiros;
    };

    bool Atingiu(Jogador jogador);
    void Reduz_numeroTiros();
    Inimigo* Obtem_inimigo();
};


#endif