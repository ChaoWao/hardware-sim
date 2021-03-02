
#ifndef WIRE_H
#define WIRE_H

#include <vector>

#define ZERO 0
#define ONE 1

using namespace std;

class action {
public:
    vector<void *> input;
    vector<void *> output;
    void (*f)(vector<void *>, vector<void *>);
};

class wire {
private:
	int signal_value;
    vector<action> action_procedures;
	
public:
	wire() {
        signal_value = ZERO;
    }

    int get_signal() {
        return signal_value;
    }
	void set_signal(int v) {
        if (signal_value != v) {
            signal_value = v;
            for (auto it = action_procedures.cbegin(); it != action_procedures.cend(); it++) {
                (*it).f((*it).input, (*it).output);
            }
        }
    }
    void add_action(action a) {
        action_procedures.insert(action_procedures.cbegin(), a);
        a.f(a.input, a.output);
    }
};

#endif