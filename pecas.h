#include "glm/glm.hpp"
#include "glm/ext.hpp"
#ifndef PECAS_H
#define PECAS_H
typedef struct torre{
    int id;
    glm::vec2 pos;
}Torre;
typedef struct peao{
    int id;
    float x,y,z;
    int turnos;
}Peao;
typedef struct bispo{
    int id;
    float x,y,z;
}Bispo;
typedef struct cavalo{
    int id;
    float x,y,z;
}Cavalo;
typedef struct rei{
    int id;
    float x,y,z;
    int situacao;
}Rei;
typedef struct rainha{
    int id;
    float x,y,z;
}Rainha;

typedef struct jogador{
    struct rainha rainha;
    struct rei rei;
    struct peao peoes[8];
    struct torre torres[2];
    struct bispo bispos[2];
    struct cavalo cavalos[2];
}Jogador;
typedef struct quadrado{
    float x,y,z;
    float color[3];
}Quadrado;
#endif // PECAS_H
