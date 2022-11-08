#include "Automaton.h"
#include "ctype.h"
#include "set"


namespace fa {

  Automaton::Automaton() {
    states = {};
    alphabet = {};
    transitions = {};
  }
  
  bool Automaton::isValid() const {
    return !(states.empty()||transitions.empty());
  }

  bool Automaton::addSymbol(char symbol){
    if(symbol != Epsilon && isgraph(symbol)){
      return alphabet.insert(symbol).second;
    }
    return false;
  }
  bool Automaton::removeSymbol(char symbol){
    return alphabet.erase(symbol) >0;
  }
  bool Automaton::hasSymbol(char symbol) const{
    return alphabet.find(symbol) != alphabet.end();
  }
  bool Automaton::addState(int state){
    return addState(state,false,false);
  }
  bool Automaton::addState(int state,bool final,bool initial){
    struct State added_state;
    added_state.number = state;
    added_state.final = final;
    added_state.initial = initial;
    return states.insert(added_state).second;
  }
  bool Automaton::removeState(int state){
    struct State st_cpy = {state,false,false};
    return states.erase(st_cpy) > 0;
  }
  bool Automaton::hasState(int state) const{
    struct State st_cpy = {state,false,false};
    return states.find(st_cpy) != states.end();
  }
  std::size_t Automaton::countStates() const{
    return states.size();
  }
  void Automaton::setStateInitial(int state){
    struct State st_cpy = {state,false,false};
    std::set<struct State>::iterator iter = states.find(st_cpy);
    if(iter != states.end()){
      iter->initial = true;
    }
  }
  void Automaton::setStateFinal(int state){
    
  }

}

