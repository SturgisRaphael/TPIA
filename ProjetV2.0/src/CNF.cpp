//
// Created by Raphael on 4/10/2018.
//

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include "CNF.h"

using namespace std;

CNF::CNF(const vector<linkedList> &literals, const vector<linkedList> &clauses) : literals(literals),
                                                                                  clauses(clauses) {}

CNF::CNF() {}

vector<linkedList> &CNF::getLiterals(){
    return literals;
}

void CNF::setLiterals(const vector<linkedList> &literals) {
    CNF::literals = literals;
}

vector<linkedList> &CNF::getClauses(){
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

void CNF::readFromFile(string addr) {
    std::ifstream infile(addr);
    std::string line;

    std::getline(infile, line);

    std::istringstream iss(line);
    int nbClauses, nbLiterals;

    iss >> nbClauses >> nbLiterals;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int valIn = -1;
        clauses.push_back(linkedList());
        do {
            iss >> valIn;
            if(valIn == 0)
                break;
            clauses.back().addElement(valIn);
        }while( valIn != 0);
    }

    vector<linkedList> vect = this->getClauses();
    for(int j = 0; j < nbLiterals; j++)
    {
        linkedList l = linkedList();
        for(int k= 0; k < vect.size(); k++)
        {
            if(vect[k].isInList(j + 1))
                l.addElement(k+1);
        }
        this->getLiterals().push_back(l);
    }
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
                for(int i = 0; i < executionTree->getLiterals().size(); i++)
                {
                    if(executionTree->getLiterals()[i].getElement() != -1)
                    {
                        currentLiteral = i;
                        if(currentLiteral%2 == 0)
                            currentNegLiteral = currentLiteral + 1;
                        else
                            currentNegLiteral = currentLiteral - 1;

                        if(executionTree->getLiterals()[currentNegLiteral].getElement() == -1){
                            pure = true;
                            pureLiteral = currentLiteral;
                            break;
                        }
                    }
                }
                break;
        }
        cout <<  1 + currentLiteral << endl;

        if(currentLiteral == -1 /*&& executionTree->getLiterals()[currentLiteral].getClause() == -1*/)
        {
            solutions.push_back(executionTree->getCurrentModel());
            solutionsFound++;
            cout << "solution found!!" << endl;
            continue;
        }

        else{
            if(pure){
                cout << "pure = " << pureLiteral << endl;
                currentLiteral = pureLiteral;
                if(!findAllSolution)
                {
                    //explore right
                    right = cnfExecutionTree(executionTree->getLiterals(), executionTree->getClauses(), executionTree->getCurrentModel());
                    right.assignLiteral(currentLiteral + 1, currentNegLiteral + 1);

                    nodeToExplore.push_back(&right);
                    continue;
                }
            }

            cnfExecutionTree *tmp = new cnfExecutionTree(executionTree->getLiterals(), executionTree->getClauses(), executionTree->getCurrentModel());

            //explore left
            left = cnfExecutionTree(executionTree->getLiterals(), executionTree->getClauses(), executionTree->getCurrentModel());
            left.assignLiteral(currentNegLiteral + 1, currentLiteral + 1);

            executionTree = tmp;

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
    bool finish = false;
    while(!finish) {
        finish = true;
        for (int i = 0; i < pTree->getClauses().size(); i++) {
            if (pTree->getClauses()[i].getNext() == nullptr && pTree->getClauses()[i].getElement() > 0) {
                finish = false;
                int currentLiteral = pTree->getClauses()[i].getElement(), currentNegLiteral;//-1 neccesary because of indices

                cout << "unit propagationn : " << currentLiteral << endl;

                if (currentLiteral % 2 == 1)//positive
                    currentNegLiteral = currentLiteral + 1;
                else
                    currentNegLiteral = currentLiteral - 1;

                //verify negation not also a unit clause
                for (auto &j : pTree->getClauses())
                    if (j.getElement() == currentNegLiteral && j.getNext() == nullptr)
                        return false;

                //verify negation not in model
                for (auto &j : pTree->getCurrentModel())
                    if (j == currentNegLiteral)
                        return false;

                pTree->assignLiteral(currentLiteral, currentNegLiteral);
            }
        }
    }
    return true;
}

ostream &operator<<(ostream &os, const CNF &cnf) {
    os << "literals: ";
    for(auto i : cnf.literals)
        os << "[" << i << "];";
    os <<"\nclauses: ";
    for(auto i : cnf.clauses)
        os << "[" << i << "];";
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

void CNF::generateProblemFile(string addr)const {
    ofstream file;
    file.open(addr);

    file << this->clauses.size() << " " << this->literals.size() << endl;

    for(auto i: clauses)
    {
        linkedList *l = &i;
        while(l != nullptr && l->getElement() != -1)
        {
            file << l->getElement() << " ";
            l = l->getNext();
        }
        file << "0";
        file << endl;
    }

    file.close();
}

void CNF::generateSolutionFile(string addr) {
    ofstream file;
    file.open(addr);

    file << "Number of solutions: " << this->nbSolutionsFound << endl;

    for(int i = 0; i < solutions.size(); i++)
    {
       file << "solution n°" << i << ": [";
       for(int j = 0; j < solutions[i].size() - 1; j++)
       {
           file << solutions[i][j] << ",";
       }
       file << solutions[i].back() << "]" << endl;
    }

    file.close();
}
