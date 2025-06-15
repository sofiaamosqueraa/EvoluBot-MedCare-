#ifndef IA_HPP
#define IA_HPP

#include <iostream>
#include <string>
#include <sstream> // Adicionado para usar std::stringstream
#include <Python.h> // Biblioteca Python/C API
#include "diagnostico.hpp" // Para combinar com o diagnóstico baseado em regras

using namespace std;

string perguntarIA(string sintomas) {
    // Inicializar o interpretador Python
    Py_Initialize();

    // Adicionar o diretório atual ao sys.path
    PyObject* sysPath = PySys_GetObject("path");
    PyObject* currentDir = PyUnicode_FromString(".");
    PyList_Append(sysPath, currentDir);
    Py_DECREF(currentDir);

    // Nome do script Python (sem extensão .py)
    PyObject* pName = PyUnicode_FromString("ia_script");
    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != nullptr) {
        // Função a ser chamada no script Python
        PyObject* pFunc = PyObject_GetAttrString(pModule, "processar_sintomas");

        if (pFunc && PyCallable_Check(pFunc)) {
            // Converter os sintomas para um objeto Python
            PyObject* pArgs = PyTuple_Pack(1, PyUnicode_FromString(sintomas.c_str()));

            // Chamar a função Python
            PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);

            if (pValue != nullptr) {
                // Converter a resposta Python para string C++
                string resposta = PyUnicode_AsUTF8(pValue);
                Py_DECREF(pValue);
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                Py_Finalize();
                return resposta;
            } else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                Py_Finalize();
                return "Erro ao obter resposta da IA.";
            }
        } else {
            if (PyErr_Occurred()) PyErr_Print();
            Py_DECREF(pModule);
            Py_Finalize();
            return "Função processar_sintomas não encontrada no script Python.";
        }
    } else {
        PyErr_Print();
        Py_Finalize();
        return "Erro ao carregar o script Python.";
    }
}

string filtrarResposta(string resposta) {
    if (resposta.find("diagnóstico") != string::npos || resposta.find("tratamento") != string::npos) {
        return resposta;
    }
    return "A resposta da IA não foi clara. Por favor, tente novamente.";
}

string combinarDiagnostico(string sintomas, string respostaIA) {
    vector<string> sintomasUsuario;
    stringstream ss(sintomas);
    string sintoma;

    // Dividir os sintomas em palavras individuais
    while (getline(ss, sintoma, ' ')) {
        sintomasUsuario.push_back(sintoma);
    }
    // Gerar diagnóstico baseado em regras
    cout << "\n[🧠] Diagnóstico baseado em regras:\n";
    gerarDiagnostico(sintomasUsuario);

    // Combinar com a resposta da IA
    cout << "\n[🤖] Resposta da IA:\n" << respostaIA << endl;

    return "Diagnóstico combinado concluído.";
}

#endif
