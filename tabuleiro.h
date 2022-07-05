#include "glm/glm.hpp"
#include "glm/ext.hpp"
#ifndef TABULEIRO_H
#define TABULEIRO_H
typedef struct quadrado{
    glm::vec3 pos;
    float color[3];
}Quadrado;
#endif // TABULEIRO_H
