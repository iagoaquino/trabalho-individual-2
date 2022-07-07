#include <iostream>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "objeto.h"
#ifndef LEITURA_H
#define LEITURA_H
using namespace std;
Objeto* ler_arquivo(){
    Objeto* obj = new(Objeto);
    int cont = 0;
    int cont_normal = 0;
    int cont_face = 0;
    FILE* file = fopen("w.obj","r");
    if(file == NULL){
        cout<<"erro na leitura"<<endl;
    }else{
        while(1){
            char linha[100];
            int res = fscanf(file,"%s",linha);
            if(res == EOF){
                break;
            }
            if(strcmp(linha,"v") == 0){
                Ponto p;
                fscanf(file, "%f %f %f\n", &p.coord.x, &p.coord.y, &p.coord.z );
                cout<<"x: "<<p.coord.x<<", y:"<<p.coord.y<<", z:"<<p.coord.z<<endl;
                obj->pontos[cont] = p;
                cont++;
            }else if(strcmp(linha,"vt") == 0){
                glm::vec2 tex;
                fscanf(file,"%f %f\n",&tex.x,&tex.y);
                cout<<" s:"<<tex.x<<", t:"<<tex.y<<endl;
            }else if(strcmp(linha,"vn") == 0){
                glm::vec3 normal;
                fscanf(file,"%f %f %f\n",&normal.x,&normal.y,&normal.z);
                obj->pontos[cont_normal].normal = normal;
                cont_normal++;
            }else if(strcmp(linha,"f") == 0){
                unsigned int vertice[3],textura[3],normal[3];
                fscanf(file," %d/%d/%d %d/%d/%d %d/%d/%d \n",&vertice[0],&textura[0],&normal[0],&vertice[1],&textura[1],&normal[1],&vertice[2],&textura[2],&normal[2]);
                cout<<" vertice1: "<<vertice[0]<<", vertice2:"<<vertice[1]<<", vertice3:"<<vertice[2]<<endl;
                obj->faces[cont_face].id_ponto_1 = vertice[0];
                obj->faces[cont_face].id_ponto_2 = vertice[1];
                obj->faces[cont_face].id_ponto_3 = vertice[2];
                cont_face++;
            }
        }
    }
    obj->quant_ponto = cont;
    obj->quant_lados = cont_face;
    cout<<"pontos:"<<endl;
    for(int i = 0;i<obj->quant_ponto;i++){
        cout<<" x: "<<obj->pontos[i].coord.x<<" y: "<<obj->pontos[i].coord.y<<" z: "<<obj->pontos[i].coord.z<<endl;
        cout<<"x normal:"<<obj->pontos[i].normal.x<<endl;
        cout<<"y normal:"<<obj->pontos[i].normal.y<<endl;
        cout<<"z normal:"<<obj->pontos[i].normal.z<<endl;
    }
    for(int i = 0;i<cont_face;i++){
        cout<<"ponto da face 1:"<<obj->faces[i].id_ponto_1<<endl;
        cout<<"ponto da face 2:"<<obj->faces[i].id_ponto_2<<endl;
        cout<<"ponto da face 3:"<<obj->faces[i].id_ponto_3<<endl;
    }
    return obj;
}
#endif // LEITURA_H
