#include "glm/glm.hpp"
#include "glm/ext.hpp"

#ifndef OBJETO_H
#define OBJETO_H
typedef struct ponto{
    glm::vec3 coord;
    glm::vec3 normal;
    glm::vec2 tex;
}Ponto;
typedef struct face{
    int id_ponto_1,id_ponto_2,id_ponto_3;
}Face;
typedef struct objeto{
    struct face faces[50000];
    int quant_lados;
    struct ponto pontos[100000];
    int quant_ponto;
    glm::vec3 translate;
}Objeto;

#endif // OBJETO_H
