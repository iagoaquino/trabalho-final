#include <iostream>
#include<GL\glut.h>
#include"pecas.h"
#include<math.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"

#define FPS 60
using namespace std;
Jogador branco;
Jogador preto;
int w = 1200;
int h = 600;
int turno = 0;
int vencerdor = 0;
float t = 0;
Quadrado tabuleiro[64];
Quadrado possiveis[64];
int cont_possiveis;
int pos_peca;
int tipo;
glm::vec2 ponto_final;
int movimento = 0;

Quadrado selecionado;
int foiSelecionado = 0;
void criar_pecas_brancas(){
    //torres
    branco.torres[0].pos.x = 1;
    branco.torres[0].pos.y = 1;
    branco.torres[1].pos.x = 15;
    branco.torres[1].pos.y = 1;


    //cavalos
    branco.cavalos[0].x = 3;
    branco.cavalos[0].y = 1;
    branco.cavalos[0].z = 0;
    branco.cavalos[1].x = 13;
    branco.cavalos[1].y = 1;
    branco.cavalos[1].z = 0;

    //bispos
    branco.bispos[0].x = 5;
    branco.bispos[0].y = 1;
    branco.bispos[0].z = 0;
    branco.bispos[1].x = 11;
    branco.bispos[1].y = 1;
    branco.bispos[1].z = 0;
    //rei
    branco.rei.x = 7;
    branco.rei.y = 1;
    branco.rei.z = 0;
    branco.rei.situacao = 0;
    //rainha
    branco.rainha.x = 9;
    branco.rainha.y = 1;
    branco.rainha.z = 0;
}
void desenhar_branco(){
    glBegin(GL_QUADS);
        glColor3f(0.5,0.5,1);
        glVertex2f(branco.torres[0].pos.x,branco.torres[0].pos.y + 0.5);
        glVertex2f(branco.torres[0].pos.x+0.5,branco.torres[0].pos.y);
        glVertex2f(branco.torres[0].pos.x,branco.torres[0].pos.y - 0.5);
        glVertex2f(branco.torres[0].pos.x - 0.5,branco.torres[0].pos.y);
    glEnd();
}
void movimentar(int v){
    glutTimerFunc(1000.0/FPS,movimentar,0);
    if(tipo == 1){
        if(t < 1){
            t+=0.001;
            branco.torres[pos_peca].pos = (1-t)*branco.torres[pos_peca].pos + (t*ponto_final);
            cout<<branco.torres[pos_peca].pos.y<<endl;
        }
    }
    glutPostRedisplay();
}
void iniciar_tabuleiro(){
    glClearColor(1.0,1.0,1.0,1.0);
    int pos = 0;
    int cont = 0;
    float x = 1;
    float y = 1;
    float z = 0;
    for(int i = 0;i < 8;i++){
        for(int j = 0;j < 8;j++){
            Quadrado quadrado;
            quadrado.x = x;
            quadrado.y = y;
            quadrado.z = z;
            if(cont % 2 == 0){
                quadrado.color[0] = 1;
                quadrado.color[1] = 1;
                quadrado.color[2] = 1;
            }else{
                quadrado.color[0] = 0;
                quadrado.color[1] = 0;
                quadrado.color[2] = 0;
            }
            tabuleiro[pos] = quadrado;
            pos++;
            cont++;
            x += 2;
        }
        x = 1;
        y += 2;
        cont++;
    }
}
void desenhaTabuleiro(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,16.0,0,16.0,-1,1);
    glMatrixMode(GL_MODELVIEW);
    for(int i = 0;i < 64;i++){
        glBegin(GL_QUADS);
            glColor3f(tabuleiro[i].color[0],tabuleiro[i].color[1],tabuleiro[i].color[2]);
            glVertex2f(tabuleiro[i].x-1,tabuleiro[i].y+1);
            glVertex2f(tabuleiro[i].x+1,tabuleiro[i].y+1);
            glVertex2f(tabuleiro[i].x+1,tabuleiro[i].y-1);
            glVertex2f(tabuleiro[i].x-1,tabuleiro[i].y-1);
        glEnd();
    }
    if(foiSelecionado == 1){
        glLineWidth(5);
        glBegin(GL_QUADS);
            glColor3f(1,1,0.2);
            glVertex2f(selecionado.x-1,selecionado.y+1);
            glVertex2f(selecionado.x+1,selecionado.y+1);
            glVertex2f(selecionado.x+1,selecionado.y-1);
            glVertex2f(selecionado.x-1,selecionado.y-1);
        glEnd();
        for(int i = 0;i < cont_possiveis;i++){
            glBegin(GL_QUADS);
                glColor3f(1,1,0);
                glVertex2f(possiveis[i].x-1,possiveis[i].y+1);
                glVertex2f(possiveis[i].x+1,possiveis[i].y+1);
                glVertex2f(possiveis[i].x+1,possiveis[i].y-1);
                glVertex2f(possiveis[i].x-1,possiveis[i].y-1);
            glEnd();
            glPolygonMode(GL_BACK,GL_LINE);
            glBegin(GL_QUADS);
                glColor3f(0,0,0);
                glVertex2f(possiveis[i].x-1,possiveis[i].y+1);
                glVertex2f(possiveis[i].x+1,possiveis[i].y+1);
                glVertex2f(possiveis[i].x+1,possiveis[i].y-1);
                glVertex2f(possiveis[i].x-1,possiveis[i].y-1);
            glEnd();
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

        }
    }
    desenhar_branco();
    glFlush();
}
bool checar_pontos_quadrado(float x_quadrado,float y_quadrado,float x_peca,float y_peca){
    if(x_quadrado - 1.0 <= x_peca && x_quadrado + 1.0 >= x_peca && y_quadrado - 1.0 <= y_peca && y_quadrado + 1.0 >= y_peca){
        return true;
    }
    return false;
}
void passar_turno(){
    if(turno == 0){
        foiSelecionado = 0;
        cont_possiveis = 0;
        turno = 1;
    }else{
        foiSelecionado = 0;
        cont_possiveis = 0;
        turno = 0;
    }
}
void checar_possiveis(quadrado escolhido){
    if(turno == 0){
        for(int i =0; i < 2;i++){
            if(escolhido.x == branco.torres[i].pos.x && escolhido.y == branco.torres[i].pos.y){
                cont_possiveis = 0;
                int x = escolhido.x;
                int y = escolhido.y;
                while(x < 16){
                    for(int i =0;i < 64;i++){
                        if(tabuleiro[i].x == x && tabuleiro[i].y == y){
                            possiveis[cont_possiveis] = tabuleiro[i];
                            cont_possiveis++;
                        }
                    }
                    x+= 2;
                }
                x = escolhido.x;
                y = escolhido.y;
                while(y < 16){
                    for(int i =0;i < 64;i++){
                        if(tabuleiro[i].x == x && tabuleiro[i].y == y){
                            possiveis[cont_possiveis] = tabuleiro[i];
                            cont_possiveis++;
                        }
                    }
                    y+= 2;
                }
            }else{
                cont_possiveis = 0;
            }
            break;
        }
    }
}
Quadrado pegar_quadrado(float x,float y){
    for(int i = 0;i < 64;i++){
        if(checar_pontos_quadrado(tabuleiro[i].x,tabuleiro[i].y,x,y)){
            foiSelecionado = 1;
            return tabuleiro[i];
        }
    }
}
void mostrar_tabuleiro(){
    for(int i = 0; i < 64;i++){
        cout <<" x: "<< tabuleiro[i].x<<endl;
        cout <<" y: "<< tabuleiro[i].y<<endl;
    }
}
void pegar_click(int button,int status, int x,int y){
    float xFinal = (float)(16*x)/w;
    float yFinal = (float)(16*(h-y))/h;
    if(foiSelecionado == 0){
        if(button == GLUT_LEFT_BUTTON && status == GLUT_UP){
            selecionado = pegar_quadrado(xFinal,yFinal);
            checar_possiveis(selecionado);
        }
    }else{
        if(button == GLUT_LEFT_BUTTON && status == GLUT_UP){
            for(int i = 0;i < cont_possiveis;i++){
                if(checar_pontos_quadrado(possiveis[i].x,possiveis[i].y,xFinal,yFinal)){
                    if(turno == 0){
                        for(int j = 0;j< 2;j++){
                            if(branco.torres[j].pos.x == selecionado.x && branco.torres[j].pos.y == selecionado.y){
                                ponto_final = glm::vec2(possiveis[i].x,possiveis[i].y);
                                movimento = 1;
                                tipo = 1;
                                passar_turno();
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}
int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,20);
    glutInitWindowSize(1200,600);
    glutCreateWindow("Trabalho 1");
    iniciar_tabuleiro();
    criar_pecas_brancas();
    //mostrar_tabuleiro();
    glutDisplayFunc(desenhaTabuleiro);
    glutMouseFunc(pegar_click);
    glutTimerFunc(1000/FPS,movimentar,0);
    glutMainLoop();
}
