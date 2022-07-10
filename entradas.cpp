#include <iostream>
#include <GL/gl.h>
#include <GL/glext.h>
#include<GL\glut.h>
#include<math.h>
#include<tabuleiro.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "pecas.h"
#include "iniciar_jogo.cpp"
#define FPS 60
using namespace std;
Quadrado * selecionado;
int ativar = 0;
Jogador* movido;
glm::vec3 mov;
glm::vec2 peca;
float t;
int turno = 2;
int foiSelecionado = 0;
Quadrado* possiveis[64];
int quant_possivel = 0;
void passar_turno(){
    delete(movido);
    ativar = 0;
    t = 0;
    if(turno = 2){
        turno = 1;
    }else{
        turno = 2;
    }
}
void movimentar(float x, float y){
    if(selecionado->jogador_ocupando == 2){
        if(selecionado->peca_ocupada.x == 6 && selecionado->peca_ocupada.y == 1){
            movido = &preto;
            mov = glm::vec3(x,y,0);
            peca = glm::vec2(6,1);
            ativar = 1;
        }
    }
    glutPostRedisplay();
}
bool checar_pontos_quadrado(float x_quadrado,float y_quadrado,float x_peca,float y_peca){
    if(x_quadrado - 1.0 <= x_peca && x_quadrado + 1.0 >= x_peca && y_quadrado - 1.0 <= y_peca && y_quadrado + 1.0 >= y_peca){
        return true;
    }
    return false;
}
Quadrado* pegar_quadrado(float x,float y){
    for(int i = 0;i < 64;i++){
        if(checar_pontos_quadrado(tabuleiro[i].pos.x,tabuleiro[i].pos.y,x,y)){
            foiSelecionado = 1;
            return &tabuleiro[i];
        }
    }
}

bool selecionar_possivel(float x,float y){
    for(int i = 0;i < quant_possivel;i++){
        if(checar_pontos_quadrado(possiveis[i]->pos.x,possiveis[i]->pos.y,x,y)){
            possiveis[i]->situacao = selecionado->situacao;
            possiveis[i]->peca_ocupada = selecionado->peca_ocupada;
            possiveis[i]->jogador_ocupando = selecionado->jogador_ocupando;
            movimentar(possiveis[i]->pos.x,possiveis[i]->pos.y);
            selecionado->situacao = 0;
            selecionado->peca_ocupada = glm::vec2(0,0);
            selecionado->jogador_ocupando = 0;
            foiSelecionado = 0;
            quant_possivel = 0;
            return true;
        }
    }
    return false;
    glutPostRedisplay();
}
Quadrado* buscar_quadrado_preciso(float x,float y){
    Quadrado* quadrado;
    for(int i = 0;i<64;i++){
        if(tabuleiro[i].pos.x == x && tabuleiro[i].pos.y == y){
           quadrado = &tabuleiro[i];
        }
    }
    return quadrado;
}
void buscar_possiveis(Quadrado* selecionado){
    if(turno == 1){
        if(selecionado->jogador_ocupando == 1){
            int xAtual = selecionado->pos.x;
            int yAtual = selecionado->pos.y;
            if(selecionado->peca_ocupada.x == 6){
                for(int i = 0;i < 2;i++){
                    xAtual -= 2;
                    possiveis[quant_possivel] = buscar_quadrado_preciso(xAtual,yAtual);
                    quant_possivel++;
                }
            }
        }
    }else if(turno == 2){
        if(selecionado->jogador_ocupando == 2){
            int xAtual = selecionado->pos.x;
            int yAtual = selecionado->pos.y;
            if(selecionado->peca_ocupada.x == 6){
                for(int i = 0;i < 2;i++){
                    xAtual += 2;
                    possiveis[quant_possivel] = buscar_quadrado_preciso(xAtual,yAtual);
                    quant_possivel++;
                }
            }
        }
    }
}
