//Iago de Aquino Oliveira: 494017
#include <iostream>
#include<GL\glut.h>
#include<math.h>
#include<tabuleiro.h>
#include"leitura.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "textura.cpp"
using namespace std;
Quadrado tabuleiro[64];
glm::vec3 pos_camera(10,10,10);
glm::vec3 pos_luz(0,0,15);
glm::vec3 ambiente(0.2,0.2,0.2);
glm::vec3 difusa(0.9,0.9,0.9);
glm::vec3 especular(0.4,0.4,0.4);
float expoente = 2;
Objeto* obj;
float produto_escalar(glm::vec3 v1,glm::vec3 v2){
    float x = v1.x*v2.x;
    float y = v1.y*v2.y;
    float z = v1.z*v2.z;
    return x+y+z;
}
glm::vec3 aplicar_luz(glm::vec3 normal,glm::vec3 pos,glm::vec3 cor_objeto){
    glm::vec3 lp = normalize(pos_luz-pos);
    glm::vec3 vw = normalize(pos_camera-pos);
    glm::vec3 rf = 2 * glm::dot(lp,normal)*normal -lp;
    glm::vec3 ambiente_final = ambiente * glm::vec3(0.5,0.5,0.5);
    glm::vec3 difusa_final = (difusa * cor_objeto) * produto_escalar(normal,lp);
    glm::vec3 especular_final;
    if(produto_escalar(vw,rf) < 0){
        especular_final = glm::vec3(0,0,0);
    }else{
        especular_final = (especular * glm::vec3(0.5,0.5,0.5)) * pow(produto_escalar(vw,rf),expoente);
    }
    glm::vec3 resultado_final = ambiente_final+difusa_final+especular_final;
    return resultado_final;
}
void criarTabuleiro(){
    int x = 1, y = 1,z = 0,pos = 0,cont = 0;
    for(int i = 0; i < 8 ;i++){
        for(int j = 0;j < 8;j++){
            Quadrado quadrado;
            if(cont % 2 == 0){
                quadrado.color[0] = 1;
                quadrado.color[1] = 1;
                quadrado.color[2] = 1;
            }else{
                quadrado.color[0] = 0;
                quadrado.color[1] = 0;
                quadrado.color[2] = 0;
            }
            quadrado.pos.x = x;
            quadrado.pos.y = y;
            quadrado.pos.z = z;
            tabuleiro[pos] = quadrado;
            x += 2;
            pos++;
            cont++;
        }
        cont++;
        y +=2;
        x = 1;
    }
}
void mostrarTabuleiro(){
    for(int i = 0; i < 64;i++){
        cout<<"(id:"<<i<<")"<<endl;
        cout<< tabuleiro[i].pos.x<<endl;
        cout<< tabuleiro[i].pos.y<<endl;
        cout<< tabuleiro[i].pos.z<<endl;
        cout<<"("<<tabuleiro[i].color[0]<<", "<<tabuleiro[i].color[1]<<", "<<tabuleiro[i].color[2]<<")"<<endl;
    }
}
void inicializar(){
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.5,0.5,0.5,1);
    glPointSize(10);
    obj = ler_arquivo();
    glLineWidth(5);
    criarTabuleiro();
    //mostrarTabuleiro();
    carregar_textura();
}
void desenhar_obj(){
    glTranslatef(2,2,0);
    glBegin(GL_TRIANGLES);
        for(int i = 0;i < obj->quant_lados;i++){
           glm::vec3 cor1 = aplicar_luz(obj->pontos[obj->faces[i].id_ponto_1 - 1].normal,obj->pontos[obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.1,0.1,0.1));
           glColor3f(cor1.x,cor1.y,cor1.z);
           glVertex3f(obj->pontos[obj->faces[i].id_ponto_1-1].coord.x,obj->pontos[obj->faces[i].id_ponto_1-1].coord.y,obj->pontos[obj->faces[i].id_ponto_1-1].coord.z);
           glm::vec3 cor2 = aplicar_luz(obj->pontos[obj->faces[i].id_ponto_2 - 1].normal,obj->pontos[obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0,0,1));
           glColor3f(cor2.x,cor2.y,cor2.z);
           glVertex3f(obj->pontos[obj->faces[i].id_ponto_2-1].coord.x,obj->pontos[obj->faces[i].id_ponto_2-1].coord.y,obj->pontos[obj->faces[i].id_ponto_2-1].coord.z);
           glm::vec3 cor3 = aplicar_luz(obj->pontos[obj->faces[i].id_ponto_3 - 1].normal,obj->pontos[obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0,0,1));
           glColor3f(cor3.x,cor3.y,cor3.z);
           glVertex3f(obj->pontos[obj->faces[i].id_ponto_3-1].coord.x,obj->pontos[obj->faces[i].id_ponto_3-1].coord.y,obj->pontos[obj->faces[i].id_ponto_3-1].coord.z);
        }
    glEnd();
}
void desenharTabuleiro(){
    glBindTexture(GL_TEXTURE_2D,id);
    for(int i = 0;i<64;i++){
        glBegin(GL_QUADS);
            glm::vec3 cor1 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]));
            glColor3f(cor1.x,cor1.y,cor1.z);
            glTexCoord2f(0,1);
            glVertex3f(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z);
            glm::vec3 cor2 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]));
            glColor3f(cor2.x,cor2.y,cor2.z);
            glTexCoord2f(1,1);
            glVertex3f(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z);
            glm::vec3 cor3 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]));
            glColor3f(cor3.x,cor3.y,cor3.z);
            glTexCoord2f(1,0);
            glVertex3f(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z);
            glm::vec3 cor4 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]));
            glColor3f(cor4.x,cor4.y,cor4.z);
            glTexCoord2f(0,0);
            glVertex3f(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z);
        glEnd();
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}
void desenhar3D(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,1,1,40);
    glMatrixMode(GL_MODELVIEW);
    glm::mat4 camera = glm::lookAt(pos_camera,
                                   glm::vec3(0,0,0),
                                   glm::vec3(0,0,1));
    glLoadMatrixf(glm::value_ptr(camera));
    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(20,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,20,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,20);
    glEnd();
    desenharTabuleiro();
    desenhar_obj();
    glFlush();
}
int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,20);
    glutInitWindowSize(1200,600);
    glutCreateWindow("Trabalho 1");
    inicializar();
    glutDisplayFunc(desenhar3D);
    glutMainLoop();
}
