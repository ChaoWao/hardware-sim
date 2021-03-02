
#include <iostream>
#include "agenda.h"
#include "wire.h"
#include "primitive_funcs.h"
#include "run.h"

using namespace std;
void half_adder(wire *a, wire *b, wire *s, wire *c) {
    wire *d = new wire;
    wire *e = new wire;
    or_gate(a, b, d);
    and_gate(a, b, c);
    inverter(c, e);
    and_gate(d, e, s);
}

int main() {
    wire input_1, input_2, sum, carry;
    probe("sum", &sum);
    probe("carry", &carry);
    half_adder(&input_1, &input_2, &sum, &carry);
    input_1.set_signal(1);
    propagate();

    input_2.set_signal(1);
    propagate();
}
