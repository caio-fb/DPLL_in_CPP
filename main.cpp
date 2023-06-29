#include <iostream>
#include <vector>

using namespace std;
vector<vector <int>> Simplifica(vector<vector <int>> formula);

// elimina as cláusulas que contém o literal
// retira os literais negativos
vector<vector <int>> removeNasFormulas(vector<vector <int>> formula, int literal){
    for(int i = 0; i<formula.size(); i++){
        for(int j = 0; j<formula[i].size(); j++){
            if(formula[i][j] == literal){
                formula[i].clear();
            } else if(formula[i][j] == literal*(-1)){
                formula[i].erase(formula[i].begin()+ j);
            }
        }
    }
    return Simplifica(formula);
}


// verifica se tem cláusula unitária
// em seguida chama a remoção de cláusulas/literal na fórmula
vector<vector <int>> Simplifica(vector<vector <int>> formula){
    for(int i = 0; i<formula.size(); i++){
        if(formula[i].size() == 1){
            int formulaUnitaria = formula[i][0];
            formula = removeNasFormulas(formula, formulaUnitaria);
            return formula;
        }
    }
    return formula;
}

bool DPLL(vector<int> formula){
    //se todas as cláusulas de Φ forem verdadeiras -> true

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

int main() {
    vector<vector<int> > formulaTeste{
                              {-1},
                              { 1, 2 },
                              { 1, 3 },
                              { -2, -3, -4, -5 },
                              { -1, 4} };

    formulaTeste = Simplifica(formulaTeste);
    printFormula(formulaTeste);


    return 0;
}

/*
 se todas as cláusulas de Φ forem verdadeiras
       então retorne verdadeiro;
   se alguma cláusula de Φ for falsa
       então retorne falso;
   se ocorrer uma cláusula unitária c em Φ
       então retorne DPLL(atribuição(c,Φ), μ ∧ c);
   se ocorrer um literal puro c em Φ
       então retorne DPLL(atribuição(c,Φ), μ ∧ c);
   c := escolha_literal(Φ);
   retorne DPLL(atribuição(c,Φ), μ ∧ c) ou DPLL(atribuição(¬c,Φ), μ ∧ ¬c);
 */