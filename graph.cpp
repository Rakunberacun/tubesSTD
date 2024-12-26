#include "graph.h"

void createStasiun(string newNamaStasiun, adrStasiun &S) {
    S = new stasiunTransit;
    namaStasiun(S) = newNamaStasiun;
    nextStasiun(S) = NULL;
    firstRute(S) = NULL;
}

void initGraph(Graph &G) {
    firstStasiun(G) = NULL;
}

void addStasiun(Graph &G, string newNamaStasiun) {
    adrStasiun S;
    createStasiun(newNamaStasiun, S);
    nextStasiun(S) = firstStasiun(G);
    firstStasiun(G) = S;
}

void deleteStasiun(Graph &G, string namaStasiun) {
    adrStasiun prev = NULL, curr = firstStasiun(G);

    while (curr != NULL && namaStasiun(curr) != namaStasiun) {
        prev = curr;
        curr = nextStasiun(curr);
    }

    if (curr != NULL) {
        if (prev == NULL) {
            firstStasiun(G) = nextStasiun(curr);
        } else {
            nextStasiun(prev) = nextStasiun(curr);
        }

        while (firstRute(curr) != NULL) {
            adrRute temp = firstRute(curr);
            firstRute(curr) = nextRute(temp);
            delete temp;
        }

        delete curr;
    }
}

bool isRuteExist(Graph &G, string fromNamaStasiun, string toNamaStasiun) {
    adrStasiun fromStasiun;
    adrRute R;

    // Cek apakah stasiun asal ada
    if (findStasiun(G, fromNamaStasiun, fromStasiun)) {
        // Cari apakah rute sudah ada untuk stasiun asal
        R = firstRute(fromStasiun);
        while (R != NULL) {
            if (destStasiunID(R) == toNamaStasiun) {
                return true;  // Rute sudah ada
            }
            R = nextRute(R);
        }
    }
    return false;  // Rute tidak ditemukan
}

void addRute(Graph &G, string fromNamaStasiun, string toNamaStasiun, int weight, bool sedangMaintenance) {
    adrStasiun fromStasiun, toStasiun;
    if (findStasiun(G, fromNamaStasiun, fromStasiun) && findStasiun(G, toNamaStasiun, toStasiun)) {
        adrRute R = new Rute;
        destStasiunID(R) = toNamaStasiun;
        weight(R) = weight;
        sedangMaintenance(R) = false;
        nextRute(R) = firstRute(fromStasiun);
        firstRute(fromStasiun) = R;
    }
}

bool findStasiun(Graph &G, string namaStasiun, adrStasiun &S) {
    S = firstStasiun(G);
    while (S != NULL) {
        if (namaStasiun(S) == namaStasiun) {
            return true;
        }
        S = nextStasiun(S);
    }
    S = NULL;
    return false;
}

void displayGraph(Graph &G) {
    adrStasiun S = firstStasiun(G);
    while (S != NULL) {
        cout << "Stasiun " << namaStasiun(S) << ": ";
        adrRute R = firstRute(S);
        while (R != NULL) {
            cout << " -> " << destStasiunID(R);
            if (sedangMaintenance(R)) {
                cout << " (Sedang Maintenance)";
            } else {
                cout << " (Weight: " << weight(R) << ")";
            }
            R = nextRute(R);
        }
        cout << endl;
        cout << endl;
        S = nextStasiun(S);
    }
}



void dfsShortestRoute(adrStasiun current, string endID, int currentWeight, int &minWeight, string path, string &shortestPath, Graph &G, string visited[], int &visitedCount) {
    if (current == NULL) return;

    visited[visitedCount++] = namaStasiun(current);

    if (!path.empty()) {
        path += " -> ";
    }
    path += namaStasiun(current);

    if (namaStasiun(current) == endID) {
        if (currentWeight < minWeight) {
            minWeight = currentWeight;
            shortestPath = path;
        }
    } else {
        adrRute r = firstRute(current);
        while (r != NULL) {
            bool alreadyVisited = false;
            for (int i = 0; i < visitedCount; i++) {
                if (visited[i] == destStasiunID(r)) {
                    alreadyVisited = true;
                    break;
                }
            }

            if (!alreadyVisited && !sedangMaintenance(r)) {
                adrStasiun destStasiun;
                if (findStasiun(G, destStasiunID(r), destStasiun)) {
                    dfsShortestRoute(destStasiun, endID, currentWeight + weight(r), minWeight, path, shortestPath, G, visited, visitedCount);
                }
            }
            r = nextRute(r);
        }
    }

    visitedCount--;
}

void shortestRoute(Graph &G, string startID, string endID) {
    adrStasiun start;
    if (!findStasiun(G, startID, start)) {
        cout << "Stasiun awal tidak ditemukan." << endl;
        return;
    }

    adrStasiun end;
    if (!findStasiun(G, endID, end)) {
        cout << "Stasiun tujuan tidak ditemukan." << endl;
        return;
    }

    int minWeight = INT_MAX;
    string shortestPath = "";
    string visited[100];
    int visitedCount = 0;

    dfsShortestRoute(start, endID, 0, minWeight, "", shortestPath, G, visited, visitedCount);

    if (minWeight == INT_MAX) {
        cout << "Tidak ada rute dari " << startID << " ke " << endID << "." << endl;
    } else {
        cout << "Rute terpendek dari " << startID << " ke " << endID << " memiliki berat: " << minWeight << endl;
        cout << "Rute: " << shortestPath << endl;
    }
}

bool findRute(Graph &G, string fromNamaStasiun, string toNamaStasiun, adrRute &R) {
    adrStasiun S;
    if (findStasiun(G, fromNamaStasiun, S)) {
        R = firstRute(S);
        while (R != NULL) {
            if (destStasiunID(R) == toNamaStasiun) {
                return true;
            }
            R = nextRute(R);
        }
    }
    R = NULL;
    return false;
}

void startMaintenance(Graph &G, string fromNamaStasiun, string toNamaStasiun) {
    adrRute R;
    if (findRute(G, fromNamaStasiun, toNamaStasiun, R)) {
        if (!sedangMaintenance(R)) {
            sedangMaintenance(R) = true;
            cout << "Rute dari " << fromNamaStasiun << " ke " << toNamaStasiun << " sedang dalam maintenance." << endl;
        } else {
            cout << "Rute sudah dalam maintenance." << endl;
        }
    } else {
        cout << "Rute tidak ditemukan." << endl;
    }
}

void reopenRoute(Graph &G, string &fromNamaStasiun, string &toNamaStasiun) {
    adrRute R;
    if (findRute(G, fromNamaStasiun, toNamaStasiun, R)) {
        if (sedangMaintenance(R)) {
            sedangMaintenance(R) = false;
            cout << "Rute dari " << fromNamaStasiun << " ke " << toNamaStasiun << " telah dibuka kembali." << endl;
        } else {
            cout << "Rute dari " << fromNamaStasiun << " ke " << toNamaStasiun << " tidak sedang dalam maintenance." << endl;
        }
    } else {
        cout << "Rute dari " << fromNamaStasiun << " ke " << toNamaStasiun << " tidak ditemukan." << endl;
    }
}
