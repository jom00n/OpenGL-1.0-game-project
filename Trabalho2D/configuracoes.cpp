
#include "configuracoes.h" 
#include "tinyxml2.h" 

using namespace tinyxml2;

void lerCor(XMLElement* elemento, Cor& cor){
    if (elemento) {
        elemento->QueryFloatAttribute("R", &cor.r);
        elemento->QueryFloatAttribute("G", &cor.g);
        elemento->QueryFloatAttribute("B", &cor.b);
    }
}

Jogo ler_configuracoes(){
    XMLDocument configuracoes;
    Jogo jogo;

    //abrindo arquivo XML
    if(configuracoes.LoadFile("configuracoes.xml") != XML_SUCCESS){
        printf("Erro ao abrir XML");
        exit(1);
    }
    //verificando se o elemento raiz foi lido
    XMLElement* jogo_xml = configuracoes.FirstChildElement("jogo");
    if(!jogo_xml){
        printf("Erro ao tentar buscar elemento raiz");
        exit(1);
    }
    //arena
    XMLElement* arena = jogo_xml->FirstChildElement("arena");
    if(arena){
        arena->QueryFloatAttribute("altura", &jogo.arena.altura);
        arena->QueryFloatAttribute("largura", &jogo.arena.largura);
        lerCor(arena, jogo.arena.cor);

    }
    //jogador
    XMLElement* jogador = jogo_xml->FirstChildElement("jogador");
    if(jogador){
        jogador->QueryFloatAttribute("raioCabeca", &jogo.jogador.raioCabeca);
        jogador->QueryFloatAttribute("velocidade", &jogo.jogador.velocidade);
        lerCor(jogador, jogo.jogador.cor);

    }
    //inimigos
    XMLElement* inimigo = jogo_xml->FirstChildElement("inimigo");
    if(inimigo){
        inimigo->QueryFloatAttribute("raioCabeca", &jogo.inimigo.raioCabeca);
        inimigo->QueryFloatAttribute("tirosPorSegundo", &jogo.inimigo.tirosPorSegundo);
        inimigo->QueryFloatAttribute("velocidadeTiro", &jogo.inimigo.velocidadeTiro);
        lerCor(inimigo, jogo.inimigo.cor);

    }
    //barril
    XMLElement* barril = jogo_xml->FirstChildElement("barril");
    if(barril){
        barril->QueryFloatAttribute("altura", &jogo.barril.altura);
        barril->QueryFloatAttribute("largura", &jogo.barril.largura);
        barril->QueryIntAttribute("numeroTiros", &jogo.barril.numeroTiros);
        barril->QueryIntAttribute("nParaGanhar", &jogo.barril.nParaGanhar);
        barril->QueryFloatAttribute("velocidade", &jogo.barril.velocidade);
        lerCor(barril, jogo.barril.cor);

    }

    return jogo;
}