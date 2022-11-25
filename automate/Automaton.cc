#include "Automaton.h"
#include "ctype.h"
#include "set"
#include "iostream"
#include "assert.h"


namespace fa {

  Automaton::Automaton() {
    states = {};
    alphabet = {};
    transitions = {};
  }
  std::set<struct State> Automaton::getStates() const {
    return states;
  }
  std::set<struct Transition> Automaton::getTransitions() const {
    return transitions;
  }
  std::set<char> Automaton::getAlphabet() const {
    return alphabet;
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
    std::set<Transition>::iterator it = transitions.begin();
    for(;it != transitions.end();){
      if(it->alpha == symbol){
        it = transitions.erase(it);
      }else{
        it++;
      }
    }

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
    assert(isValid());
    for(Transition t : transitions){
      if(t.alpha == Epsilon){
        return true;
      }
    }
    return false;
  }
  bool Automaton::hasTransitionAlpha(int from, char alpha) const{
    assert(isValid());
    for(Transition t : transitions){
      if(t.from == from && t.alpha == alpha){
        return true;
      }
    }
    return false;
  }
  bool Automaton::isComplete() const{
    assert(isValid());
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
    assert(isValid());
    bool has_initial = false;
    if(hasEpsilonTransition()){
      return false;
    }
    for(State s : states){
      if(isStateInitial(s.number)){
        if(has_initial){
          return false;
        }
        has_initial = true;
      }
      for(char alpha : alphabet){
        if(countTransitionAlpha(s.number,alpha) > 1){
          return false;
        }
      }
    }
    return has_initial;
  }
  int Automaton::add_uniq_state(){
    int state = 0;
    while(hasState(state)){
      state++;
    }
    addState(state);
    return state;
  }
  int Automaton::add_trash_state(){
    int trash_state = add_uniq_state();
    for (char alpha : alphabet){
      addTransition(trash_state,alpha,trash_state);
    }
    return trash_state;
  }
  void Automaton::completion(){
    
    int trash_state = add_trash_state();
    for(State s : states){
      for(char alpha : alphabet){
        if(!hasTransitionAlpha(s.number,alpha)){
          addTransition(s.number,alpha,trash_state);
        }
      }
    }
  }
  Automaton createComplete(const Automaton& automaton){
    Automaton complete = automaton.create_copy();
    if(!complete.isComplete()){
      complete.completion();
    }
    return complete;
  }
  void Automaton::get_accessible_states(int state, std::set<int>* accessible_state) const{
    accessible_state->insert(state);
    for(Transition t : transitions){
      if(t.from == state){
        get_accessible_states(t.to,accessible_state);
      }
    }
  }
  void Automaton::removeNonAccessibleStates(){
    assert(isValid());
    std::set<int> accessible_states = {};
    for (State s : states){
      if(isStateInitial(s.number)){
        get_accessible_states(s.number, &accessible_states);
      }
    }
    
    std::set<State>::iterator iter = states.begin();
    for(;iter != states.end();iter++){
      if(accessible_states.find(iter->number) == accessible_states.end()){
        iter = states.erase(iter);
      }
    }
  }

  void Automaton::get_coaccessible_states(int state, std::set<int>* coaccessible_state) const{
    coaccessible_state->insert(state);
    for(Transition t : transitions){
      if(t.to == state){
        get_coaccessible_states(t.from,coaccessible_state);
      }
    }
  }
  void Automaton::removeNonCoAccessibleStates(){
    assert(isValid());
    std::set<int> coaccessible_states = {};
    for (State s : states){
      if(isStateFinal(s.number)){
        get_coaccessible_states(s.number, &coaccessible_states);
      }
    }
    std::set<State>::iterator iter = states.begin();
    for(;iter != states.end();iter++){
      if(coaccessible_states.find(iter->number) == coaccessible_states.end()){
        iter = states.erase(iter);
      }
    }
  }
  bool Automaton::isLanguageEmpty() const{
    assert(isValid());
    Automaton copy = create_copy();
    copy.removeNonAccessibleStates();
    copy.removeNonCoAccessibleStates();
    return copy.countStates() == 0;
  }

  void Automaton::removeEpsilonTransitions(){
    std::set<Transition> epsilon_transitions = {};
    for(Transition t : transitions){
      if(t.alpha == Epsilon){
        epsilon_transitions.insert(t);
      }
    }
    for(Transition t : epsilon_transitions){
      removeTransition(t.from,t.alpha,t.to);
    }
    for(Transition t : epsilon_transitions){
      for(Transition t2 : transitions){
        if(t2.from == t.to){
          addTransition(t.from,t2.alpha,t2.to);
        }
      }
    }
  }
  Automaton Automaton::createProduct(const Automaton& lhs, const Automaton& rhs){
    assert(lhs.isValid());
    assert(rhs.isValid());
    Automaton product = Automaton();
    for(char alpha : lhs.getAlphabet()){
      product.addSymbol(alpha);
    }
    for(State s1 : lhs.getStates()){
      for(State s2 : rhs.getStates()){
        product.addState(s1.number * rhs.countStates() + s2.number);
      }
    }
    for(State s1 : lhs.getStates()){
      for(State s2 : rhs.getStates()){
        for(char alpha : lhs.getAlphabet()){
          for(Transition t1 : lhs.getTransitions()){
            for(Transition t2 : rhs.getTransitions()){
              if(t1.from == s1.number && t2.from == s2.number && t1.alpha == t2.alpha && t1.alpha == alpha){
                product.addTransition(s1.number * rhs.countStates() + s2.number, alpha, t1.to * rhs.countStates() + t2.to);
              }
            }
          }
        }
      }
    }
    for(State s1 : lhs.getStates()){
      for(State s2 : rhs.getStates()){
        if(lhs.isStateInitial(s1.number) && rhs.isStateInitial(s2.number)){
          product.setStateInitial(s1.number * rhs.countStates() + s2.number);
        }
        if(lhs.isStateFinal(s1.number) && rhs.isStateFinal(s2.number)){
          product.setStateFinal(s1.number * rhs.countStates() + s2.number);
        }
      }
    }
    return product;
  }


  bool Automaton::hasEmptyIntersectionWith(const Automaton& other) const{
    assert(isValid());
    assert(other.isValid());
    return createProduct(*this,other).isLanguageEmpty();
  }

  Automaton Automaton::createComplete(const Automaton& automaton){
    assert(automaton.isValid());
    return automaton;
  }
  Automaton Automaton::createMirror(const Automaton& automaton){
    assert(automaton.isValid());
    return automaton;
  }
  Automaton Automaton::createComplement(const Automaton& automaton){
    assert(automaton.isValid());
    return automaton;
  }
  Automaton Automaton::createDeterministic(const Automaton& other){
    assert(other.isValid());
    return other;
  }
  Automaton Automaton::createMinimalMoore(const Automaton& other){
    assert(other.isValid());
    return other;
  }
  Automaton Automaton::createMinimalBrzozowski(const Automaton& other){
    assert(other.isValid());
    return other;
  }
}


