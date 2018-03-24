#include <iostream>
#include "src/CNF.h"
#include "src/cnfExecutionTree.h"
#include "src/clauseList.h"
#include "src/literalList.h"

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
    clauseList clauseList1 = clauseList(1);
    clauseList1.setNext(new clauseList(3));

    clauseList clauseList2 = clauseList(2);

    clauseList clauseList3 = clauseList(1);
    clauseList3.addClause(2);

    clauseList clauseList4;

    clauseList clauseList5 = clauseList(1);
    clauseList5.addClause(2);

    clauseList clauseList6;

    literalList literalList1 = literalList(1);
    literalList1.addLiteral(3);
    literalList1.addLiteral(5);

    literalList literalList2 = literalList(2);
    literalList2.addLiteral(3);
    literalList2.addLiteral(5);

    literalList literalList3 = literalList(1);

    vector<clauseList> literals = {clauseList1, clauseList2, clauseList3, clauseList4, clauseList5, clauseList6};
    vector<literalList> clauses = {literalList1, literalList2, literalList3};

    cnfExecutionTree tree = cnfExecutionTree(literals, clauses);

    cout << "Before: " << tree << endl;

    cout << "return = " << CNF::UnitPropagation(&tree) << endl;

    cout << "After: " << tree << endl;

    return 0;
}