//
// Created by raphael on 4/12/18.
//

#ifndef PROJETV2_0_GENERATOR_H
#define PROJETV2_0_GENERATOR_H


#include "CNF.h"

class generator {
    enum problem {PIGEON, RAMSEY, CHESS, SAT3};
private:
    CNF cnf;
    problem pb;
    int sizeProblem;
public:
    generator(problem pb, int sizeProblem);

    void generatePigeon(int nbPigeon);
};


#endif //PROJETV2_0_GENERATOR_H
