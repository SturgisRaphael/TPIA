//
// Created by Raphael on 4/10/2018.
//

#include <iostream>
#include <unistd.h>
#include "CNF.h"

using namespace std;

CNF::CNF(const vector<linkedList> &literals, const vector<linkedList> &clauses) : literals(literals),
                                                                                  clauses(clauses) {}

CNF::CNF() {}

const vector<linkedList> &CNF::getLiterals() const {
    return literals;
}

void CNF::setLiterals(const vector<linkedList> &literals) {
    CNF::literals = literals;
}

const vector<linkedList> &CNF::getClauses() const {
    return clauses;
}

void CNF::setClauses(const vector<linkedList> &clauses) {
    CNF::clauses = clauses;
}

const vector<vector<int>> &CNF::getSolutions() const {
    return solutions;
}

int CNF::getNbSolutionsFound() const {
    return nbSolutionsFound;
}

void CNF::solve() {
    solve(-1, NO);
}

void CNF::solve(CNF::heuristic h) {
    solve(-1, h);
}

void CNF::solve(int nbSolution, CNF::heuristic h) {

    int solutionsFound = 0;
    vector<int > currentSolution;
    int currentLiteral, currentNegLiteral;
    cnfExecutionTree *executionTree, left, right;
    cnfExecutionTree root = cnfExecutionTree(this->literals, this->clauses);
    bool findAllSolution = false;
    if(nbSolution < 0)
        findAllSolution = true;

    vector<cnfExecutionTree *> nodeToExplore;
    nodeToExplore.push_back(&root);

    do{
        bool pure = false;
        int currentLiteral = -1, pureLiteral = 0;
        executionTree = nodeToExplore.back();
        nodeToExplore.pop_back();

        //Unit propagation
        if(!UnitPropagation(executionTree))//Impossible state
            continue;

        int max;
        //choose literal

        switch (h){
            case FIRST_SATISFY:
                max = 0;
                for(int i = 0; i < executionTree->getLiterals().size(); i++)
                {
                    if(executionTree->getLiterals()[i].countElement() >= max){
                        max = executionTree->getLiterals()[i].countElement();
                        currentLiteral = i;
                    }

                    if(currentLiteral%2 == 0)
                        currentNegLiteral = currentLiteral + 1;
                    else
                        currentNegLiteral = currentLiteral - 1;

                    if(executionTree->getLiterals()[currentNegLiteral].getElement() == -1){
                        pure = true;
                        pureLiteral = currentLiteral;
                    }
                }
                break;
            case FIRST_FAIL:
                break;
            default:
                for(int i = 0; i < executionTree->getLiterals().size(); currentLiteral++)
                {
                    if(executionTree->getLiterals()[currentLiteral].getElement() != -1)
                    {
                        currentLiteral = i;
                        if(currentLiteral%2 == 0)
                            currentNegLiteral = currentLiteral + 1;
                        else
                            currentNegLiteral = currentLiteral - 1;

                        if(executionTree->getLiterals()[currentNegLiteral].getElement() == -1){
                            pure = true;
                            pureLiteral = currentLiteral;
                        }
                    }
                }
                break;
        }

        if(currentLiteral == -1 /*&& executionTree->getLiterals()[currentLiteral].getClause() == -1*/)
        {
            solutions.push_back(executionTree->getCurrentModel());
            solutionsFound++;
            continue;
        }

        else{
            if(pure){
                cout << "pure = " << pureLiteral << endl;
                currentLiteral = pureLiteral;
                if(!findAllSolution)
                {
                    //explore left
                    left = cnfExecutionTree(executionTree->getLiterals(), executionTree->getClauses(), executionTree->getCurrentModel());
                    left.assignLiteral(currentNegLiteral + 1, currentLiteral + 1);

                    nodeToExplore.push_back(&left);
                    continue;
                }
            }

            //explore left
            left = cnfExecutionTree(executionTree->getLiterals(), executionTree->getClauses(), executionTree->getCurrentModel());
            left.assignLiteral(currentNegLiteral + 1, currentLiteral + 1);
            //explore right
            right = cnfExecutionTree(executionTree->getLiterals(), executionTree->getClauses(), executionTree->getCurrentModel());
            right.assignLiteral(currentLiteral + 1, currentNegLiteral + 1);

            nodeToExplore.push_back(&left);
            nodeToExplore.push_back(&right);
        }

    }while((!findAllSolution && (solutionsFound < nbSolution)) || !nodeToExplore.empty());
    nbSolutionsFound = solutionsFound;
}

bool CNF::UnitPropagation(cnfExecutionTree *pTree) {
    for (int i = 0; i < pTree->getClauses().size(); i++) {
        if(pTree->getClauses()[i].getNext() == nullptr && pTree->getClauses()[i].getElement() > 0){

            int currentLiteral = pTree->getClauses()[i].getElement(), currentNegLiteral;//-1 neccesary because of indices
            if(currentLiteral%2 == 1)//positive
                currentNegLiteral = currentLiteral + 1;
            else
                currentNegLiteral = currentLiteral - 1;

            //verify negation not also a unit clause
            for (auto &j : pTree->getClauses())
                if(j.getElement() == currentNegLiteral && j.getNext() == nullptr)
                    return false;

            pTree->assignLiteral(currentLiteral, currentNegLiteral);
        }
    }

    return true;
}

ostream &operator<<(ostream &os, const CNF &cnf) {
    os << "literals: ";
    for(auto i : cnf.literals)
        os << i << ",";
    os <<"\nclauses: ";
    for(auto i : cnf.clauses)
        os << i << ",";
    os << "\nsolutions: ";
    for(auto i : cnf.solutions) {
        os << "[";
        for (auto j : i)
            os << j << ",";
        os << "]";
    }
    os << "\nnbSolutionsFound: " << cnf.nbSolutionsFound;
    return os;
}