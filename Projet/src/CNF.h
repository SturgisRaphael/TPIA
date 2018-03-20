//
// Created by raphael on 3/14/18.
//

#ifndef PROJET_CNF_H
#define PROJET_CNF_H


#include "literalList.h"
#include "clauseList.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

enum heuristic {NO, FIRST_SATISFY, FIRST_FAIL};

class Generator {

public:
static void GenereFile (int nbClauses, int nbLiterals);

};

class CNF {
private:
    vector<clauseList> clauses;
    vector<literalList> literals;
    vector<vector<int>> solutions;

public:
    static void readFromFile(string addr);

    void solve(int nbSolutions, heuristic h);
};


#endif //PROJET_CNF_H
