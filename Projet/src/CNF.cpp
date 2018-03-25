//
// Created by raphael on 3/14/18.
//

#include <fstream>
#include <sstream>
#include <time.h>
#include "CNF.h"
#include "cnfExecutionTree.h"

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
    ifstream myfile;
    myfile.open(addr);
    string line;
    getline(myfile, line);
    int nbClauses;

    while ( getline(myfile, line)){
        string delimiter = " ";

        size_t pos = 0;
        string token;
        while ((pos = line.find(delimiter)) != string::npos) {
            token = line.substr(0, pos);
            int literal = atoi(token.c_str());

            line.erase(0, pos + delimiter.length());
        }
        cout << line << endl;
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
    cnfExecutionTree *executionTree;
    cnfExecutionTree root = cnfExecutionTree(this->literals, this->clauses);
    bool findAllSolution = false;
    if(nbSolution < 0)
        findAllSolution = true;

    vector<cnfExecutionTree *> nodeToExplore;
    nodeToExplore.push_back(&root);

    literalList *tmp;

    do{
        int currentLiteral = -1;
        executionTree = nodeToExplore.back();
        nodeToExplore.pop_back();

        //Unit propagation
        if(!UnitPropagation(executionTree))//Impossible state
            continue;

        //PureLiteral


        //choose literal
        switch (h){
            case FIRST_SATISFY:
                break;
            case FIRST_FAIL:
                break;
            default:
                for(currentLiteral = 0; currentLiteral < literals.size(); currentLiteral++)
                {
                    if(literals[currentLiteral].getClause() > 0)
                    {
                        if(currentLiteral%2 == 0)
                            currentNegLiteral = currentLiteral + 1;
                        else
                            currentNegLiteral = currentLiteral - 1;

                        if(literals[currentNegLiteral].getClause() == -1);
                            //TODO: pure literal

                        break;
                    }
                }
                break;
        }

        if(currentLiteral == literals.size())
        {
            printf("found model\n");
            continue;
        }

        //explore left


        //explore right

    }while((!findAllSolution && (solutionsFound < nbSolution)) && !nodeToExplore.empty());
}

bool CNF::UnitPropagation(cnfExecutionTree *pTree) {
    for (int i = 0; i < pTree->getClauses().size(); i++) {
        if(pTree->getClauses()[i].getNext() == nullptr && pTree->getClauses()[i].getLiteral() > 0){

            int currentLiteral = pTree->getClauses()[i].getLiteral() - 1, currentNegLiteral;//-1 neccesary because of indices
            if(currentLiteral%2 == 0)//positive
                currentNegLiteral = currentLiteral + 1;
            else
                currentNegLiteral = currentLiteral - 1;

            printf("lit = %d, negLit = %d\n", currentLiteral, currentNegLiteral);

            //verify negation not also a unit clause
            for (auto &j : pTree->getClauses())
                if(j.getLiteral() == currentNegLiteral + 1 && j.getNext() == nullptr)
                    return false;

            //remove clauses with currentLiteral
            clauseList *currentClause = &pTree->getLiterals()[currentLiteral];
            while(currentClause != nullptr){
                pTree->getClauses()[currentClause->getClause() - 1].setLiteral(-1);
                pTree->getClauses()[currentClause->getClause() - 1].setNext(nullptr);

                //remove from litteral list
                //printf("clause = %d\n", currentClause->getClause());
                for(int j = 0; j < pTree->getLiterals().size(); j++)
                {
                    std::cout << pTree->getLiterals()[j] << endl;
                    pTree->getLiterals()[j].removeClause(currentClause->getClause());
                }

                currentClause = currentClause->getNext();
            }

            pTree->getLiterals()[currentLiteral].setNext(nullptr);
            pTree->getLiterals()[currentLiteral].setClause(-1);

            //remove currentNegLiterals from all clauses
            if(pTree->getLiterals()[currentNegLiteral].getClause() > 0)//there are NegLiterals to remove
            {
                currentClause = &pTree->getLiterals()[currentNegLiteral];
                while (currentClause != nullptr) {
                    pTree->getClauses()[currentClause->getClause() - 1].deleteLiteral(currentNegLiteral + 1);

                    currentClause = currentClause->getNext();
                }
            }

            pTree->getLiterals()[currentNegLiteral].setNext(nullptr);
            pTree->getLiterals()[currentNegLiteral].setClause(-1);

            pTree->getClauses()[i].setLiteral(-1);
            pTree->getCurrentModel().push_back(currentLiteral + 1);
        }
    }

    return true;
}

