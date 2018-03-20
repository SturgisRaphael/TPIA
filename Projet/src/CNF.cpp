//
// Created by raphael on 3/14/18.
//

#include <fstream>
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
    ifstream myfile;
    myfile.open(addr);
    string line;
    getline(myfile, line);
    int nbClauses =

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

void CNF::solve(int nbSolutions, heuristic h) {

}
