#ifndef RUN_H
#define RUN_H

#include <iostream>
#include <vector>
#include <string>
#include "agenda.h"
#include "wire.h"

#define ZERO 0
#define ONE 1
#define INVERTER_DELAY 2
#define AND_GATE_DELAY 3
#define OR_GATE_DELAY 5

using namespace std;

static void inverter_func(vector<void *> input, vector<void *> output) {
    if (input.size() != 1 || output.size() != 1) {
        cout << "Inverter Arguments Error!" << endl;
        exit(EXIT_FAILURE);
    }
    int value = ((wire *)(input[0]))->get_signal() == ONE ? ZERO : ONE;
    add_to_agenda(get_agenda().current_time()+INVERTER_DELAY, make_pair(output[0], value));
}

void inverter(wire *a, wire *b) {
	vector<void *> input, output;
	action act;
	input.insert(input.begin(), a);
	output.insert(output.begin(), b);
	act.input = input;
	act.output = output;
	act.f = inverter_func;
	a->add_action(act);
	b->add_action(act);
}


static void and_gate_func(vector<void *> input, vector<void *> output) {
    if (input.size() != 2 || output.size() != 1) {
        cout << "And Gate Arguments Error!" << endl;
        exit(EXIT_FAILURE);
    }
    int value = ((wire *)(input[0]))->get_signal() && ((wire *)(input[1]))->get_signal();
    add_to_agenda(get_agenda().current_time()+AND_GATE_DELAY, make_pair(output[0], value));
}

void and_gate(wire *a, wire *b, wire *c) {
	vector<void *> input, output;
	action act;
	input.insert(input.begin(), a);
	input.insert(input.end(), b);
	output.insert(output.begin(), c);
	act.input = input;
	act.output = output;
	act.f = and_gate_func;
	a->add_action(act);
	b->add_action(act);
}

static void or_gate_func(vector<void *> input, vector<void *> output) {
    if (input.size() != 2 || output.size() != 1) {
        cout << "Or Gate Arguments Error!" << endl;
        exit(EXIT_FAILURE);
    }
    int value = ((wire *)(input[0]))->get_signal() || ((wire *)(input[1]))->get_signal();
    add_to_agenda(get_agenda().current_time()+OR_GATE_DELAY, make_pair(output[0], value));
}

void or_gate(wire *a, wire *b, wire *c) {
	vector<void *> input, output;
	action act;
	input.insert(input.begin(), a);
	input.insert(input.end(), b);
	output.insert(output.begin(), c);
	act.input = input;
	act.output = output;
	act.f = or_gate_func;
	a->add_action(act);
	b->add_action(act);
}

void probe_func(vector<void *> input, vector<void *> output) {
	if (input.size() != 1 || output.size() != 1) {
		cout << "Inverter Arguments Error!" << endl;
		exit(EXIT_FAILURE);
	} else {
		cout << *((string *)(input[0])) << " " << get_agenda().current_time() << "  New-value = " << ((wire *)(output[0]))->get_signal() << endl;
	}
}

void probe(string s, wire * w) {
	string *ss = new string;
	*ss = s;
	vector<void *> input, output;
	action act;
	input.insert(input.begin(), ss);
	output.insert(output.begin(), w);
	act.input = input;
	act.output = output;
	act.f = probe_func;
	w->add_action(act);
}

void propagate() {
	agenda& agen = get_agenda();
	vector<time_segment>& time_segms = agen.segments();
	if (time_segms.size() != 0) {
			pair<void *, int> p = first_agenda_item();
			((wire *)(p.first))->set_signal(p.second);
			remove_first_agenda_item();
		propagate();
	}
}

#endif