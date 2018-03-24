//
// Created by raphael on 3/14/18.
//

#ifndef PROJET_CNF_H
#define PROJET_CNF_H


#include "literalList.h"
#include "clauseList.h"
#include "cnfExecutionTree.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Generator {

public:
static void GenereFile (int nbClauses, int nbLiterals);

};

class CNF {
    enum heuristic {NO, FIRST_SATISFY, FIRST_FAIL};
private:
    vector<clauseList> literals;
    vector<literalList> clauses;
    vector<vector<int>> solutions;
    int nbSolutionsFound;

public:
    static void readFromFile(string addr);
    void solve();
    void solve(heuristic h);
    void solve(int nbSolution, heuristic h);

    bool UnitPropagation(cnfExecutionTree *pTree);
};


#endif //PROJET_CNF_H
