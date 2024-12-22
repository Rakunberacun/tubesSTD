#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
#include <string>
#include <climits>
using namespace std;

// Define macros for easier access to node properties
#define namaStasiun(S) S->namaStasiun
#define nextStasiun(S) S->nextStasiun
#define firstStasiun(G) G.firstStasiun
#define firstRute(S) S->firstRute
#define destStasiunID(R) R->destStasiunID
#define weight(R) R->weight
#define nextRute(R) R->nextRute

struct Rute;
struct stasiunTransit;

typedef stasiunTransit *adrStasiun;
typedef Rute *adrRute;

struct stasiunTransit {
    string namaStasiun; // Nama stasiun sebagai ID unik
    adrStasiun nextStasiun; // Pointer ke stasiun berikutnya
    adrRute firstRute; // Pointer ke rute pertama dari stasiun ini
};

struct Rute {
    string destStasiunID; // Nama stasiun tujuan
    int weight; // Bobot rute
    adrRute nextRute; // Pointer ke rute berikutnya
};

struct Graph {
    adrStasiun firstStasiun; // Pointer ke stasiun pertama dalam graph
};

// Fungsi dan prosedur untuk operasi pada graph
void createStasiun(string newNamaStasiun, adrStasiun &S);
void initGraph(Graph &G);
void addStasiun(Graph &G, string newNamaStasiun);
void deleteStasiun(Graph &G, string namaStasiun);
void addRute(Graph &G, string fromNamaStasiun, string toNamaStasiun, int weight);
bool findStasiun(Graph &G, string namaStasiun, adrStasiun &S);
bool findRute(Graph &G, string fromNamaStasiun, string toNamaStasiun, adrRute &R);
void displayGraph(Graph &G);
void shortestRoute(Graph &G, string startNama, string endNama);

#endif // GRAPH_H_INCLUDED
