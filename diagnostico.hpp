#ifndef DIAGNOSTICO_HPP
#define DIAGNOSTICO_HPP

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

map<string, vector<string>> baseDoencas = {
    {"Gripe", {"febre", "tosse", "dor de cabeça", "cansaco"}},
    {"Covid-19", {"febre", "tosse", "falta de ar", "cansaco", "dor de cabeça"}},
    {"Gastroenterite", {"vomito", "diarreia", "nausea", "febre"}},
    {"Amigdalite", {"dor", "garganta", "febre", "dor de cabeça"}}
};

void gerarDiagnostico(const vector<string>& sintomasUsuario) {
    map<string, int> pontuacoes;

    for (const auto& [doenca, sintomas] : baseDoencas) {
        for (const auto& sintoma : sintomas) {
            if (find(sintomasUsuario.begin(), sintomasUsuario.end(), sintoma) != sintomasUsuario.end()) {
                pontuacoes[doenca]++;
            }
        }
    }

    string melhorDiagnostico;
    int maxPontuacao = 0;

    for (const auto& [doenca, pontuacao] : pontuacoes) {
        if (pontuacao > maxPontuacao) {
            maxPontuacao = pontuacao;
            melhorDiagnostico = doenca;
        }
    }

    if (!melhorDiagnostico.empty()) {
        cout << "\n[🧠] Diagnóstico sugerido: " << melhorDiagnostico << " (" << maxPontuacao << " sintomas coincidem)\n";

        ofstream ficheiro("diagnostico.txt", ios::app);
        ficheiro << "Diagnóstico: " << melhorDiagnostico << " | Sintomas: ";
        for (const auto& s : sintomasUsuario) {
            ficheiro << s << " ";
        }
        ficheiro << endl;
        ficheiro.close();

        map<string, pair<string, string>> conselhos = {
            {"Gripe", {"Baixo", "Repousa, bebe muita água e usa antipiréticos."}},
            {"Covid-19", {"Alto", "Isola-te e procura ajuda médica se os sintomas piorarem."}},
            {"Gastroenterite", {"Médio", "Mantém-te hidratado e evita alimentos pesados."}},
            {"Amigdalite", {"Médio", "Evita bebidas frias, faz gargarejos e procura um médico se persistir."}}
        };

        if (conselhos.find(melhorDiagnostico) != conselhos.end()) {
            cout << "[🚦] Urgência: " << conselhos[melhorDiagnostico].first << endl;
            cout << "[💡] Conselho: " << conselhos[melhorDiagnostico].second << endl;
        }

    } else {
        cout << "\n[❓] Não foi possível sugerir um diagnóstico com os sintomas fornecidos.\n";
    }
}

#endif