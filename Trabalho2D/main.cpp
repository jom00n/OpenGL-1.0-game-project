#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include "configuracoes.h"
#include "source/jogador.h"
#include "source/barril.h"
#include "source/inimigo.h"
#include "source/tiro.h"
#include <memory>
#include <array>
#include <vector>
#include <time.h>

#define QTD_TIROS 50

// Key status
int keyStatus[256];

// XML info
Jogo informacoes_jogo = ler_configuracoes();

// jogador
Jogador jogador(informacoes_jogo.jogador);

// tiros
std::array<std::unique_ptr<Tiro>, QTD_TIROS> tiro;
std::array<std::unique_ptr<Tiro>, QTD_TIROS> tiro_inimigo;

// barris
int maximo_barris = (informacoes_jogo.arena.altura / 2) / informacoes_jogo.barril.altura;
std::vector<std::unique_ptr<Barril>> barril;
float tempo_ultimo_barril = 0;
int qtd_barris = informacoes_jogo.barril.nParaGanhar;
int barris_destruidos = 0;

// incrementações
float inc_theta = 0.1;
GLfloat inc = 0.01;

void ResetKeyStatus()
{
    for (int i = 0; i < 256; i++)
    {
        keyStatus[i] = 0;
    }
}

void init(void)
{
    ResetKeyStatus();
    glClearColor(informacoes_jogo.arena.cor.r, informacoes_jogo.arena.cor.g, informacoes_jogo.arena.cor.b, 1.0);

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, (informacoes_jogo.arena.largura), // <>x
            0, (informacoes_jogo.arena.altura),  // <>y
            -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void desenhaTexto(GLint x, GLint y, const char *text, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glRasterPos2i(x, y);
    for (const char *c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (const auto &b : barril)
    {
        if (b)
            b->Desenha();
    }
    for (const auto &t : tiro)
    {
        if (t)
            t->Desenha();
    }

    for (const auto &t : tiro_inimigo)
    {
        if (t)
            t->Desenha();
    }

    jogador.Desenha();

    desenhaTexto(10, informacoes_jogo.arena.altura - 20, "Barris restantes: ", 1, 1, 1);
    desenhaTexto(150, informacoes_jogo.arena.altura - 20, std::to_string(qtd_barris).c_str(), 1, 1, 1);

    desenhaTexto(10, informacoes_jogo.arena.altura - 40, "Barris destruídos: ", 1, 1, 1);
    desenhaTexto(150, informacoes_jogo.arena.altura - 40, std::to_string(barris_destruidos).c_str(), 1, 1, 1);

    glutSwapBuffers();
}

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
    case 'A':
        keyStatus[(int)('a')] = 1;
        break;
    case 'd':
    case 'D':
        keyStatus[(int)('d')] = 1;
        break;
    case 'w':
    case 'W':
        keyStatus[(int)('w')] = 1;
        break;
    case 's':
    case 'S':
        keyStatus[(int)('s')] = 1;
        break;
    case 27:
        exit(0);
    }
    glutPostRedisplay();
}

void keyup(unsigned char key, int x, int y)
{
    keyStatus[(int)(key)] = 0;
    glutPostRedisplay();
}

void mouseMotion(int x, int y)
{
    int y_crr = informacoes_jogo.arena.altura - y;

    jogador.Mira(x, y_crr);

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        for (auto &t : tiro)
        {
            if (t == nullptr)
            {
                t.reset(jogador.Atira());
                break;
            }
        }
    }
    glutPostRedisplay();
}

void idle(void)
{
    // correção de tempo
    static GLdouble previous_time = glutGet(GLUT_ELAPSED_TIME);
    GLdouble current_time, time_diference;
    // Pega o tempo que passou do inicio da aplicacao
    current_time = glutGet(GLUT_ELAPSED_TIME);
    time_diference = current_time - previous_time;
    previous_time = current_time;

    // cria barril (2s)
    if (tempo_ultimo_barril + 2000 < current_time)
    {
        for (auto &b : barril)
        {
            if (b == nullptr)
            {
                float x = rand() % ((int)informacoes_jogo.arena.largura - (int)informacoes_jogo.barril.largura);
                if (x - informacoes_jogo.barril.largura / 2 < 0)
                {
                    x = informacoes_jogo.barril.largura / 2;
                }
                if (rand() % 2 == 0)
                {
                    b.reset(new Barril(informacoes_jogo.barril, x, informacoes_jogo.arena.altura, &informacoes_jogo.inimigo));
                }
                else
                {
                    b.reset(new Barril(informacoes_jogo.barril, x, informacoes_jogo.arena.altura, nullptr));
                }

                tempo_ultimo_barril = current_time;

                break;
            }
        }
    }

    float x_jogador = jogador.Obtem_x();
    float y_jogador = jogador.Obtem_y();

    // chaves de movimento
    if (keyStatus[(int)('w')])
    {
        jogador.Move(1, time_diference, informacoes_jogo.arena.largura, informacoes_jogo.arena.altura/2);
    }
    if (keyStatus[(int)('s')])
    {
        jogador.Move(-1, time_diference, informacoes_jogo.arena.largura, informacoes_jogo.arena.altura/2);
    }
    if (keyStatus[(int)('a')])
    {
        jogador.Roda_jogador(inc_theta, time_diference);
    }
    if (keyStatus[(int)('d')])
    {
        jogador.Roda_jogador(-inc_theta, time_diference);
    }

    // tiro jogador move e colide
    for (auto &t : tiro)
    {
        if (t)
        {
            t->Move(time_diference);

            // Trata colisao tiro - barril
            for (auto &b : barril)
            {
                if (b)
                {
                    if (b->Atingido(t.get()))
                    {
                        if (b->Obtem_numeroTiros() > 1)
                        {
                            b->Reduz_numeroTiros();
                        }
                        else
                        {
                            b.reset();
                            qtd_barris--;
                            barris_destruidos++;
                            if (qtd_barris <= 0)
                            {
                                printf("Parabens, voce ganhou!\n");
                                exit(0);
                            }
                        }
                        t.reset();
                        break;
                    }
                }
            }

            if (t && !t->Valido(informacoes_jogo.arena.altura))
            {
                t.reset();
            }
        }
    }
    // tiro inimigo move e colide
    for (auto &t : tiro_inimigo)
    {
        if (t)
        {
            t->Move(time_diference);

            // Trata colisao tiro - jogador
            if (jogador.Atingido(t.get()))
            {
                printf("Game Over\n");
                exit(0);
            }

            if (t && !t->Valido(informacoes_jogo.arena.altura))
            {
                t.reset();
            }
        }
    }

    // barril atinge jogador
    for (auto &b : barril)
    {
        if (b)
        {
            // move barril
            b->Move(time_diference);
            // verifica colisao barril - jogador
            if (b->Atingiu(jogador))
            {
                printf("Game Over\n");
                exit(0);
            }
            // inimigo atira
            Inimigo *inimigo = b->Obtem_inimigo();
            if (inimigo)
            {
                inimigo->Mira(jogador.Obtem_x(), jogador.Obtem_y());

                float tempo_entre_tiros = 1000.0 / informacoes_jogo.inimigo.tirosPorSegundo;
                float tempo_ultimo_tiro = inimigo->Obtem_ultimoTiro();
                if (tempo_ultimo_tiro + tempo_entre_tiros < current_time)
                {
                    for (auto &t : tiro_inimigo)
                    {
                        if (t == nullptr)
                        {
                            t.reset(inimigo->Atira());
                            inimigo->altera_ultimoTiro(current_time);
                            break;
                        }
                    }
                }
            }
        }
    }

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    srand(time(NULL));

    // window.
    glutInitWindowSize(informacoes_jogo.arena.largura, informacoes_jogo.arena.altura);
    glutInitWindowPosition(150, 50);
    glutCreateWindow("bahilhes");

    // callbacks
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyPress);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(mouseMotion);
    glutKeyboardUpFunc(keyup);

    // inicializa barris e inimigos
    barril.resize(maximo_barris);

    init();

    glutMainLoop();

    return 0;
}