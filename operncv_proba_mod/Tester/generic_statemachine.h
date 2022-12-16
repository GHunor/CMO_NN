//
// Created by ghuno on 2022-03-22.
//

#ifndef TESTER_GENERIC_STATEMACHINE_H
#define TESTER_GENERIC_STATEMACHINE_H
#include "named_vector.hpp"

class state_machine{
    //std::vector<bool> dependencies;
    //std::map<std::string,int> dependencies_names;

    named_vector<bool> dependencies;
    struct state{
        int ID;
        std::string name;
        std::vector<std::pair<state*,complex_id> next_states;
    };
    std::vector<state> states;
    void connect(state A, state B, complex_id Dep){
        states[A.ID]
    }

};

#endif //TESTER_GENERIC_STATEMACHINE_H
