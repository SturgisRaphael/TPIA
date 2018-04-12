#include <iostream>
#include "src/linkedList.h"
#include "src/CNF.h"
#include <vector>

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;

    //Generator::GenereFile (20, 50);

    //CNF::readFromFile("InfoClauses.txt");

    /*
     * c1 = a | b | c
     * c2 = -a | b | c
     * c3 = a
     * a=1, -a = 2, b = 3, -b = 4, c = 5, -c = 6
     * */
    linkedList clauseList1 = linkedList(1);
    clauseList1.addElement(3);

    linkedList clauseList2 = linkedList(2);

    linkedList clauseList3 = linkedList(1);
    clauseList3.addElement(2);

    linkedList clauseList4;

    linkedList clauseList5 = linkedList(1);
    clauseList5.addElement(2);

    linkedList clauseList6;

    linkedList literalList1 = linkedList(1);
    literalList1.addElement(3);
    literalList1.addElement(5);

    linkedList literalList2 = linkedList(2);
    literalList2.addElement(3);
    literalList2.addElement(5);

    linkedList literalList3 = linkedList(1);

    vector<linkedList> literals = {clauseList1, clauseList2, clauseList3, clauseList4, clauseList5, clauseList6};
    vector<linkedList> clauses = {literalList1, literalList2, literalList3};

    CNF cnf = CNF(literals, clauses);

    cout << cnf << endl;

    cnf.solve();

    cout << cnf << endl;


    for(auto &i : cnf.getSolutions())
    {
        for(auto &j : i)
            cout << j << ",";
        cout << endl;
    }

    cout << endl;

    return 0;
}