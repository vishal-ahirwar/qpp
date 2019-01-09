// Used for testing, do not use it as an example
#include <iostream>

#include "qpp.h"
#include "experimental/experimental.h"

int main() {
    using namespace qpp;
    using namespace qpp::experimental;

    QCircuit circ{10, 10};
    // circ.apply(gt.X, 7, "X gate on qubit 7");
    circ.measureV(gt.X, 4, 0, "Initial measurement on qubit 4");
    circ.apply(gt.X, 2, "X gate on qubit 2");
    circ.apply(gt.CNOT, 1, 3, "CNOT on 1 3");
    circ.measureZ(2, 0, "Z meas on qubit 2");
    circ.apply(gt.TOF, 5, 3, 6, "TOF on 5 3 6");
    circ.measureZ(6, 0);
    circ.measureZ(9, 0);
    circ.CTRL(gt.X, 6, 7, "Control X 6->7");
    circ.measureV(gt.H, 0, 0, "Measure in X basis");
    circ.apply(gt.Y, 8);
    circ.measureKs({std::sqrt(2) * gt.X, std::sqrt(2) * gt.Z}, 7, 0, "Kraus");
    circ.measureZ(8, 0);
    circ.apply(gt.Z, {1, 2, 3}, "Z on 1 2 3");
    circ.measureZ(5, 9);
    // circ.apply(gt.TOF, 4, 6, 7, "TOF 4 6 7");

    std::cout << circ << std::endl;

    QCircuit test{10, 1, 2, "some circuit"};

    test.measureZ(1, 0);
    test.measureZ(3, 0);

    std::cout << test << '\n';

    QCircuit bell{2};
    bell.apply_many(gt.X, {0, 1});
    bell.apply(gt.H, 0);
    //bell.apply(gt.CNOT, {0, 1});
    bell.CTRL(gt.X, 0, 1);
    bell.CTRL(gt.X, std::vector<idx>{0}, std::vector<idx>{1}); // FIXME
    //bell.CTRL(gt.X, 0, 1);
    bell.CTRL_custom(gt.X, {0}, {1});

    bell.run();

    std::cout << disp(bell.get_psi()) << '\n';

    std::cout << bell << '\n';
}
