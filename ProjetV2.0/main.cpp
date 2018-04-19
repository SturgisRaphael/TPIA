#include <iostream>
#include "src/linkedList.h"
#include "src/CNF.h"
#include "src/generator.h"
#include <vector>

using namespace std;

int main() {
/*
    string fileName;
    int nbNoeud = 0;
    int start_s, stop_s;

    cout << "Pigeon:" << endl;
    for(int i = 2; i < 8; i++)
    {
        fileName = "data/pigeon" + to_string(i);
        generator gen = generator(generator::PIGEON, i);
        gen.getCnf().generateProblemFile(fileName + ".pb");

        start_s=clock();
        nbNoeud = gen.getCnf().solve(CNF::NO);
        stop_s=clock();

        cout << "n/a," << i << "," << nbNoeud << "," << stop_s - start_s << endl;
        gen.getCnf().generateSolutionFile(fileName + "_NO.sol");

        gen = generator(generator::PIGEON, i);
        start_s=clock();
        nbNoeud = gen.getCnf().solve(CNF::FIRST_SATISFY);
        stop_s=clock();

        cout << "FIRST_SATISFY," << i << "," << nbNoeud << "," << stop_s - start_s << endl;
        gen.getCnf().generateSolutionFile(fileName + "_FS.sol");

        gen = generator(generator::PIGEON, i);
        start_s=clock();
        nbNoeud = gen.getCnf().solve(CNF::FIRST_FAIL);
        stop_s=clock();

        cout << "FIRST_FAIL," << i << "," << nbNoeud << "," << stop_s - start_s << endl;
        gen.getCnf().generateSolutionFile(fileName + "_FF.sol");
    }

    cout << "Dames:" << endl;
    for(int i = 2; i < 8; i++)
    {
        fileName = "data/dames" + to_string(i);
        generator gen = generator(generator::CHESS, i);
        gen.getCnf().generateProblemFile(fileName + ".pb");

        start_s=clock();
        nbNoeud = gen.getCnf().solve(CNF::NO);
        stop_s=clock();

        cout << "n/a," << i << "," << nbNoeud << "," << stop_s - start_s << endl;
        gen.getCnf().generateSolutionFile(fileName + "_NO.sol");

        gen = generator(generator::CHESS, i);
        start_s=clock();
        nbNoeud = gen.getCnf().solve(CNF::FIRST_SATISFY);
        stop_s=clock();

        cout << "FIRST_SATISFY," << i << "," << nbNoeud << "," << stop_s - start_s << endl;
        gen.getCnf().generateSolutionFile(fileName + "_FS.sol");

        gen = generator(generator::CHESS, i);
        start_s=clock();
        nbNoeud = gen.getCnf().solve(CNF::FIRST_FAIL);
        stop_s=clock();

        cout << "FIRST_FAIL," << i << "," << nbNoeud << "," << stop_s - start_s << endl;
        gen.getCnf().generateSolutionFile(fileName + "_FF.sol");
    }

    cout << "3-SAT:" << endl;
    for(int i = 2; i < 40; i++)
    {
        fileName = "data/3_sat" + to_string(i);
        generator gen = generator(generator::SAT3, i);
        gen.getCnf().generateProblemFile(fileName + ".pb");

        start_s=clock();
        nbNoeud = gen.getCnf().solve(CNF::NO);
        stop_s=clock();

        cout << "n/a," << i << "," << nbNoeud << "," << stop_s - start_s << endl;
        gen.getCnf().generateSolutionFile(fileName + "_NO.sol");

        gen = generator(generator::SAT3, i);
        start_s=clock();
        nbNoeud = gen.getCnf().solve(CNF::FIRST_SATISFY);
        stop_s=clock();

        cout << "FIRST_SATISFY," << i << "," << nbNoeud << "," << stop_s - start_s << endl;
        gen.getCnf().generateSolutionFile(fileName + "_FS.sol");

        gen = generator(generator::SAT3, i);
        start_s=clock();
        nbNoeud = gen.getCnf().solve(CNF::FIRST_FAIL);
        stop_s=clock();

        cout << "FIRST_FAIL," << i << "," << nbNoeud << "," << stop_s - start_s << endl;
        gen.getCnf().generateSolutionFile(fileName + "_FF.sol");
    }
*/

    CNF cnf;

    return 0;
}