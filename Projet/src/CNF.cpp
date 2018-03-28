//
// Created by raphael on 3/14/18.
//

#include <fstream>
#include <ctime>
#include <unistd.h>
#include <sstream>
#include "CNF.h"

void Generator::GenereFile (int nbClauses, int nbLiterals){
    ofstream myfile;
    myfile.open ("InfoClauses.txt");
    myfile << nbClauses << " " << nbLiterals << "\n";

    srand (time(NULL));

    for(int i = 0; i < nbClauses; i++){
        int nbLiteralsInLine = rand()%(nbLiterals/10) + 1;
        for(int j = 0; j < nbLiteralsInLine; j++)
        {
            myfile << rand()%(nbLiterals * 2) + 1 << " ";
        }
        myfile << "\n";
    }

    myfile.close();
}

void CNF::readFromFile(string addr) {
    std::ifstream infile(addr);
    std::string line;

    std::getline(infile, line);

    std::istringstream iss(line);
    int nbClauses, ;


    vector<clauseList> literals;
    vector<literalList> clauses;
    int i = 0;
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        int valIn = -1;
        do {
            iss >> valIn;
            clauses[i].addLiteral(valIn);
            literals[valIn].addClause(i);
        }while( valIn != 0);

        cout << clauses[i] << endl;

        i++;
    }
    this->literals = literals;
    this->clauses = clauses;

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
        int currentLiteral = -1, pureLiteral;
        executionTree = nodeToExplore.back();
        nodeToExplore.pop_back();

        //Unit propagation
        if(!UnitPropagation(executionTree))//Impossible state
            continue;

        //cout << *executionTree << endl;

        int max;
        //choose literal
        switch (h){
            case FIRST_SATISFY:
                max = 0;
                for(int i = 0; i < executionTree->getLiterals().size(); i++)
                {
                    cout << "count = " << executionTree->getLiterals()[i].countClauses() << endl;
                    if(executionTree->getLiterals()[i].countClauses() >= max){
                        max = executionTree->getLiterals()[i].countClauses();
                        currentLiteral = i;
                    }

                    if(currentLiteral%2 == 1)
                        currentNegLiteral = currentLiteral + 1;
                    else
                        currentNegLiteral = currentLiteral - 1;

                    if(executionTree->getLiterals()[currentNegLiteral].getClause() == -1){
                        pure = true;
                        pureLiteral = currentLiteral;
                    }

                }
                cout << currentLiteral << "::" << currentNegLiteral << "::" << pure << endl;
                break;
            case FIRST_FAIL:
                break;
            default:
                for(currentLiteral = 0; currentLiteral < executionTree->getLiterals().size(); currentLiteral++)
                {
                    if(executionTree->getLiterals()[currentLiteral].getClause() != -1)
                    {
                        if(currentLiteral%2 == 0)
                            currentNegLiteral = currentLiteral + 1;
                        else
                            currentNegLiteral = currentLiteral - 1;

                        if(executionTree->getLiterals()[currentNegLiteral].getClause() == -1){
                            pure = true;
                            pureLiteral = currentLiteral;
                        }

                        break;
                    }
                }
                break;
        }

        if(currentLiteral == executionTree->getLiterals().size() /*&& executionTree->getLiterals()[currentLiteral].getClause() == -1*/)
        {
            std::cout << "found model" << endl;
            solutions.push_back(executionTree->getCurrentModel());
            solutionsFound++;
            continue;
        }

        else{
            if(pure){
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

        sleep(1);
    }while(/*(!findAllSolution && (solutionsFound < nbSolution)) ||*/ !nodeToExplore.empty());
}

bool CNF::UnitPropagation(cnfExecutionTree *pTree){
    for (int i = 0; i < pTree->getClauses().size(); i++) {
        if(pTree->getClauses()[i].getNext() == nullptr && pTree->getClauses()[i].getLiteral() > 0){

            int currentLiteral = pTree->getClauses()[i].getLiteral(), currentNegLiteral;//-1 neccesary because of indices
            if(currentLiteral%2 == 1)//positive
                currentNegLiteral = currentLiteral + 1;
            else
                currentNegLiteral = currentLiteral - 1;

            //verify negation not also a unit clause
            for (auto &j : pTree->getClauses())
                if(j.getLiteral() == currentNegLiteral && j.getNext() == nullptr)
                    return false;

            pTree->assignLiteral(currentLiteral, currentNegLiteral);
        }
    }

    return true;
}

CNF::CNF(const vector<clauseList> &literals, const vector<literalList> &clauses) : literals(literals),
                                                                                   clauses(clauses) {}

const vector<clauseList> &CNF::getLiterals() const {
    return literals;
}

void CNF::setLiterals(const vector<clauseList> &literals) {
    CNF::literals = literals;
}

const vector<literalList> &CNF::getClauses() const {
    return clauses;
}

void CNF::setClauses(const vector<literalList> &clauses) {
    CNF::clauses = clauses;
}

const vector<vector<int>> &CNF::getSolutions() const {
    return solutions;
}

int CNF::getNbSolutionsFound() const {
    return nbSolutionsFound;
}

CNF::CNF() {}

