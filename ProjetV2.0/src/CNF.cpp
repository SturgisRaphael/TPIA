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

int CNF::solve() {
    return solve(-1, NO);
}

int CNF::solve(CNF::heuristic h) {
    return solve(-1, h);
}

int CNF::solve(int nbSolution, CNF::heuristic h) {
    int solutionsFound = 0;
    int nbNoeud = 0;
    vector<int > currentSolution;
    int currentLiteral, currentNegLiteral;
    cnfExecutionTree *executionTree;
    cnfExecutionTree *left;
    cnfExecutionTree *right;
    cnfExecutionTree root = cnfExecutionTree(this->literals, this->clauses);
    bool findAllSolution = false;
    if(nbSolution < 0)
        findAllSolution = true;

    vector<cnfExecutionTree *> nodeToExplore;
    nodeToExplore.push_back(&root);

    do{
        nbNoeud++;
        currentLiteral = -1;
        executionTree = nodeToExplore.back();
        nodeToExplore.pop_back();

        //Unit propagation
        if(!executionTree->UnitPropagation())//Impossible state
            continue;

        //choose literal
        switch (h){
            case FIRST_SATISFY:
                currentLiteral = executionTree->firstSatisfyHeuristic();
                break;
            case FIRST_FAIL:
                currentLiteral = executionTree->firstFailHeuristic();
                break;
            default:
                currentLiteral = executionTree->noHeuristic();
                break;
        }
        currentNegLiteral = negationOfVariable(currentLiteral + 1) - 1;

        if(currentLiteral == -1 || executionTree->getLiterals()[currentLiteral].getElement() == -1)
        {
            solutions.push_back(executionTree->getCurrentModel());
            solutionsFound++;
            continue;
        }

        else{
            if(executionTree->isPureLiteral(currentLiteral + 1)){
                if(!findAllSolution)
                {
                    //explore right
                    right = new cnfExecutionTree(executionTree->getLiterals(), executionTree->getClauses(), executionTree->getCurrentModel());
                    right->assignLiteral(currentLiteral + 1);

                    nodeToExplore.push_back(right);
                    continue;
                }
            }

            cnfExecutionTree *tmp = new cnfExecutionTree(executionTree->getLiterals(), executionTree->getClauses(), executionTree->getCurrentModel());

            //explore left
            left = new cnfExecutionTree(executionTree->getLiterals(), executionTree->getClauses(), executionTree->getCurrentModel());
            left->assignLiteral(currentNegLiteral + 1);

            executionTree = tmp;

            //explore right
            right = new cnfExecutionTree(executionTree->getLiterals(), executionTree->getClauses(), executionTree->getCurrentModel());
            right->assignLiteral(currentLiteral + 1);

            nodeToExplore.push_back(left);
            nodeToExplore.push_back(right);
        }

    }while((!findAllSolution && (solutionsFound < nbSolution)) || !nodeToExplore.empty());
    nbSolutionsFound = solutionsFound;
    return nbNoeud;
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

int CNF::negationOfVariable(int literal) {
    if(literal%2 == 1)
        return literal + 1;
    else
        return literal - 1;

}
