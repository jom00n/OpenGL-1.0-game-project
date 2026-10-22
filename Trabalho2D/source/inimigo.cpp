#include "inimigo.h"

void Inimigo::Desenha_rect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    glVertex3f(width / 2, height, 0.0);
    glVertex3f(-width / 2, height, 0.0);
    glVertex3f(-width / 2, 0, 0.0);
    glVertex3f(width / 2, 0, 0.0);
    glEnd();
}
void Inimigo::Desenha_circ(GLint radius, GLfloat R, GLfloat G, GLfloat B)
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
void Inimigo::Desenha_partes(GLfloat x, GLfloat y, GLfloat height, GLfloat width, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();

    glTranslatef(x, y, .0);
    Desenha_rect(height, width, R, G, B);

    glPopMatrix();
}
void Inimigo::Desenha_arma(GLfloat x, GLfloat y, GLfloat height, GLfloat width, GLfloat theta, GLfloat R, GLfloat G, GLfloat B)
{
    glPushMatrix();

    glTranslatef(x, y, .0);
    glRotatef(theta, 0, 0, 1);
    Desenha_rect(height, width, R, G, B);

    glPopMatrix();
}
void Inimigo::Desenha_inimigo(GLfloat x, GLfloat y, GLfloat thetaArma, GLfloat raioCabeca)
{

    glPushMatrix();

    glTranslatef(x, y, .0);
    Desenha_arma(raioCabeca + 0.4 * raioCabeca, raioCabeca, 3 * raioCabeca, 0.5 * raioCabeca, thetaArma, 0.6, 0.2, 0);
    Desenha_partes(-raioCabeca / 2, -origem_pes, 2 * raioCabeca, raioCabeca / 2, 0, 0, 0);
    Desenha_partes(raioCabeca / 2, origem_pes, -2 * raioCabeca, raioCabeca / 2, 0, 0, 0);
    // cabeca
    Desenha_circ(raioCabeca, cor.r, cor.g, cor.b);

    glPopMatrix();
}

void Inimigo::Move_pes(GLfloat time)
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

void Inimigo::Move(GLfloat time)
{
    gY -= velocidade * time;

    Move_pes(time);
}

void Inimigo::RotatePoint(GLfloat x, GLfloat y, GLfloat angle, GLfloat &xOut, GLfloat &yOut)
{
    float angleRad = angle * M_PI / 180.0;
    xOut = x * cos(angleRad) - y * sin(angleRad);
    yOut = x * sin(angleRad) + y * cos(angleRad);
}

void Inimigo::Mira(GLfloat x, GLfloat y)
{
    const GLfloat baseArmaX = gX + raioCabeca + 0.4 * raioCabeca;
    const GLfloat baseArmaY = gY + raioCabeca;
    const GLfloat dx = x - baseArmaX;
    const GLfloat dy = y - baseArmaY;

    gThetaArma = -atan2(dx, dy) * 180.0 / M_PI;
}

Tiro *Inimigo::Atira()
{
    GLfloat pontaX, pontaY;
    RotatePoint(0, 3 * raioCabeca, gThetaArma, pontaX, pontaY);
    pontaX += gX + raioCabeca + 0.4 * raioCabeca;
    pontaY += gY + raioCabeca;

    GLfloat direcaoX, direcaoY;
    RotatePoint(0, 1, gThetaArma, direcaoX, direcaoY);
    const GLfloat anguloTiro = atan2(direcaoY, direcaoX);

    Tiro *t = new Tiro(pontaX, pontaY, anguloTiro, velocidadeTiro);

    return t;
}

float Inimigo::Obtem_ultimoTiro()
{
    return ultimoTiro;
};

void Inimigo::altera_ultimoTiro(GLfloat tempo)
{

    ultimoTiro = tempo;
}
