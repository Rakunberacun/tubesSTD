#include "graph.h"

int main() {
    Graph G;
    initGraph(G);

    addStasiun(G, "Tanah Abang");
    addStasiun(G, "Manggarai");
    addStasiun(G, "Jakarta Kota");
    addStasiun(G, "Duri");
    addStasiun(G, "Kampung Bandan");
    addStasiun(G, "Rajawali");
    addStasiun(G, "Jatinegara");

    addRute(G, "Tanah Abang", "Duri", 1, false);
    addRute(G, "Duri", "Tanah Abang", 1, false);

    addRute(G, "Tanah Abang", "Manggarai", 4, false);
    addRute(G, "Manggarai", "Tanah Abang", 4, false);

    addRute(G, "Tanah Abang", "Kampung Bandan", 3, false);
    addRute(G, "Kampung Bandan", "Tanah Abang", 3, false);

    addRute(G, "Tanah Abang", "Rajawali", 4, false);
    addRute(G, "Rajawali", "Tanah Abang", 4, false);

    addRute(G, "Tanah Abang", "Jatinegara", 10, false);
    addRute(G, "Jatinegara", "Tanah Abang", 10, false);

    addRute(G, "Duri", "Rajawali", 3, false);
    addRute(G, "Rajawali", "Duri", 3, false);

    addRute(G, "Duri", "Kampung Bandan", 2, false);
    addRute(G, "Kampung Bandan", "Duri", 2, false);

    addRute(G, "Duri", "Jatinegara", 9, false);
    addRute(G, "Jatinegara", "Duri", 9, false);

    addRute(G, "Duri", "Manggarai", 5, false);
    addRute(G, "Manggarai", "Duri", 5, false);

    addRute(G, "Manggarai", "Rajawali", 8, false);
    addRute(G, "Rajawali", "Manggarai", 8, false);

    addRute(G, "Manggarai", "Kampung Bandan", 7, false);
    addRute(G, "Kampung Bandan", "Manggarai", 7, false);

    addRute(G, "Manggarai", "Jakarta Kota", 8, false);
    addRute(G, "Manggarai", "Jatinegara", 1, false);

    addRute(G, "Jakarta Kota", "Manggarai", 8, false);
    addRute(G, "Jakarta Kota", "Jatinegara", 9, false);

    addRute(G, "Jatinegara", "Manggarai", 1, false);
    addRute(G, "Jatinegara", "Jakarta Kota", 9, false);

    addRute(G, "Jakarta Kota", "Kampung Bandan", 1, false);
    addRute(G, "Jakarta Kota", "Rajawali", 2, false);

    addRute(G, "Kampung Bandan", "Jakarta Kota", 1, false);
    addRute(G, "Kampung Bandan", "Rajawali", 1, false);

    addRute(G, "Rajawali", "Jakarta Kota", 2, false);
    addRute(G, "Rajawali", "Kampung Bandan", 1, false);


    int choice;
    do {
        cout << "\n==== Menu Graph ====\n";
        cout << "1. Menunjukkan semua graph\n";
        cout << "2. Mencari rute terpendek\n";
        cout << "3. Menambahkan Rute\n";
        cout << "4. Menambahkan Stasiun\n";
        cout << "5. Menghapus Stasiun\n";
        cout << "6. Mulai Maintenance Rute\n";
        cout << "7. Buka Kembali Rute\n";
        cout << "9. Exit Program\n";
        cout << "Pilihan: ";

        if (!(cin >> choice)) {
            cout << "Input tidak valid. Masukkan angka." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }

        switch (choice) {
            case 1:
                cout << "\n== Menampilkan Graph ==\n";
                displayGraph(G);
                break;
            case 2: {
                string startNama, endNama;
                cout << "\nMasukkan nama stasiun asal: ";
                cin.ignore(INT_MAX, '\n');
                getline(cin, startNama);

                cout << "Masukkan nama stasiun tujuan: ";
                getline(cin,endNama);

                shortestRoute(G, startNama, endNama);
                break;
            }
            case 3: {
                string fromNamaStasiun, toNamaStasiun;
                int bobot;
                cout << "\nMasukkan nama stasiun asal: ";
                cin.ignore(INT_MAX, '\n');
                getline(cin, fromNamaStasiun);
                cout << "Masukkan nama stasiun tujuan: ";
                getline(cin, toNamaStasiun);

                adrStasiun S;

                bool foundAsal = findStasiun(G, fromNamaStasiun, S);
                bool foundTujuan = findStasiun(G, toNamaStasiun, S);

                if (!foundAsal && !foundTujuan) {
                    cout << "Stasiun asal dan tujuan tidak ditemukan" << endl;
                } else if (!foundAsal) {
                    cout << "Stasiun asal tidak ditemukan" << endl;
                } else if (!foundTujuan) {
                    cout << "Stasiun tujuan tidak ditemukan" << endl;
                } else {
                    cout << "Masukkan jarak rute: ";
                    cin >> bobot;
                    if (cin.fail()) {
                        cout << "Input tidak valid, masukkan angka. Rute tidak ditambahkan." << endl;
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                    } else if (bobot <= 0) {
                        cout << "Masukkan angka positif untuk jarak. Rute tidak ditambahkan." << endl;
                    } else {
                        if (isRuteExist(G, fromNamaStasiun, toNamaStasiun)) {
                            cout << "Rute dari " << fromNamaStasiun << " ke " << toNamaStasiun << " sudah ada." << endl;
                        } else {
                            addRute(G, fromNamaStasiun, toNamaStasiun, bobot, false);
                            cout << "Rute dari " << fromNamaStasiun << " ke " << toNamaStasiun << " berhasil ditambahkan dengan jarak " << bobot << "." << endl;
                        }
                    }
                }
                break;
            }
            case 4: {
                string namaStasiun;
                cout << "\nMasukkan nama stasiun baru: ";
                cin.ignore(INT_MAX, '\n');
                getline(cin, namaStasiun);

                if (namaStasiun.empty()) {
                    cout << "Nama stasiun tidak boleh kosong." << endl;
                    break;
                }

                adrStasiun S;
                if (findStasiun(G, namaStasiun, S)) {
                    cout << "Stasiun sudah ada, tambahkan stasiun lain." << endl;
                } else {
                    addStasiun(G, namaStasiun);
                    cout << "Stasiun " << namaStasiun << " berhasil ditambahkan." << endl;

                    char tambahRute;
                    cout << "Ingin menambahkan rute dari stasiun ini? (y/n): ";
                    cin >> tambahRute;

                    if (tambahRute == 'y' || tambahRute == 'Y') {
                        string tujuan;
                        int bobot;

                        cout << "Masukkan nama stasiun tujuan: ";
                        cin.ignore(INT_MAX, '\n');
                        getline(cin, tujuan);

                        if (tujuan.empty()) {
                            cout << "Nama stasiun tujuan tidak boleh kosong. Rute tidak ditambahkan." << endl;
                            break;
                        }

                        if (!findStasiun(G, tujuan, S)) {
                            cout << "Stasiun tujuan tidak ditemukan, rute tidak ditambahkan." << endl;
                            break;
                        }

                        cout << "Masukkan jarak rute: ";
                        cin >> bobot;

                        if (cin.fail()) {
                            cout << "Input tidak valid, masukkan angka. Rute tidak ditambahkan." << endl;
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                        } else if (bobot <= 0) {
                            cout << "Masukkan angka positif untuk jarak. Rute tidak ditambahkan." << endl;
                        } else {
                            addRute(G, namaStasiun, tujuan, bobot, false);
                            cout << "Rute dari " << namaStasiun << " ke " << tujuan << " berhasil ditambahkan dengan jarak " << bobot << "." << endl;
                        }
                    }
                }
                break;
            }
            case 5: {
                string namaStasiun;
                cout << "\nMasukkan nama stasiun yang ingin dihapus: ";
                cin.ignore(INT_MAX, '\n');
                getline(cin, namaStasiun);

                adrStasiun S;

                bool foundAsal = findStasiun(G, namaStasiun, S);

                if (!foundAsal) {
                    cout << "Nama stasiun tidak ditemukan" << endl;
                } else {
                    deleteStasiun(G, namaStasiun);
                    cout << "Stasiun " << namaStasiun << " dan semua rutenya berhasil dihapus." << endl;
                }
                break;
            }
            case 6: {
                string fromNamaStasiun, toNamaStasiun;
                cout << "\nMasukkan nama stasiun asal: ";
                cin.ignore(INT_MAX, '\n');
                getline(cin, fromNamaStasiun);
                cout << "Masukkan nama stasiun tujuan: ";
                getline(cin, toNamaStasiun);

                adrStasiun S;

                bool foundAsal = findStasiun(G, fromNamaStasiun, S);
                bool foundTujuan = findStasiun(G, toNamaStasiun, S);

                if (!foundAsal && !foundTujuan) {
                    cout << "Stasiun asal dan tujuan tidak ditemukan" << endl;
                } else if (!foundAsal) {
                    cout << "Stasiun asal tidak ditemukan" << endl;
                } else if (!foundTujuan) {
                    cout << "Stasiun tujuan tidak ditemukan" << endl;
                } else {
                    startMaintenance(G, fromNamaStasiun, toNamaStasiun);
                }
                break;
            }
            case 7: {
                string fromNamaStasiun, toNamaStasiun;
                cout << "\nMasukkan nama stasiun asal: ";
                cin.ignore(INT_MAX, '\n');
                getline(cin, fromNamaStasiun);
                cout << "Masukkan nama stasiun tujuan: ";
                getline(cin, toNamaStasiun);

                adrStasiun S;

                bool foundAsal = findStasiun(G, fromNamaStasiun, S);
                bool foundTujuan = findStasiun(G, toNamaStasiun, S);

                if (!foundAsal && !foundTujuan) {
                    cout << "Stasiun asal dan tujuan tidak ditemukan" << endl;
                } else if (!foundAsal) {
                    cout << "Stasiun asal tidak ditemukan" << endl;
                } else if (!foundTujuan) {
                    cout << "Stasiun tujuan tidak ditemukan" << endl;
                } else {
                    reopenRoute(G, fromNamaStasiun, toNamaStasiun);
                }
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
