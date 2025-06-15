#include <iostream>
#include <thread>
#include <chrono>

#include "sintomas.hpp"
#include "diagnostico.hpp"
#include "utils.hpp"
#include "ia.hpp"


using namespace std;

void mostrarMenu() {
    cout << "\033[1;36m==============================\033[0m" << endl; // Azul claro
    cout << "    🧠 \033[1;32mEvoluBot MedCare\033[0m 🏥" << endl; // Verde
    cout << "\033[1;36m==============================\033[0m" << endl;
    cout << "1. 📝 Introduzir sintomas" << endl;
    cout << "2. 📄 Ver diagnósticos anteriores" << endl;
    cout << "3. 🧹 Apagar histórico de diagnósticos" << endl;
    cout << "4. ❌ Sair" << endl;
    cout << "\033[1;33mEscolha uma opção: \033[0m"; // Amarelo
}

void mostrarLoading() {
    cout << "\033[1;34m[🔄] Processando...\033[0m";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    cout << endl;
}

int main() {
    int opcao;

    do {
        mostrarMenu();
        cin >> opcao;
        while (cin.fail() || opcao < 1 || opcao > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\033[1;31m[⚠️] Entrada inválida. Escolha uma opção válida: \033[0m";
            cin >> opcao;
        }
        cin.ignore(); // Ignorar o '\n' após o número

        switch (opcao) {
            case 1:
                tratarSintomas();
                break;
            case 2:
                cout << "\n[📄] Mostrando diagnósticos anteriores...\n";
                mostrarLoading();
                mostrarHistorico();
                break;
            case 3:
                cout << "\n[🧹] Apagando histórico...\n";
                mostrarLoading();
                apagarHistorico();
                break;
            case 4:
                cout << "\n\033[1;32m[👋] Obrigado por usar o EvoluBot MedCare!\033[0m" << endl;
                cout << "\033[1;34m[💡] Cuide-se e até logo!\033[0m\n";
                break;
            default:
                cout << "\033[1;31m[⚠️] Opção inválida. Tente novamente.\033[0m\n";
        }

        cout << endl;

    } while (opcao != 4);

    return 0;
}