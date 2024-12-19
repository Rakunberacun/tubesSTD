#include "graph.h"

// Membuat stasiun baru
void createStasiun(string newStasiunID, adrStasiun &S) {
    S = new stasiunTransit;
    S->idStasiun = newStasiunID;
    S->nextStasiun = nullptr;
    S->firstRute = nullptr;
}

// Inisialisasi graph kosong
void initGraph(Graph &G) {
    G.firstStasiun = nullptr;
}

// Menambahkan stasiun ke dalam graph
void addStasiun(Graph &G, string newStasiunID) {
    adrStasiun S;
    createStasiun(newStasiunID, S);
    S->nextStasiun = G.firstStasiun;
    G.firstStasiun = S;
}

// Menambahkan rute antara dua stasiun
void addRute(Graph &G, string fromStasiunID, string toStasiunID, int weight) {
    adrStasiun fromStasiun, toStasiun;
    if (findStasiun(G, fromStasiunID, fromStasiun) && findStasiun(G, toStasiunID, toStasiun)) {
        adrRute R = new Rute;
        R->destStasiunID = toStasiunID;
        R->weight = weight;
        R->nextRute = fromStasiun->firstRute;
        fromStasiun->firstRute = R;
    } else {
        cout << "Stasiun tidak ditemukan!" << endl;
    }
}

// Mencari stasiun berdasarkan ID
bool findStasiun(Graph &G, string stasiunID, adrStasiun &S) {
    S = G.firstStasiun;
    while (S != nullptr) {
        if (S->idStasiun == stasiunID) {
            return true; // Langsung keluar saat stasiun ditemukan
        }
        S = S->nextStasiun;
    }
    return false; // Tidak ditemukan
}


// Mencari rute berdasarkan stasiun asal dan tujuan
bool findRute(Graph &G, string fromStasiun, string toStasiun, adrRute &R) {
    adrStasiun S = G.firstStasiun;
    while (S != nullptr) {
        if (S->idStasiun == fromStasiun) { // Temukan stasiun asal
            R = S->firstRute;
            while (R != nullptr) { // Iterasi melalui semua rute dari stasiun asal
                if (R->destStasiunID == toStasiun) {
                    return true; // Rute ditemukan
                }
                R = R->nextRute;
            }
            break; // Keluar jika semua rute dari stasiun asal telah diperiksa
        }
        S = S->nextStasiun;
    }
    R = nullptr; // Rute tidak ditemukan
    return false;
}


// Menampilkan graph
void displayGraph(Graph &G) {
    adrStasiun S = G.firstStasiun;
    while (S != nullptr) {
        cout << "Stasiun " << S->idStasiun << ": ";
        adrRute R = S->firstRute;
        while (R != nullptr) {
            cout << " -> " << R->destStasiunID << " (Weight: " << R->weight << ")";
            R = R->nextRute;
        }
        cout << endl;
        S = S->nextStasiun;
    }
}

// Mencari rute terpendek dengan DFS
void shortestRoute(Graph &G, string startID, string endID) {
    adrStasiun startStasiun;
    if (!findStasiun(G, startID, startStasiun)) {
        cout << "Stasiun awal tidak ditemukan." << endl;
        return;
    }

    const int MAX_WEIGHT = 999999; // Pengganti INT_MAX
    int minWeight = MAX_WEIGHT;

    // Array untuk menandai kunjungan stasiun
    const int MAX_STATIONS = 100; // Jumlah maksimum stasiun
    bool visited[MAX_STATIONS] = {false};

    // Fungsi lokal untuk DFS
    auto DFS = [&](adrStasiun S, int currentWeight, auto &DFSRef) -> void {
        if (S->idStasiun == endID) {
            if (currentWeight < minWeight) {
                minWeight = currentWeight;
            }
            return;
        }

        // Tandai stasiun ini telah dikunjungi
        int index = stoi(S->idStasiun); // Asumsi idStasiun dapat diubah ke indeks integer
        visited[index] = true;

        adrRute R = S->firstRute;
        while (R != nullptr) {
            int destIndex = stoi(R->destStasiunID); // Konversi ke indeks
            if (!visited[destIndex]) {
                adrStasiun destStasiun = G.firstStasiun;
                while (destStasiun != nullptr && destStasiun->idStasiun != R->destStasiunID) {
                    destStasiun = destStasiun->nextStasiun;
                }
                if (destStasiun != nullptr) {
                    DFSRef(destStasiun, currentWeight + R->weight, DFSRef);
                }
            }
            R = R->nextRute;
        }

        // Kembalikan status tidak dikunjungi
        visited[index] = false;
    };

    // Mulai DFS dari stasiun awal
    DFS(startStasiun, 0, DFS);

    if (minWeight == MAX_WEIGHT) {
        cout << "Tidak ada jalur dari " << startID << " ke " << endID << "." << endl;
    } else {
        cout << "Jalur terpendek dari " << startID << " ke " << endID << " memiliki bobot: " << minWeight << endl;
    }
}

// Menghapus stasiun dari graph
void removeStasiun(Graph &G, string stasiunID) {
    adrStasiun prev = nullptr, S = G.firstStasiun;
    while (S != nullptr && S->idStasiun != stasiunID) {
        prev = S;
        S = S->nextStasiun;
    }
    if (S != nullptr) {
        if (prev == nullptr) {
            G.firstStasiun = S->nextStasiun;
        } else {
            prev->nextStasiun = S->nextStasiun;
        }
        delete S;
    }
}

// Menghapus rute dari graph
void removeRute(Graph &G, string fromStasiunID, string toStasiunID) {
    adrStasiun S;
    if (findStasiun(G, fromStasiunID, S)) {
        adrRute prev = nullptr, R = S->firstRute;
        while (R != nullptr && R->destStasiunID != toStasiunID) {
            prev = R;
            R = R->nextRute;
        }
        if (R != nullptr) {
            if (prev == nullptr) {
                S->firstRute = R->nextRute;
            } else {
                prev->nextRute = R->nextRute;
            }
            delete R;
        }
    }
}
