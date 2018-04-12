//
// Created by raphael on 4/12/18.
//

#include <iostream>
#include "generator.h"

generator::generator(generator::problem pb, int sizeProblem) : pb(pb), sizeProblem(sizeProblem) {
    switch (pb){
        case PIGEON:
            generatePigeon(sizeProblem);
            break;
        case RAMSEY:break;
        case CHESS:
            generateChess(sizeProblem);
            break;
        case SAT3:break;
    }
}

void generator::generatePigeon(int nbPigeon) {
    if (nbPigeon < 2){
        cerr << "Error: number of pigeons < 2" << endl;
    }
    else
    {
        int indexClause = 0;
        for(int p = 0; p < nbPigeon; p++)
        {
            linkedList l = linkedList();
            for(int h = 0; h < nbPigeon - 1; h++)
            {
                l.addElement(((p * (nbPigeon - 1) + h) * 2) + 1);
            }
            this->cnf.getClauses().push_back(l);
        }
        for(int h = 0; h < nbPigeon-1; h++)
        {
            for(int i = 0; i < nbPigeon; i++)
            {
                for(int j = i + 1; j < nbPigeon; j++)
                {
                    linkedList l = linkedList();
                    l.addElement(((i * (nbPigeon - 1) + h) * 2) + 2);
                    l.addElement(((j * (nbPigeon - 1) + h) * 2) + 2);
                    this->cnf.getClauses().push_back(l);
                }
            }
        }
        genrateLiterals(nbPigeon * (nbPigeon - 1));
    }
}

void generator::generateChess(int boardSize) {
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            for(int k = j + 1; k < boardSize; k++)
            {
                linkedList l1 = linkedList();
                l1.addElement(((i * (boardSize) + j) * 2) + 2);
                l1.addElement(((i * (boardSize) + k) * 2) + 2);
                this->cnf.getClauses().push_back(l1);
            }
        }
    }

    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
            for(int k = j + 1; k < boardSize; k++)
            {
                linkedList l2 = linkedList();
                l2.addElement(((j * (boardSize) + i) * 2) + 2);
                l2.addElement(((k * (boardSize) + i) * 2) + 2);
                this->cnf.getClauses().push_back(l2);
            }
        }
    }

    for(int d = 0; d <= boardSize; d++)
    {
        for(int j = 0; j <= boardSize - d; j++)
        {
            for(int k = j + 1; k <= boardSize - 1 - d; k++)
            {
                linkedList l1 = linkedList();
                l1.addElement((((d+j) * (boardSize) + j) * 2) + 2);
                l1.addElement((((d+k) * (boardSize) + k) * 2) + 2);
                this->cnf.getClauses().push_back(l1);
            }
        }
    }

    for(int d = -(boardSize - 2); d <= -1; d++)
    {
        for(int j = 0; j < boardSize + d; j++)
        {
            for(int k = j + 1; k < boardSize + d; k++)
            {
                linkedList l1 = linkedList();
                l1.addElement(((j * (boardSize) + (j - d)) * 2) + 2);
                l1.addElement(((k * (boardSize) + (k - d)) * 2) + 2);
                this->cnf.getClauses().push_back(l1);
            }
        }
    }

    for(int d = 1; d <= boardSize - 1; d++)
    {
        for(int j = 0; j < d; j++)
        {
            for(int k = j + 1; k <= d; k++)
            {
                linkedList l1 = linkedList();
                l1.addElement(((j * (boardSize) + d - j) * 2) + 2);
                l1.addElement(((k * (boardSize) + d - k) * 2) + 2);
                this->cnf.getClauses().push_back(l1);
            }
        }
    }


    for(int d = 1; d < boardSize; d++)
    {
        for(int j = d ; j < boardSize; j++)
        {
            for(int k = j + 1; k < boardSize; k++)
            {
                linkedList l1 = linkedList();
                l1.addElement((generateVariable(j, boardSize + d - j - 1, boardSize) * 2) + 2);
                l1.addElement((generateVariable(k, boardSize + d - k - 1, boardSize) * 2) + 2);
                this->cnf.getClauses().push_back(l1);
            }
        }
    }

    for(int i = 0; i < boardSize; i++)
    {
        linkedList l = linkedList();
        for(int j = 0; j < boardSize; j++)
        {
            l.addElement((i * boardSize + j) * 2 + 1);
        }
        this->getCnf().getClauses().push_back(l);
    }
    genrateLiterals(boardSize * boardSize);
}

void generator::genrateLiterals(int i) {
    vector<linkedList> vect = cnf.getClauses();
    for(int j = 0; j < i*2; j++)
    {
        linkedList l = linkedList();
        for(int k= 0; k < vect.size(); k++)
        {
            if(vect[k].isInList(j + 1))
                l.addElement(k+1);
        }
        cnf.getLiterals().push_back(l);
    }
}

int generator::generateVariable(int a, int b, int offset) {
    return a*offset + b;
}

CNF &generator::getCnf(){
    return cnf;
}

generator::problem generator::getPb() const {
    return pb;
}

int generator::getSizeProblem() const {
    return sizeProblem;
}