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
        case CHESS:break;
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
                l.addElement(((p * nbPigeon + h) * 2) + 1);
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
                    l.addElement(((i * nbPigeon + h) * 2) + 2);
                    l.addElement(((j * nbPigeon + h) * 2) + 2);
                    this->cnf.getClauses().push_back(l);
                }
            }
        }
    }
}
