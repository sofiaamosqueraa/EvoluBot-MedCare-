#ifndef SINTOMAS_HPP
#define SINTOMAS_HPP

#include <iostream>
#include <string>
#include <fstream>
#include "ia.hpp" // Para usar a função perguntarIA
using namespace std;

void tratarSintomas() {
    string sintomas;
    cout << "\n[📝] Escreva seus sintomas: ";
    getline(cin, sintomas);

    cout << "\n[🔍] Analisando seus sintomas com a IA...\n";
    string respostaIA = perguntarIA(sintomas);

    // Combinar diagnóstico baseado em regras com a resposta da IA
    string diagnosticoFinal = combinarDiagnostico(sintomas, respostaIA);

    // Salvar no histórico
    ofstream historico("historico.txt", ios::app);
    historico << "Sintomas: " << sintomas << endl;
    historico << "Diagnóstico IA: " << respostaIA << endl;
    historico << "Diagnóstico baseado em regras: " << diagnosticoFinal << "\n---\n";
    historico.close();
}

#endif
