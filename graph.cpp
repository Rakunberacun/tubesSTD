#include "graph.h"
#include <iostream>
#include <string>
#include <map>         // Untuk std::map
#include <functional>  // Untuk std::function
#include <climits>     // Untuk INT_MAX
using namespace std;

// Membuat stasiun baru
void createStasiun(string newNamaStasiun, adrStasiun &S) {
    S = new stasiunTransit;
    namaStasiun(S) = newNamaStasiun;
    nextStasiun(S) = nullptr;
    firstRute(S) = nullptr;
}

// Inisialisasi graph kosong
void initGraph(Graph &G) {
    firstStasiun(G) = nullptr;
}

// Menambahkan stasiun ke dalam graph
void addStasiun(Graph &G, string newNamaStasiun) {
    adrStasiun S;
    createStasiun(newNamaStasiun, S);
    nextStasiun(S) = firstStasiun(G);
    firstStasiun(G) = S;
}

// Menghapus stasiun dari graph
void deleteStasiun(Graph &G, string namaStasiun) {
    adrStasiun prev = nullptr, curr = firstStasiun(G);

    while (curr != nullptr && namaStasiun(curr) != namaStasiun) {
        prev = curr;
        curr = nextStasiun(curr);
    }

    if (curr != nullptr) {
        if (prev == nullptr) {
            firstStasiun(G) = nextStasiun(curr);
        } else {
            nextStasiun(prev) = nextStasiun(curr);
        }

        while (firstRute(curr) != nullptr) {
            adrRute temp = firstRute(curr);
            firstRute(curr) = nextRute(temp);
            delete temp;
        }

        delete curr;
    }
}

// Menambahkan rute antara dua stasiun
void addRute(Graph &G, string fromNamaStasiun, string toNamaStasiun, int weight) {
    adrStasiun fromStasiun, toStasiun;
    if (findStasiun(G, fromNamaStasiun, fromStasiun) && findStasiun(G, toNamaStasiun, toStasiun)) {
        adrRute R = new Rute;
        destStasiunID(R) = toNamaStasiun;
        weight(R) = weight;
        nextRute(R) = firstRute(fromStasiun);
        firstRute(fromStasiun) = R;
    }
}

// Mencari stasiun berdasarkan nama
bool findStasiun(Graph &G, string namaStasiun, adrStasiun &S) {
    S = firstStasiun(G);
    while (S != nullptr) {
        if (namaStasiun(S) == namaStasiun) {
            return true;
        }
        S = nextStasiun(S);
    }
    S = nullptr;
    return false;
}

// Menampilkan graph
void displayGraph(Graph &G) {
    adrStasiun S = firstStasiun(G);
    while (S != nullptr) {
        cout << "Stasiun " << namaStasiun(S) << ": ";
        adrRute R = firstRute(S);
        while (R != nullptr) {
            cout << " -> " << destStasiunID(R) << " (Weight: " << weight(R) << ")";
            R = nextRute(R);
        }
        cout << endl;
        S = nextStasiun(S);
    }
}

void dfsShortestRoute(adrStasiun current, string endID, int currentWeight, int &minWeight, string path, string &shortestPath, Graph &G, string visited[], int &visitedCount) {
    if (current == NULL) return;

    // Mark the current station as visited
    visited[visitedCount++] = namaStasiun(current);

    // Append the current station to the path
    path += namaStasiun(current) + " ";

    // If we reached the destination, check if this is the shortest path
    if (namaStasiun(current) == endID) {
        if (currentWeight < minWeight) {
            minWeight = currentWeight;
            shortestPath = path;
        }
    } else {
        // Explore all adjacent stations
        adrRute r = firstRute(current);
        while (r != NULL) {
            bool alreadyVisited = false;
            for (int i = 0; i < visitedCount; i++) {
                if (visited[i] == destStasiunID(r)) {
                    alreadyVisited = true;
                    break;
                }
            }

            if (!alreadyVisited) {
                // Find the destination station pointer
                adrStasiun destStasiun;
                if (findStasiun(G, destStasiunID(r), destStasiun)) {
                    dfsShortestRoute(destStasiun, endID, currentWeight + weight(r), minWeight, path, shortestPath, G, visited, visitedCount);
                }
            }
            r = nextRute(r);
        }
    }

    // Backtrack: remove the station from visited
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

    int minWeight = INT_MAX; // Initialize the shortest distance as infinity
    string shortestPath = "";
    string visited[100]; // Array to keep track of visited stations (maximum 100 stations)
    int visitedCount = 0; // Counter for the number of visited stations

    // Start DFS from the start station
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
    if (findStasiun(G, fromNamaStasiun, S)) { // Cari stasiun asal
        R = firstRute(S); // Mulai dari rute pertama
        while (R != nullptr) {
            if (destStasiunID(R) == toNamaStasiun) { // Cek apakah tujuan cocok
                return true;
            }
            R = nextRute(R); // Lanjut ke rute berikutnya
        }
    }
    R = nullptr; // Set nullptr jika tidak ditemukan
    return false;
}

