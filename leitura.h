#include <iostream>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#ifndef LEITURA_H
#define LEITURA_H
using namespace std;
void ler_arquivo(){
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
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
                cout<<"x: "<<vertex.x<<", y:"<<vertex.y<<", z:"<<vertex.z<<endl;
            }else if(strcmp(linha,"vt") == 0){
                glm::vec2 tex;
                fscanf(file,"%f %f\n",&tex.x,&tex.y);
                cout<<" s:"<<tex.x<<", t:"<<tex.y<<endl;
            }else if(strcmp(linha,"vn") == 0){
                glm::vec3 normal;
                fscanf(file,"%f %f %f\n",&normal.x,&normal.y,&normal.z);
                cout<<" x: "<<normal.x<<", y:"<<normal.y<<" , z: "<<normal.z<<endl;
            }else if(strcmp(linha,"f") == 0){
                unsigned int vertice[3],textura[3],normal[3];
                fscanf(file," %d/%d/%d %d/%d/%d %d/%d/%d \n",&vertice[0],&textura[0],&normal[0],&vertice[1],&textura[1],&normal[1],&vertice[2],&textura[2],&normal[2]);
                cout<<" vertice1: "<<vertice[0]<<", vertice2:"<<vertice[1]<<", vertice3:"<<vertice[2]<<endl;
            }
        }
    }
}
#endif // LEITURA_H
