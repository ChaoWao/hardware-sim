
#ifndef AGENDA_H
#define AGENDA_H

#include <iostream>
#include <vector>
#include <queue>
#include "wire.h"

using namespace std;

class time_segment {
private:
    int time;
    queue<pair<void *, int>> update_wires;
public:
    time_segment(int t, queue<pair<void *, int>> q) {
        time = t;
        update_wires = q;
    }
    int segment_time() {
        return time;
    }
    queue<pair<void *, int>>& segment_queue() {
        return update_wires;
    }
};

class agenda {
private:
    int curr_time;
    vector<time_segment> time_segms;
public:
	agenda() {
		curr_time = 0;
	}
    int current_time() {
        return curr_time;
    }
    void set_current_time(int t) {
        curr_time = t;
    }
    vector<time_segment>& segments() {
        return time_segms;
    }
};

static agenda agen;

static agenda& get_agenda() {
	return agen;
}

void add_to_agenda(int t, pair<void *, int> uw) {
	auto& time_segms = agen.segments();
	auto curr_time = agen.current_time();

	auto it = time_segms.begin();
	for (; it != time_segms.end(); it++) {
		if (t <= (*it).segment_time()) {
			break;
		}
	}
	if (time_segms.size() == 0 || t < curr_time) {
		queue<pair<void *, int>> q;
		q.push(uw);
		time_segment ts(t, q);
		time_segms.insert(time_segms.cbegin(), ts);
	} else {
		if (t == (*it).segment_time()) {
			(*it).segment_queue().push(uw);
		} else {
			queue<pair<void *, int>> q;
			q.push(uw);
			time_segment ts(t, q);
			time_segms.insert(it, ts);
		}
	}
}

void remove_first_agenda_item() {
	auto& time_segms = agen.segments();
	auto& u_wires = time_segms[0].segment_queue();
	u_wires.pop();
	if (u_wires.empty()) {
		time_segms.erase(time_segms.begin());
	}
}

pair<void *, int> first_agenda_item() {
	auto& time_segms = agen.segments();
	if (time_segms.empty()) {
		cout << "Agenda is empty: FIRST_AGENDA_ITEM" << endl;
		exit(EXIT_FAILURE);
	} else {
		auto first_segm = time_segms[0];
		agen.set_current_time(first_segm.segment_time());
		return first_segm.segment_queue().front();
	}
}

#endif
