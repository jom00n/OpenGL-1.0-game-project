#ifndef CONFIGURACOES_H
#define CONFIGURACOES_H

#include <iostream>
#include <stdio.h>
#include "configuracoes.h" 


struct Cor {
    float r = 0;
    float g = 0;
    float b = 0;
};

struct Arena {
    float altura = 0;
    float largura = 0;
    Cor cor;
};

struct Jogador_ {
    float raioCabeca = 0;
    float velocidade = 0;
    Cor cor;
};

struct Inimigo_ {
    float raioCabeca = 0;
    float tirosPorSegundo = 0;
    float velocidadeTiro = 0;
    Cor cor;
};

struct Barril_ {
    float altura = 0;
    float largura = 0;
    int numeroTiros = 0;   
    int nParaGanhar = 0;   
    float velocidade = 0;
    Cor cor;
};

struct Jogo {
    Arena arena;
    Jogador_ jogador;
    Inimigo_ inimigo;
    Barril_ barril;
};

Jogo ler_configuracoes();

#endif