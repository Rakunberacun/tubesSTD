#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>

using namespace std;

#define namaStasiun(S) S->namaStasiun
#define nextStasiun(S) S->nextStasiun
#define firstStasiun(G) G.firstStasiun
#define firstRute(S) S->firstRute
#define destStasiunID(R) R->destStasiunID
#define weight(R) R->weight
#define nextRute(R) R->nextRute
#define sedangMaintenance(R) R->sedangMaintenance

struct Rute;
struct stasiunTransit;

typedef stasiunTransit *adrStasiun;
typedef Rute *adrRute;

struct stasiunTransit {
    string namaStasiun;
    adrStasiun nextStasiun;
    adrRute firstRute;
};

struct Rute {
    string destStasiunID;
    int weight;
    adrRute nextRute;
    bool sedangMaintenance;
};

struct Graph {
    adrStasiun firstStasiun;
};

void createStasiun(string newNamaStasiun, adrStasiun &S);
void initGraph(Graph &G);
void addStasiun(Graph &G, string newNamaStasiun);
void deleteStasiun(Graph &G, string namaStasiun);
void addRute(Graph &G, string fromNamaStasiun, string toNamaStasiun, int weight, bool sedangMaintenance);
bool isRuteExist(Graph &G, string fromNamaStasiun, string toNamaStasiun);
bool findStasiun(Graph &G, string namaStasiun, adrStasiun &S);
bool findRute(Graph &G, string fromNamaStasiun, string toNamaStasiun, adrRute &R);
void displayGraph(Graph &G);
void shortestRoute(Graph &G, string startID, string endID);
void dfsShortestRoute(adrStasiun current, string endID, int currentWeight, int &minWeight, string path, string &shortestPath, Graph &G, string visited[], int &visitedCount);
void reopenRoute(Graph &G, string &fromNamaStasiun, string &toNamaStasiun);
void startMaintenance(Graph &G, string fromNamaStasiun, string toNamaStasiun);

#endif // GRAPH_H_INCLUDED
