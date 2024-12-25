#include "graph.h"
#include <iostream>
using namespace std;

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
        cout << "\n==== Menu Graph ====\n";
        cout << "1. Menunjukkan semua graph\n";
        cout << "2. Mencari stasiun\n";
        cout << "3. Mencari rute\n";
        cout << "4. Mencari rute terpendek\n";
        cout << "5. Menambahkan Stasiun\n";
        cout << "6. Menghapus Stasiun\n";
        cout << "9. Exit Program\n";
        cout << "Pilihan: ";

        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n== Menampilkan Graph ==\n";
                displayGraph(G);
                break;
            case 2: {
                string namaStasiun;
                cout << "\nMasukkan nama stasiun yang ingin dicari: ";
                cin.ignore(INT_MAX, '\n'); // Clear the input buffer
                getline(cin, namaStasiun);
                adrStasiun S;
                if (findStasiun(G, namaStasiun, S)) {
                    cout << "Stasiun " << namaStasiun << " ditemukan." << endl;
                } else {
                    cout << "Stasiun " << namaStasiun << " tidak ditemukan." << endl;
                }
                break;
            }
            case 3: {
                string fromNamaStasiun, toNamaStasiun;
                cout << "\nMasukkan nama stasiun asal: ";
                cin.ignore(INT_MAX, '\n'); // Clear the input buffer
                getline(cin,fromNamaStasiun);

                cout << "Masukkan nama stasiun tujuan: ";
                getline(cin, toNamaStasiun);

                adrRute R;
                if (findRute(G, fromNamaStasiun, toNamaStasiun, R)) {
                    cout << "Rute ditemukan dengan bobot: " << weight(R) << endl;
                } else {
                    cout << "Rute dari " << fromNamaStasiun << " ke " << toNamaStasiun << " tidak ditemukan." << endl;
                }
                break;
            }
            case 4: {
                string startNama, endNama;
                cout << "\nMasukkan nama stasiun asal: ";
                cin.ignore(INT_MAX, '\n');
                getline(cin, startNama);

                cout << "Masukkan nama stasiun tujuan: ";
                getline(cin,endNama);

                shortestRoute(G, startNama, endNama);
                break;
            }
            case 5: {
                string namaStasiun;
                cout << "\nMasukkan nama stasiun baru: ";
                cin.ignore(INT_MAX, '\n');
                getline(cin, namaStasiun);
                addStasiun(G, namaStasiun);
                cout << "Stasiun " << namaStasiun << " berhasil ditambahkan." << endl;
                break;
            }
            case 6: {
                string namaStasiun;
                cout << "\nMasukkan nama stasiun yang ingin dihapus: ";
                cin.ignore(INT_MAX, '\n');
                getline(cin, namaStasiun);
                deleteStasiun(G, namaStasiun);
                break;
            }
            case 9:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    } while (choice != 9);

    return 0;
}
