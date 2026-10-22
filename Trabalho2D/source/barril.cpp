#include "barril.h"

void Barril::Desenha_rect(GLint height, GLint width, GLfloat R, GLfloat G, GLfloat B)
{
glColor3f(R, G, B);
    glBegin(GL_POLYGON);

    int num_segmentos = 10; 
    float theta;
    float r = 15.0f;

    float cx = width / 2.0f - r;
    float cy = height - r;
    for (int i = 0; i <= num_segmentos; i++) {
        theta = i * (M_PI / 2.0f) / num_segmentos; 
        glVertex3f(cx + r * cos(theta), cy + r * sin(theta), 0.0f);
    }

    cx = -width / 2.0f + r;
    cy = height - r;
    for (int i = 0; i <= num_segmentos; i++) {
        theta = (M_PI / 2.0f) + i * (M_PI / 2.0f) / num_segmentos;
        glVertex3f(cx + r * cos(theta), cy + r * sin(theta), 0.0f);
    }

    cx = -width / 2.0f + r;
    cy = r;
    for (int i = 0; i <= num_segmentos; i++) {
        theta = M_PI + i * (M_PI / 2.0f) / num_segmentos;
        glVertex3f(cx + r * cos(theta), cy + r * sin(theta), 0.0f);
    }

    cx = width / 2.0f - r;
    cy = r;
    for (int i = 0; i <= num_segmentos; i++) {
        theta = (3.0f * M_PI / 2.0f) + i * (M_PI / 2.0f) / num_segmentos;
        glVertex3f(cx + r * cos(theta), cy + r * sin(theta), 0.0f);
    }

    glEnd();
}

void Barril::Desenha_texto(const char *text, GLint x, GLint y, GLfloat R, GLfloat G, GLfloat B)
{
    glColor3f(R, G, B);
    glRasterPos2i(x, y);
    for (const char *c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void Barril::Desenha_barril(GLfloat x, GLfloat y, GLint height, GLint width, Cor cor)
{
    glPushMatrix();

    glTranslatef(x, y, .0);
    Desenha_rect(height, width, cor.r, cor.g, cor.b);

    char texto[3];
    sprintf(texto, "%d", numeroTiros);
    Desenha_texto(texto, width / 4, height / 2, 0, 0, 0);

    glPopMatrix();
}

bool Barril::Atingido(Tiro *tiro)
{
    float x_t = 0, y_t = 0;
    tiro->GetPos(x_t, y_t);
    float raio_tiro = tiro->Obtem_raio();

    if ((x_t + raio_tiro) > (gX - largura / 2) && (x_t - raio_tiro) < (gX + largura / 2) &&
        (y_t + raio_tiro) > gY && (y_t - raio_tiro) < (gY + altura))
    {
        return true;
    }
    return false;
};

bool Barril::Atingiu(Jogador jogador)
{
    float x_j = jogador.Obtem_x();
    float y_j = jogador.Obtem_y();
    float raio_j = jogador.Obtem_raioCabeca();

    if ((x_j + raio_j) > (gX - largura / 2) && (x_j - raio_j) < (gX + largura / 2) &&
        (y_j + raio_j) > gY && (y_j - raio_j) < (gY + altura))
    {
        return true;
    }
    return false;
}

void Barril::Reduz_numeroTiros()
{
    if (numeroTiros > 1)
    {
        numeroTiros--;
    }
}

Inimigo* Barril::Obtem_inimigo()
{
    return inimigo;
}
