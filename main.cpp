//Iago de Aquino Oliveira: 494017
#include <iostream>
#include <GL/gl.h>
#include <GL/glext.h>
#include<GL\glut.h>
#include<math.h>
#include<tabuleiro.h>
#include"leitura.cpp"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "textura.cpp"
#include "pecas.h"
#include "iniciar_jogo.cpp"
Jogador branco;
jogador preto;
Quadrado selecionado;
int foiSelecionado = 0;
float w = 1200,h = 600;
using namespace std;
glm::vec3 pos_jogador_branco(29,9.5,15);
glm::vec3 pos_jogador_preto(-12,7.5,15);
glm::vec3 pos_camera(15,15,15);
glm::vec3 pos_luz(0,0,0);
glm::vec3 ambiente(0.5f,0.5f,0.5f);
glm::vec3 difusa(0.9f,0.9f,0.9f);
glm::vec3 especular(0.8f,0.8f,0.8f);
float expoente = 1;
float produto_escalar(glm::vec3 v1,glm::vec3 v2){
    float x = v1.x*v2.x;
    float y = v1.y*v2.y;
    float z = v1.z*v2.z;
    return x+y+z;
}
glm::vec3 aplicar_luz(glm::vec3 normal,glm::vec3 pos,glm::vec3 cor_objeto){
    glm::vec3 lp = normalize(pos_luz-pos);
    glm::vec3 vw = normalize(pos_camera-pos);
    glm::vec3 rf = 2*glm::dot(lp,normal)*normal -lp;
    glm::vec3 ambiente_final = ambiente * cor_objeto;
    glm::vec3 difusa_final = (difusa * cor_objeto) * glm::dot(normal,lp);
    glm::vec3 especular_final;
    if(produto_escalar(vw,rf) < 0){
        especular_final = glm::vec3(0.0f,0.0f,0.0f);
    }else{
        especular_final = especular * glm::vec3(0.9f,0.9f,0.9f) * (float)pow(glm::dot(vw,rf),expoente);
    }
    glm::vec3 resultado_final = ambiente_final+difusa_final+especular_final;
    return resultado_final;
}
bool checar_pontos_quadrado(float x_quadrado,float y_quadrado,float x_peca,float y_peca){
    if(x_quadrado - 1.0 <= x_peca && x_quadrado + 1.0 >= x_peca && y_quadrado - 1.0 <= y_peca && y_quadrado + 1.0 >= y_peca){
        return true;
    }
    return false;
}
Quadrado pegar_quadrado(float x,float y){
    for(int i = 0;i < 64;i++){
        if(checar_pontos_quadrado(tabuleiro[i].pos.x,tabuleiro[i].pos.y,x,y)){
            foiSelecionado = 1;
            return tabuleiro[i];
        }
    }
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
void desenhar_preto(int pos,int tipo){
    if(tipo == 1){
        glPushMatrix();
        glTranslatef(preto.torres[pos].translate.x,preto.torres[pos].translate.y,preto.torres[pos].translate.z);
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < preto.torres[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1 - 1].normal,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1-1].coord.x,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1-1].coord.y,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2 - 1].normal,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2-1].coord.x,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2-1].coord.y,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_3 - 1].normal,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_3-1].coord.x,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_3-1].coord.y,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }else if(tipo == 2){
        glPushMatrix();
        glTranslatef(preto.cavalos[pos].translate.x,preto.cavalos[pos].translate.y,preto.cavalos[pos].translate.z);
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < preto.cavalos[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1 - 1].normal,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.x,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.y,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2 - 1].normal,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.x,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.y,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_3 - 1].normal,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_3-1].coord.x,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_3-1].coord.y,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }else if(tipo == 3){
        glPushMatrix();
        glTranslatef(preto.bispos[pos].translate.x,preto.bispos[pos].translate.y,preto.bispos[pos].translate.z);
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < preto.bispos[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1 - 1].normal,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1-1].coord.x,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1-1].coord.y,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2 - 1].normal,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2-1].coord.x,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2-1].coord.y,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_3 - 1].normal,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_3-1].coord.x,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_3-1].coord.y,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }else if(tipo == 4){
        glPushMatrix();
        glTranslatef(preto.rainha.translate.x,preto.rainha.translate.y,preto.rainha.translate.z);
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < preto.rainha.obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1 - 1].normal,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1-1].coord.x,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1-1].coord.y,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2 - 1].normal,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2-1].coord.x,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2-1].coord.y,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_3 - 1].normal,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_3-1].coord.x,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_3-1].coord.y,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }else if(tipo == 5){
        glPushMatrix();
        glTranslatef(preto.rei.translate.x,preto.rei.translate.y,preto.rei.translate.z);
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < preto.rei.obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1 - 1].normal,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1-1].coord.x,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1-1].coord.y,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2 - 1].normal,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2-1].coord.x,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2-1].coord.y,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_3 - 1].normal,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_3-1].coord.x,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_3-1].coord.y,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }else if(tipo == 6){
        glPushMatrix();
        glTranslatef(preto.peoes[pos].translate.x,preto.peoes[pos].translate.y,preto.peoes[pos].translate.z);
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < preto.peoes[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1 - 1].normal,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1-1].coord.x,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1-1].coord.y,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2 - 1].normal,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2-1].coord.x,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2-1].coord.y,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_3 - 1].normal,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3));
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_3-1].coord.x,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_3-1].coord.y,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }
}
void desenhar_branco(int pos,int tipo){
    if(tipo == 1){
        glPushMatrix();
        glTranslatef(branco.torres[pos].translate.x,branco.torres[pos].translate.y,branco.torres[pos].translate.z);
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < branco.torres[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1 - 1].normal,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1-1].coord.x,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1-1].coord.y,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2 - 1].normal,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2-1].coord.x,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2-1].coord.y,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_3 - 1].normal,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_3-1].coord.x,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_3-1].coord.y,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }else if(tipo == 2){
        glPushMatrix();
        glTranslatef(branco.cavalos[pos].translate.x,branco.cavalos[pos].translate.y,branco.cavalos[pos].translate.z);
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < branco.cavalos[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1 - 1].normal,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.x,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.y,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2 - 1].normal,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.x,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.y,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_3 - 1].normal,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_3-1].coord.x,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_3-1].coord.y,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }else if(tipo == 3){
        glPushMatrix();
        glTranslatef(branco.bispos[pos].translate.x,branco.bispos[pos].translate.y,branco.bispos[pos].translate.z);
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < branco.bispos[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1 - 1].normal,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1-1].coord.x,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1-1].coord.y,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2 - 1].normal,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2-1].coord.x,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2-1].coord.y,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_3 - 1].normal,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_3-1].coord.x,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_3-1].coord.y,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }else if(tipo == 4){
        glPushMatrix();
        glTranslatef(branco.rainha.translate.x,branco.rainha.translate.y,branco.rainha.translate.z);
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < branco.rainha.obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1 - 1].normal,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1-1].coord.x,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1-1].coord.y,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2 - 1].normal,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2-1].coord.x,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2-1].coord.y,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_3 - 1].normal,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_3-1].coord.x,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_3-1].coord.y,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }else if(tipo == 5){
        glPushMatrix();
        glTranslatef(branco.rei.translate.x,branco.rei.translate.y,branco.rei.translate.z);
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < branco.rei.obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1 - 1].normal,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1-1].coord.x,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1-1].coord.y,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2 - 1].normal,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2-1].coord.x,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2-1].coord.y,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_3 - 1].normal,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_3-1].coord.x,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_3-1].coord.y,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }else if(tipo == 6){
        glPushMatrix();
        glTranslatef(branco.peoes[pos].translate.x,branco.peoes[pos].translate.y,branco.peoes[pos].translate.z);
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < branco.peoes[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1 - 1].normal,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1-1].coord.x,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1-1].coord.y,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2 - 1].normal,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2-1].coord.x,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2-1].coord.y,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_3 - 1].normal,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1));
               glColor3f(cor3.x,cor3.y,cor3.z);
               glVertex3f(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_3-1].coord.x,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_3-1].coord.y,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_3-1].coord.z);
            }
        glEnd();
        glPopMatrix();
    }
}
void inicializar(){
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.5,0.5,0.5,1);
    glPointSize(10);
    branco = iniciar_branco();
    preto = iniciar_preto();
    glLineWidth(5);
    criarTabuleiro();
    iniciar_2D();
    //mostrarTabuleiro();
    carregar_textura();
}
void desenhar_tabuleiro(){
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
    glBindTexture(GL_TEXTURE_2D,0);
}
void desenhar_tabuleiro_2D(){
    for(int i = 0;i<64;i++){
        glBegin(GL_QUADS);
            glColor3f(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]);
            glVertex2f(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y+1);
            glVertex2f(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y+1);
            glVertex2f(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y-1);
            glVertex2f(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y-1);
            if(tabuleiro[i].situacao == 1){
                glColor3f(1,0,0);
                glVertex2f(tabuleiro[i].pos.x-0.5,tabuleiro[i].pos.y);
                glVertex2f(tabuleiro[i].pos.x,tabuleiro[i].pos.y+0.5);
                glVertex2f(tabuleiro[i].pos.x+0.5,tabuleiro[i].pos.y);
                glVertex2f(tabuleiro[i].pos.x,tabuleiro[i].pos.y-0.5);
            }
        glEnd();
    }
}
void desenhar_pecas(){
    int tipo;
    for(tipo = 1;tipo<4;tipo++){
        for(int i =0;i<2;i++){
            desenhar_branco(i,tipo);
            desenhar_preto(i,tipo);
        }
    }
    for(tipo = 4;tipo<6;tipo++){
        for(int i =0;i<1;i++){
            desenhar_branco(i,tipo);
            desenhar_preto(i,tipo);
        }
    }
    tipo = 6;
    for(int i =0;i<8;i++){
        desenhar_branco(i,tipo);
        desenhar_preto(i,tipo);
    }
}
void pegar_click(int button,int status, int x,int y){
    float xFinal = (float)(16*x)/(w/2);
    float yFinal = (float)(16*(h-y))/h;
    if(button == GLUT_LEFT_BUTTON && status == GLUT_UP){
        selecionado = pegar_quadrado(xFinal,yFinal);
    }
 }
void desenhar(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,w/2,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,17.0,0,16.0,-1,1);
    desenhar_tabuleiro_2D();
    if(foiSelecionado == 1){
        glLineWidth(5);
        glBegin(GL_QUADS);
            glColor3f(1,1,0.2);
            glVertex2f(selecionado.pos.x-1,selecionado.pos.y+1);
            glVertex2f(selecionado.pos.x+1,selecionado.pos.y+1);
            glVertex2f(selecionado.pos.x+1,selecionado.pos.y-1);
            glVertex2f(selecionado.pos.x-1,selecionado.pos.y-1);
        glEnd();
    }
    glViewport(w/2,0,w,h);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,1,1,40);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glm::mat4 camera = glm::lookAt(pos_jogador_preto,
                                   glm::vec3(7,-2,4),
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
    desenhar_tabuleiro();
    desenhar_pecas();
    glDisable(GL_DEPTH_TEST);
    glPopMatrix();
    glFlush();
}
int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,20);
    glutInitWindowSize(1200,600);
    glutCreateWindow("Trabalho 1");
    inicializar();
    glutDisplayFunc(desenhar);
    glutMouseFunc(pegar_click);
    glutMainLoop();
}
