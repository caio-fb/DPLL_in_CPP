// Caio Finotti, José Leonardo e Victor M.
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
vector<vector <int>> Simplifica(vector<vector <int>> formula);
vector <int> modelo;

// elimina as cláusulas que contém o literal
// retira os literais negativos
vector<vector <int>> removeNasFormulas(vector<vector <int>> formula, int literal){
    modelo.push_back(literal);          // adiciona os literais usados dentro do modelo
    vector <vector <int>> newFormula;
    for(int i = 0; i<formula.size(); i++){          // passa por cada cláusula
        for(int j = 0; j<formula[i].size(); j++){   // passa por cada literal
            if(formula[i][j] == literal){
                formula[i].clear();                 // se o literal estiver em alguma cláusula, deleta cláusula
            } else if(formula[i][j] == literal*(-1)){   // se o literal negado estiver em alguma cláusula
                formula[i].erase(formula[i].begin()+ j);    // remova apenas ele
                if(formula[i].size() == 0){         // se a cláusula for unitária
                    newFormula.push_back(formula[i]);       // adiciona uma cláusula vazia em newFormula
                }
            }
        }
    }

    for(int i = 0; i<formula.size(); i++){      // adiciona todas as cláusulas não vazias no conjunto newFormula
        if(formula[i].size() != 0){
            newFormula.push_back(formula[i]);
        }
    }
    return Simplifica(newFormula); // chama o Simplifica passando o novo conjunto
}


// verifica se tem cláusula unitária
// em seguida chama a remoção de cláusulas/literal na fórmula
vector<vector <int>> Simplifica(vector<vector <int>> formula){
    for(int i = 0; i<formula.size(); i++){          // passa por todas as cláusulas
        if(formula[i].size() == 1){         // se a formula for unitária
            formula = removeNasFormulas(formula, formula[i][0]);    // recebe a formula pós remoção dos literais
            return formula;
        }
    }
    return formula;
}


bool DPLL(vector <vector<int>> formula){
    // recebe a formula simplificada
    formula = Simplifica(formula);
    if(formula.size() == 0){        // se a formula em si estiver vazia então é verdadeira
        return true;
    }
    for(int i = 0; i <formula.size(); i++){    // se dentro da formula tiver alguma cláusula vazia
        if(formula[i].size() == 0){
            return false;                       // então a formula é falsa
        }
    }
            // seleciona o primeiro literal da ultima cláusula
    int literal = formula.back()[0];
    formula.push_back({literal});   // adiciona este literal como uma nova cláusula unitária
    if(DPLL(formula)){          // chama o DPLL de novo, se for verdadeiro retorna true
        return true;
    } else if(DPLL(formula)){ // caso seja falso com o literal escolhido
        formula.push_back({literal*(-1)});      // escolhemos a negação deste literal
        if(DPLL(formula)){      // se dessa vez retornar verdadeiro então retorne true
            return true;
        }
    } else {    // se não retorna falso
        return false;
    }
}

void printFormula(vector<vector<int>> vec){
    for(int i = 0; i<vec.size(); i++){
        cout << "vetor: " << i << "\n[ ";
        for(int j = 0; j<vec[i].size(); j++){
            cout << vec[i][j] << " | ";
        }
        cout << " ]\n";
    }
}

// exibir o modelo (para n-rainhas)
void printModelo(vector <int> modelo){
    for(int i = 0; i<modelo.size()/2; i++){
        cout <<"Modelo: " << modelo[i] << endl;
    }
}


vector<vector<int>> getFormulaInTXT() {
    vector<vector<int>> formula;
    ifstream data_file("../CLAUSULAS.txt");

    if (data_file.is_open()) {
        string line;
        while (getline(data_file, line)) {  // cada linha do arquivo usando getline() é armazenado em line.
            stringstream ss(line);
            vector<int> clausula;
            int value;
            while (ss >> value) {          // ss extrai os valores inteiros de line e armazena em cláusulas
                clausula.push_back(value);
                if (ss.peek() == ',')   // ignora as virgulas
                    ss.ignore();
            }
            formula.push_back(clausula);
        }
        data_file.close();
    } else {
        cout << "Falha ao abrir o arquivo!" << endl;
    }

    return formula;
}

int main() {
    vector<vector<int>> formula = getFormulaInTXT();

    if(DPLL(formula)){
        cout << "Satisfazivel!" << endl;
    } else{
        cout << "Insatisfazivel!" << endl;
    }

    cout << "\n---------------" << endl;
    printModelo(modelo);

    return 0;
}
