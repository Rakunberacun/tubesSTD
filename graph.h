#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

#define idStasiun(S) S->idStasiun
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
    string idStasiun;
    adrStasiun nextStasiun;
    adrRute firstRute;
};

struct Rute {
    string destStasiunID;
    int weight;
    adrRute nextRute;
};

struct Graph {
    adrStasiun firstStasiun;
};

void createStasiun(string newStasiunID, adrStasiun &S);
void initGraph(Graph &G);
void addStasiun(Graph &G, string newStasiunID);
void buildGraph(Graph &G);
void addRute(Graph &G, string fromStasiunID, string toStasiunID, int weight);
bool findStasiun(Graph &G, string stasiunID, adrStasiun &S);
bool findRute(Graph &G, string fromStasiunID, string toStasiunID, adrRute &R);
void displayGraph(Graph &G);
void shortestRoute(Graph &G, string startID, string endID);
void removeStasiun(Graph &G, string stasiunID);
void removeRute(Graph &G, string fromStasiunID, string toStasiunID);

#endif // GRAPH_H_INCLUDED
