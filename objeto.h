#include "glm/glm.hpp"
#include "glm/ext.hpp"
#ifndef OBJETO_H
#define OBJETO_H
typedef struct objeto{
    float coord[10000];
    int tam_cord;
    glm::vec3 matriz_mudança;
}Objeto;
#endif // OBJETO_H
