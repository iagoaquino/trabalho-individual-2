#include <iostream>
#include<GL\glut.h>
#include <GL/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_images.h"


using namespace std;

unsigned int id = 0;
int largura = 0,altura = 0,canais = 0;
void carregar_textura(){

    stbi_set_flip_vertically_on_load(true);
    unsigned char* entrada = stbi_load("textura.jpg",&largura,&altura,&canais,3);
    if(!entrada){
        cout<<"impossivel de carregar o arquivo"<<endl;
    }else{
        cout<<"arquivo carregado com sucesso"<<endl;
    }
    //gerar textura

    glGenTextures(1,&id);
    //configurar textura
    glBindTexture(GL_TEXTURE_2D,id);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, entrada);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(entrada);
}
