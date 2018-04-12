//
// Created by raphael on 4/12/18.
//

#ifndef PROJETV2_0_GENERATOR_H
#define PROJETV2_0_GENERATOR_H


#include "CNF.h"

class generator {
public:
    enum problem {PIGEON, RAMSEY, CHESS, SAT3};
private:
    CNF cnf;
    problem pb;
    int sizeProblem;
public:
    generator(problem pb, int sizeProblem);

    CNF &getCnf();

    problem getPb() const;

    int getSizeProblem() const;

    void generatePigeon(int nbPigeon);

    void genrateLiterals(int i);

    void generateChess(int boardSize);

    int generateVariable(int a, int b, int offset);
};


#endif //PROJETV2_0_GENERATOR_H
