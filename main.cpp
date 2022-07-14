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
#include "entradas.cpp"
using namespace std;
float w = 1200,h = 600;
glm::vec3 pos_jogador_branco(29,9.5,17);
glm::vec3 pos_jogador_preto(-12,7.5,17);
glm::vec3 pos_camera(-12,7.5,17);
glm::vec3 look(0,0,0);
glm::vec3 pos_luz(5,-10,5);
glm::vec3 ambiente(0.25f,0.25f,0.25f);
glm::vec3 difusa(1.0f,1.0f,1.0f);
glm::vec3 especular(0.5f,0.5f,0.5f);
void movimento_animado(int v){
    glutTimerFunc(1000.0/FPS,movimento_animado,0);
    glutPostRedisplay();
    if(ativar == 1){
        if(peca.x == 6 && peca.y == 1){
            t+= 0.1;
            movido->peoes[0].translate = ((1-t)*movido->peoes[0].translate)+(t * mov);
            cout<<t<<endl;
            if(t >= 1){
                passar_turno();
            }
        }else if(peca.x == 6 && peca.y == 2){
            t+= 0.1;
            movido->peoes[1].translate = ((1-t)*movido->peoes[1].translate)+(t * mov);
            cout<<t<<endl;
            if(t >= 1){
                passar_turno();
            }
        }else if(peca.x == 6 && peca.y == 3){
            t+= 0.1;
            movido->peoes[2].translate = ((1-t)*movido->peoes[2].translate)+(t * mov);
            cout<<t<<endl;
            if(t >= 1){
                passar_turno();
            }
        }else if(peca.x == 6 && peca.y == 4){
            t+= 0.1;
            movido->peoes[3].translate = ((1-t)*movido->peoes[3].translate)+(t * mov);
            cout<<t<<endl;
            if(t >= 1){
                passar_turno();
            }
        }else if(peca.x == 6 && peca.y == 5){
            t+= 0.1;
            movido->peoes[4].translate = ((1-t)*movido->peoes[4].translate)+(t * mov);
            cout<<t<<endl;
            if(t >= 1){
                passar_turno();
            }
        }else if(peca.x == 6 && peca.y == 6){
            t+= 0.1;
            movido->peoes[5].translate = ((1-t)*movido->peoes[5].translate)+(t * mov);
            cout<<t<<endl;
            if(t >= 1){
                passar_turno();
            }
        }else if(peca.x == 6 && peca.y == 7){
            t+= 0.1;
            movido->peoes[6].translate = ((1-t)*movido->peoes[6].translate)+(t * mov);
            cout<<t<<endl;
            if(t >= 1){
                passar_turno();
            }
        }else if(peca.x == 6 && peca.y == 8){
            t+= 0.1;
            movido->peoes[7].translate = ((1-t)*movido->peoes[7].translate)+(t * mov);
            cout<<t<<endl;
            if(t >= 1){
                passar_turno();
            }
        }else if(peca.x == 7 && peca.y == 1){
            t+= 0.1;
            pos_camera = (1-t)*pos_jogador_preto + (t*pos_jogador_branco);
            if(t >= 1){
                ativar = 0;
                t = 0;
            }
        }else if(peca.x == 7 && peca.y == 2){
            t+= 0.1;
            pos_camera = (1-t)*pos_jogador_branco + (t*pos_jogador_preto);
            if(t >= 1){
                ativar = 0;
                t = 0;
            }
        }
    }
}
glm::vec3 aplicar_luz(glm::vec3 normal,glm::vec3 pos,glm::vec3 cor_objeto,glm::vec3 obj_ambiente,glm::vec3 obj_especular,int obj_expoente){
    glm::vec3 lp = normalize(pos_luz-pos);
    glm::vec3 vw = normalize(pos_camera-pos);
    glm::vec3 rf = 2*glm::dot(lp,normal)*normal -lp;
    glm::vec3 ambiente_final = ambiente * obj_ambiente;
    glm::vec3 difusa_final = (difusa * cor_objeto) * glm::dot(normal,lp);
    glm::vec3 especular_final;
    if(glm::dot(vw,rf) < 0){
        especular_final = glm::vec3(0.0f,0.0f,0.0f);
    }else{
        especular_final = especular * obj_especular * (float)pow(glm::dot(vw,rf),obj_expoente);
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
void desenhar_preto(int pos,int tipo){
    if(tipo == 1){
        glPushMatrix();
        glTranslatef(preto.torres[pos].translate.x,preto.torres[pos].translate.y,preto.torres[pos].translate.z);
        glScalef(3,3,3);
        glBegin(GL_TRIANGLES);
            for(int i = 0;i < preto.torres[pos].obj->quant_lados;i++){
               glm::vec3 cor1 = aplicar_luz(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1 - 1].normal,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1-1].coord.x,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1-1].coord.y,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2 - 1].normal,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2-1].coord.x,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2-1].coord.y,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_3 - 1].normal,preto.torres[pos].obj->pontos[preto.torres[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
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
               glm::vec3 cor1 = aplicar_luz(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1 - 1].normal,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.x,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.y,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2 - 1].normal,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.x,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.y,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_3 - 1].normal,preto.cavalos[pos].obj->pontos[preto.cavalos[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
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
               glm::vec3 cor1 = aplicar_luz(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1 - 1].normal,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1-1].coord.x,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1-1].coord.y,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2 - 1].normal,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2-1].coord.x,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2-1].coord.y,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_3 - 1].normal,preto.bispos[pos].obj->pontos[preto.bispos[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
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
               glm::vec3 cor1 = aplicar_luz(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1 - 1].normal,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1-1].coord.x,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1-1].coord.y,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2 - 1].normal,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2-1].coord.x,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2-1].coord.y,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_3 - 1].normal,preto.rainha.obj->pontos[preto.rainha.obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
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
               glm::vec3 cor1 = aplicar_luz(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1 - 1].normal,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1-1].coord.x,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1-1].coord.y,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2 - 1].normal,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2-1].coord.x,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2-1].coord.y,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_3 - 1].normal,preto.rei.obj->pontos[preto.rei.obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
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
               glm::vec3 cor1 = aplicar_luz(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1 - 1].normal,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1-1].coord.x,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1-1].coord.y,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2 - 1].normal,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2-1].coord.x,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2-1].coord.y,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_3 - 1].normal,preto.peoes[pos].obj->pontos[preto.peoes[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(0.3,0.3,0.3),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
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
               glm::vec3 cor1 = aplicar_luz(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1 - 1].normal,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1-1].coord.x,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1-1].coord.y,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2 - 1].normal,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2-1].coord.x,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2-1].coord.y,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_3 - 1].normal,branco.torres[pos].obj->pontos[branco.torres[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
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
               glm::vec3 cor1 = aplicar_luz(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1 - 1].normal,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.x,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.y,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2 - 1].normal,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.x,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.y,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_3 - 1].normal,branco.cavalos[pos].obj->pontos[branco.cavalos[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
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
               glm::vec3 cor1 = aplicar_luz(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1 - 1].normal,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1-1].coord.x,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1-1].coord.y,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2 - 1].normal,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2-1].coord.x,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2-1].coord.y,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_3 - 1].normal,branco.bispos[pos].obj->pontos[branco.bispos[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
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
               glm::vec3 cor1 = aplicar_luz(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1 - 1].normal,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1-1].coord.x,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1-1].coord.y,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2 - 1].normal,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2-1].coord.x,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2-1].coord.y,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_3 - 1].normal,branco.rainha.obj->pontos[branco.rainha.obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
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
               glm::vec3 cor1 = aplicar_luz(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1 - 1].normal,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1-1].coord.x,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1-1].coord.y,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2 - 1].normal,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2-1].coord.x,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2-1].coord.y,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_3 - 1].normal,branco.rei.obj->pontos[branco.rei.obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
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
               glm::vec3 cor1 = aplicar_luz(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1 - 1].normal,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor1.x,cor1.y,cor1.z);
               glVertex3f(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1-1].coord.x,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1-1].coord.y,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_1-1].coord.z);
               glm::vec3 cor2 = aplicar_luz(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2 - 1].normal,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
               glColor3f(cor2.x,cor2.y,cor2.z);
               glVertex3f(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2-1].coord.x,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2-1].coord.y,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_2-1].coord.z);
               glm::vec3 cor3 = aplicar_luz(branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_3 - 1].normal,branco.peoes[pos].obj->pontos[branco.peoes[pos].obj->faces[i].id_ponto_3 - 1].coord,glm::vec3(1,1,1),glm::vec3(0.2,0.2,0.2),glm::vec3(0.8,0.8,0.8),20);
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
            glm::vec3 cor1 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]),glm::vec3(0.2,0.2,0.2),glm::vec3(0.7,0.7,0.7),1);
            glColor3f(cor1.x,cor1.y,cor1.z);
            glTexCoord2f(0,1);
            glVertex3f(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z);
            glm::vec3 cor2 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]),glm::vec3(0.2,0.2,0.2),glm::vec3(0.7,0.7,0.7),1);
            glColor3f(cor2.x,cor2.y,cor2.z);
            glTexCoord2f(1,1);
            glVertex3f(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y+1,tabuleiro[i].pos.z);
            glm::vec3 cor3 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]),glm::vec3(0.2,0.2,0.2),glm::vec3(0.7,0.7,0.7),1);
            glColor3f(cor3.x,cor3.y,cor3.z);
            glTexCoord2f(1,0);
            glVertex3f(tabuleiro[i].pos.x+1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z);
            glm::vec3 cor4 = aplicar_luz(glm::vec3(0,0,1),glm::vec3(tabuleiro[i].pos.x-1,tabuleiro[i].pos.y-1,tabuleiro[i].pos.z),glm::vec3(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]),glm::vec3(0.2,0.2,0.2),glm::vec3(0.7,0.7,0.7),1);
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
    glutPostRedisplay();
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
        bool moveu;
        if(foiSelecionado == 1){
            moveu = selecionar_possivel(xFinal,yFinal);
            if(!moveu){
                cout<<"errou";
                selecionado = pegar_quadrado(xFinal,yFinal);
                quant_possivel = 0;
                if(selecionado->situacao == 1){
                    buscar_possiveis(selecionado);
                }
            }
        }else if(foiSelecionado == 0){
            selecionado = pegar_quadrado(xFinal,yFinal);
            if(selecionado->situacao == 1){
                buscar_possiveis(selecionado);
            }
        }
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
        glBegin(GL_LINES);
            glColor3f(1,1,0.2);
            glVertex2f(selecionado->pos.x-1,selecionado->pos.y+1);
            glVertex2f(selecionado->pos.x+1,selecionado->pos.y+1);
            glVertex2f(selecionado->pos.x+1,selecionado->pos.y+1);
            glVertex2f(selecionado->pos.x+1,selecionado->pos.y-1);
            glVertex2f(selecionado->pos.x+1,selecionado->pos.y-1);
            glVertex2f(selecionado->pos.x-1,selecionado->pos.y-1);
            glVertex2f(selecionado->pos.x-1,selecionado->pos.y-1);
            glVertex2f(selecionado->pos.x-1,selecionado->pos.y+1);
        glEnd();
    }
    if(quant_possivel > 0){
        for(int i = 0;i< quant_possivel;i++){
            glBegin(GL_LINES);
                glColor3f(1,1,0.2);
                glVertex2f(possiveis[i]->pos.x-1,possiveis[i]->pos.y+1);
                glVertex2f(possiveis[i]->pos.x+1,possiveis[i]->pos.y+1);
                glVertex2f(possiveis[i]->pos.x+1,possiveis[i]->pos.y+1);
                glVertex2f(possiveis[i]->pos.x+1,possiveis[i]->pos.y-1);
                glVertex2f(possiveis[i]->pos.x+1,possiveis[i]->pos.y-1);
                glVertex2f(possiveis[i]->pos.x-1,possiveis[i]->pos.y-1);
                glVertex2f(possiveis[i]->pos.x-1,possiveis[i]->pos.y-1);
                glVertex2f(possiveis[i]->pos.x-1,possiveis[i]->pos.y+1);
            glEnd();
        }
    }
    glViewport(w/2,0,w,h);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90,1,1,40);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    if(turno == 2){
        look = glm::vec3(7,-2,4);
    }else{
        look = glm::vec3(9,18,4);
    }
    glm::mat4 camera = glm::lookAt(pos_camera,
                                   look,
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
    glutTimerFunc(1000/FPS,movimento_animado,0);
    glutMainLoop();
}
