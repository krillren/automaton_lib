#include "Automaton.h"
#include "ctype.h"
#include "set"
#include "iostream"


namespace fa {

  Automaton::Automaton() {
    states = {};
    alphabet = {};
    transitions = {};
  }
  Automaton Automaton::create_copy() const{
    Automaton a = Automaton();
    for(State s : states){
      a.addState(s.number);
      if(s.final){
        a.setStateFinal(s.number);
      }
      if(s.initial){
        a.setStateInitial(s.number);
      }
    }
    for(char c : alphabet){
      a.addSymbol(c);
    }
    for(Transition t : transitions){
      a.addTransition(t.from,t.alpha,t.to);
    }
    return a;
  }
  
  bool Automaton::isValid() const {
    return !states.empty() && !alphabet.empty();
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
  std::size_t Automaton::countSymbols() const{
    return alphabet.size();
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
  bool Automaton::isStateInitial(int state) const{
    struct State st_cpy = {state,false,false};
    std::set<struct State>::iterator iter = states.find(st_cpy);
    if(iter != states.end()){
      return iter->initial;
    }
    return false;
  }

  void Automaton::setStateFinal(int state){
    struct State st_cpy = {state,false,false};
    std::set<struct State>::iterator iter = states.find(st_cpy);
    if(iter != states.end()){
      iter->final = true;
    }
  }
  bool Automaton::isStateFinal(int state) const{
    struct State st_cpy = {state,false,false};
    std::set<struct State>::iterator iter = states.find(st_cpy);
    if(iter != states.end()){
      return iter->final;
    }
    return false;
  }
  bool Automaton::addTransition(int from, char alpha, int to){
    if(hasState(from) && hasState(to) && (hasSymbol(alpha) || alpha == Epsilon)){
      struct Transition tr_added = {from,alpha,to};
      return transitions.insert(tr_added).second;
    }
    return false;
  }
  bool Automaton::removeTransition(int from, char alpha, int to){
    for(Transition t : transitions){
      if(t.from == from && t.alpha == alpha && t.to == to){
        return transitions.erase(t)>0;
      }
    }
    return false;
  }
  bool Automaton::hasTransition(int from, char alpha, int to) const{
    struct Transition tr = {from,alpha,to};
    return transitions.find(tr) != transitions.end();
  }
  std::size_t Automaton::countTransitions() const{
    return transitions.size();
  }
  void Automaton::prettyPrint(std::ostream& os) const {
    //initial states
    os << "Initial states:" << std::endl << '\t';
    for(State s : states){
      if(isStateInitial(s.number)){
        os << s.number << " ";
      }
    }
    //final states
    os << std::endl << "Final states:" << std::endl << '\t';
    for(State s : states){
      if(isStateFinal(s.number)){
        os << s.number << " ";
      }
    }
    //Transitions
    os << std::endl << "Transitions:" << std::endl << '\t';
    for(State s : states){
      os << "For state " << s.number << ":" << std::endl << "\t\t";
      for(char alpha : alphabet){
        os << "For letter " << alpha << ": ";
        for(Transition t : transitions){
          if(t.from == s.number && t.alpha == alpha){
            os << t.to << " ";
          }
        }
        os << std::endl << "\t\t";
      }
      os << std::endl << "\t";
    }
  }
  bool Automaton::hasEpsilonTransition() const{
    for(Transition t : transitions){
      if(t.alpha == Epsilon){
        return true;
      }
    }
    return false;
  }
  bool Automaton::hasTransitionAlpha(int from, char alpha) const{
    for(Transition t : transitions){
      if(t.from == from && t.alpha == alpha){
        return true;
      }
    }
    return false;
  }
  bool Automaton::isComplete() const{
    for(State s : states){
      for(char alpha : alphabet){
        if(!hasTransitionAlpha(s.number,alpha)){
          return false;
        }
      }
    }
    return true;
  }
  std::size_t Automaton::countTransitionAlpha(int from, char alpha) const{
    std::size_t count= 0;
    for(Transition t : transitions){
      if(t.from == from && t.alpha == alpha){
        count++;
      }
    }
    return count;
  }
  bool Automaton::isDeterministic() const{
    for(State s : states){
      for(char alpha : alphabet){
        if(countTransitionAlpha(s.number,alpha) > 1){
          return false;
        }
      }
    }
    return true;
  }
  Automaton createComplete(const Automaton& automaton){
    if(automaton.isComplete()){
      return automaton.create_copy();
    }
    

  }
}

