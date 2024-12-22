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

// Mencari rute terpendek menggunakan DFS
void shortestRoute(Graph &G, string startNama, string endNama) {
    adrStasiun startStasiun;
    if (!findStasiun(G, startNama, startStasiun)) {
        cout << "Stasiun awal tidak ditemukan." << endl;
        return;
    }

    const int MAX_WEIGHT = INT_MAX;
    int minWeight = MAX_WEIGHT;

    map<string, bool> visited;

    function<void(adrStasiun, int)> DFS = [&](adrStasiun S, int currentWeight) {
        if (namaStasiun(S) == endNama) {
            minWeight = min(minWeight, currentWeight);
            return;
        }

        visited[namaStasiun(S)] = true;

        adrRute R = firstRute(S);
        while (R != nullptr) {
            if (!visited[destStasiunID(R)]) {
                adrStasiun destStasiun;
                if (findStasiun(G, destStasiunID(R), destStasiun)) {
                    DFS(destStasiun, currentWeight + weight(R));
                }
            }
            R = nextRute(R);
        }

        visited[namaStasiun(S)] = false;
    };

    DFS(startStasiun, 0);

    if (minWeight == MAX_WEIGHT) {
        cout << "Tidak ada jalur dari " << startNama << " ke " << endNama << "." << endl;
    } else {
        cout << "Jalur terpendek dari " << startNama << " ke " << endNama << " memiliki bobot: " << minWeight << endl;
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

