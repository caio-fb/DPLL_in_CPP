Objetivo do trabalho é solucionar o problema de xadrez das N-Rainhas usando o algoritmo de DPLL

DPLL:

função DPLL(Φ, μ)
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
