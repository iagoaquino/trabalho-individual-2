#include "glm/glm.hpp"
#include "glm/ext.hpp"

#ifndef OBJETO_H
#define OBJETO_H
typedef struct normal{
    glm::vec3 normal;
}Normal;
typedef struct ponto{
    glm::vec3 coord;
}Ponto;
typedef struct objeto{
    struct ponto[100000];
    int quant_ponto;
}Objeto;

#endif // OBJETO_H
