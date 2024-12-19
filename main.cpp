#include "graph.h"

int main() {
    Graph G;
    initGraph(G); // Inisialisasi graph

    // Tambahkan beberapa stasiun dan rute untuk contoh
    addStasiun(G, "Tanah Abang");
    addStasiun(G, "Manggarai");
    addStasiun(G, "Jakarta Kota");
    addStasiun(G, "Bogor");
    addRute(G, "Tanah Abang", "Manggarai", 10);
    addRute(G, "Manggarai", "Jakarta Kota", 15);
    addRute(G, "Tanah Abang", "Bogor", 25);
    addRute(G, "Bogor", "Jakarta Kota", 5);

    int choice;
    do {
        cout << "\n==== Menu Graph ====" << endl;
        cout << "1. Menunjukkan semua graph" << endl;
        cout << "2. Mencari stasiun" << endl;
        cout << "3. Mencari rute" << endl;
        cout << "4. Mencari rute terpendek" << endl;
        cout << "9. Exit Program" << endl;
        cout << "Pilihan: ";

        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\n== Menampilkan Graph ==" << endl;
                displayGraph(G);
                break;
            }
            case 2: {
            string stasiunID;
            cout << "\nMasukkan ID stasiun yang ingin dicari: ";
            cin >> stasiunID;
            adrStasiun S = nullptr; // Inisialisasi dengan nullptr
            if (findStasiun(G, stasiunID, S)) {
                cout << "Stasiun " << stasiunID << " ditemukan." << endl;
            } else {
                cout << "Stasiun " << stasiunID << " tidak ditemukan." << endl;
            }
            break;
            }
            case 3: {
            string fromStasiun, toStasiun;
            cout << "\nMasukkan ID stasiun asal: ";
            cin >> fromStasiun;
            cout << "Masukkan ID stasiun tujuan: ";
            cin >> toStasiun;
            adrRute R = nullptr; // Inisialisasi dengan nullptr
            if (findRute(G, fromStasiun, toStasiun, R)) {
                cout << "Rute ditemukan dengan bobot: " << R->weight << endl;
            } else {
                cout << "Rute dari " << fromStasiun << " ke " << toStasiun << " tidak ditemukan." << endl;
            }
            break;
            }
            case 4: {
                string startID, endID;
                cout << "\nMasukkan ID stasiun asal: ";
                cin >> startID;
                cout << "Masukkan ID stasiun tujuan: ";
                cin >> endID;
                shortestRoute(G, startID, endID);
                break;
            }
            case 9: {
                cout << "Keluar dari program." << endl;
                break;
            }
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (choice != 9);

    return 0;
}
