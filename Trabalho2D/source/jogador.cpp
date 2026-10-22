#include "jogador.h"

void Jogador::Desenha_rect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    glVertex3f(width / 2, height, 0.0);
    glVertex3f(-width / 2, height, 0.0);
    glVertex3f(-width / 2, 0, 0.0);
    glVertex3f(width / 2, 0, 0.0);
    glEnd();
}

void Jogador::Desenha_circ(GLint radius, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 20)
    {
        float radiano = i * M_PI / 180.0;
        int x = radius * cos(radiano);
        int y = radius * sin(radiano);
        glVertex3f(x, y, 0.0);
    }
    glEnd();
}

void Jogador::Desenha_arma(GLfloat x, GLfloat y, GLfloat height, GLfloat width, GLfloat theta, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();

    glTranslatef(x, y, .0);
    glRotatef(theta, 0, 0, 1);
    Desenha_rect(height, width, R, G, B);

    glPopMatrix();
}

void Jogador::Desenha_partes(GLfloat x, GLfloat y, GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();

    glTranslatef(x, y, .0);
    Desenha_rect(height, width, R, G, B);

    glPopMatrix();
}

void Jogador::Desenha_jogador(GLfloat x, GLfloat y, GLfloat thetaArma, GLfloat thetaJogador, GLfloat raioCabeca, Cor cor)
{
    glPushMatrix();

    glTranslatef(x, y, .0);
    glRotatef(thetaJogador, 0, 0, 1);

    Desenha_arma(raioCabeca + 0.4 * raioCabeca, -raioCabeca, 3 * raioCabeca, 0.5 * raioCabeca, thetaArma, 0.6, 0.2, 0);
    Desenha_partes(-raioCabeca / 2, -origem_pes, 2 * raioCabeca, raioCabeca / 2, 0, 0, 0);
    Desenha_partes(raioCabeca / 2, origem_pes, -2 * raioCabeca, raioCabeca / 2, 0, 0, 0);
    // cabeca
    Desenha_circ(raioCabeca, cor.r, cor.g, cor.b);

    glPopMatrix();
}

void RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut)
{
    float angleRad = angle * M_PI / 180.0;
    xOut = x * cos(angleRad) - y * sin(angleRad);
    yOut = x * sin(angleRad) + y * cos(angleRad);
}

void Jogador::Roda_arma(GLfloat theta)
{
    gThetaArma = theta;
}

void Jogador::Mira(float x_mouse, float y_mouse)
{
    GLfloat p1x = 0, p1y = 0;
    GLfloat p1xl = 0, p1yl = 0;
    GLfloat p1xl2 = 0, p1yl2 = 0;

    // transformações para a base da arma
    RotatePoint(p1x, p1y, gThetaArma, p1xl, p1yl);
    p1xl += raioCabeca + 0.4 * raioCabeca;
    RotatePoint(p1xl, p1yl, gThetaJogador, p1xl2, p1yl2);
    p1yl2 += gY;
    p1xl2 += gX;

    float dx = x_mouse - p1xl2;
    float dy = y_mouse - p1yl2;

    // angulo do vetor base-mouse
    float theta_global = atan2(dx, dy) * 180.0 / M_PI * -1;

    // transforma referente ao angulo do jogador
    float theta_local = theta_global - gThetaJogador;

    while (theta_local > 180.0)
        theta_local -= 360.0;
    while (theta_local < -180.0)
        theta_local += 360.0;

    if (theta_local > 30.0)
    {
        theta_local = 30.0;
    }
    else if (theta_local < -30.0)
    {
        theta_local = -30.0;
    }

    Roda_arma(theta_local);
}

void Jogador::Roda_jogador(GLfloat inc, GLfloat time)
{
    gThetaJogador += inc * time;
}

void Jogador::Move_pes(GLfloat time)
{
    origem_pes += 0.1 * passo * time;
    if (origem_pes > (2 * raioCabeca))
    {
        passo *= -1;
    }
    else if (origem_pes <= 0)
    {
        passo *= -1;
    }
}

void Jogador::Move(int dir, GLfloat time, GLfloat limite_largura, GLfloat limite_altura)
{
    float radiano = (gThetaJogador + 90.0f) * M_PI / 180.0f;

    float proximo_x = gX + cos(radiano) * velocidade * dir * time;
    float proximo_y = gY + sin(radiano) * velocidade * dir * time;

    //testa a parede (Eixo X).
    if ((proximo_x - raioCabeca > 0) && (proximo_x + raioCabeca < limite_largura)) 
    {
        gX = proximo_x;
    }

    //testa a parede (Eixo Y).
    if ((proximo_y - raioCabeca > 0) && (proximo_y + raioCabeca < limite_altura)) 
    {
        gY = proximo_y;
    }
    Move_pes(time);
}

Tiro *Jogador::Atira()
{

    GLfloat p1x = 0, p1y = 0;
    GLfloat p1xl = 0, p1yl = 0;
    GLfloat p1xl2 = 0, p1yl2 = 0;

    RotatePoint(p1x, p1y, gThetaArma, p1xl, p1yl);
    p1xl += raioCabeca + 0.4 * raioCabeca;
    p1yl -= raioCabeca;

    RotatePoint(p1xl, p1yl, gThetaJogador, p1xl2, p1yl2);

    p1yl2 += gY;
    p1xl2 += gX;

    GLfloat p2x = 0, p2y = raioCabeca * 4;
    GLfloat p2xl = 0, p2yl = 0;
    GLfloat p2xl2 = 0, p2yl2 = 0;

    RotatePoint(p2x, p2y, gThetaArma, p2xl, p2yl);
    p2xl += raioCabeca + 0.4 * raioCabeca;
    p2yl -= raioCabeca;
    RotatePoint(p2xl, p2yl, gThetaJogador, p2xl2, p2yl2);

    p2yl2 += gY;
    p2xl2 += gX;

    float dy = p2yl2 - p1yl2;
    float dx = p2xl2 - p1xl2;
    GLfloat angulo_tiro = atan2(dy, dx);

    Tiro *t = new Tiro(p2xl2, p2yl2, angulo_tiro, 0.1);

    return t;
}

bool Jogador::Atingido(Tiro *tiro)
{
    float x_t = 0, y_t = 0;
    tiro->GetPos(x_t, y_t);
    float raio_tiro = tiro->Obtem_raio();

    float dx = x_t - gX;
    float dy = y_t - gY;
    float distancia = sqrt(dx * dx + dy * dy);

    if (distancia < raio_tiro + raioCabeca)
    {
        return true;
    }
    return false;
};