#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void mostrarHistorico() {
    ifstream ficheiro("diagnostico.txt");
    if (!ficheiro.is_open()) {
        cout << "[⚠️] Nenhum histórico encontrado.\n";
        return;
    }

    cout << "\n📖 Histórico de Diagnósticos:\n\n";
    string linha;
    while (getline(ficheiro, linha)) {
        cout << linha << endl;
    }

    ficheiro.close();
}

void apagarHistorico() {
    ofstream ficheiro("diagnostico.txt", ios::trunc);
    ficheiro.close();
    cout << "[🧹] Histórico apagado com sucesso!\n";
}

#endif