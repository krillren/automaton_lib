
#include "gtest/gtest.h"

#include "Automaton.h"
/*
  test isValid()
*/
//test isValid everything empty
TEST(isValid, everything_empty) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isValid());
}
//test isValid symbol empty
TEST(isValid, symbol_empty){
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_FALSE(fa.isValid());
}
//test isValid state empty
TEST(isValid, state_empty){
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_FALSE(fa.isValid());
}
//test isValid nothing empty
TEST(isValid, nothing_empty){
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addState(1);
  EXPECT_TRUE(fa.isValid());
}
/*
  test addSymbol()
*/
//test addSymbol add one symbol
TEST(addSymbol, add_one_symbol){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('a'));
}
//test addSymbol add multiple symbol
TEST(addSymbol, add_multiple_symbol){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
  EXPECT_TRUE(fa.addSymbol('b'));
  EXPECT_TRUE(fa.addSymbol('c'));
  EXPECT_TRUE(fa.hasSymbol('a'));
  EXPECT_TRUE(fa.hasSymbol('b'));
  EXPECT_TRUE(fa.hasSymbol('c'));
}
//test addSymbol add same symbol
TEST(addSymbol, add_same_symbol){
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_FALSE(fa.addSymbol('a'));
}
//test addSymbol add epsilon TODO

//test addSymbol add non ascii
TEST(addSymbol, add_empty){
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol(' '));
  EXPECT_FALSE(fa.hasSymbol(' '));
}
//test addSymbol add epsilon
TEST(addSymbol, add_epsilon){
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol(fa::Epsilon));
}

/*
  test removeSymbol()
*/
//test removeSymbol remove one symbol
TEST(removeSymbol, remove_one_symbol){
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.hasSymbol('a'));
}
//test removeSymbol remove multiple symbol
TEST(removeSymbol, remove_two_symbol){
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_TRUE(fa.removeSymbol('b'));
  EXPECT_TRUE(fa.removeSymbol('c'));
  EXPECT_FALSE(fa.hasSymbol('a'));
  EXPECT_FALSE(fa.hasSymbol('b'));
  EXPECT_FALSE(fa.hasSymbol('c'));
}
//test removeSymbol remove same symbol
TEST(removeSymbol, remove_same_symbol){
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.removeSymbol('a'));
}
//test removeSymbol remove inexistent symbol
TEST(removeSymbol, remove_inexistent_symbol){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('a'));
}
//test removeSymbol remove epsilon
TEST(removeSymbol, remove_epsilon){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol(fa::Epsilon));
}
//test removeSymbol remove epsilon TODO

/*
  test hasSymbol()
*/
//test hasSymbol has one symbol
TEST(hasSymbol, has_one_symbol){
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_TRUE(fa.hasSymbol('a'));
}
//test hasSymbol epsilon
TEST(hasSymbol, has_epsilon){
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasSymbol(fa::Epsilon));
}
//test hasSymbol has epsilon TODO
/*
  test countSymbols()
*/
//test countSymbols count empty alphabet
TEST(countSymbols, empty_alphabet){
  fa::Automaton fa;
  EXPECT_EQ(fa.countSymbols(), 0UL);
}
//test countSymbols count one symbol
TEST(countSymbols, one_symbol){
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_EQ(fa.countSymbols(), 1UL);
}
//test countSymbols count multiple symbol
TEST(countSymbols, multiple_symbol){
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  EXPECT_EQ(fa.countSymbols(), 3UL);
}
/*
  test addState()
*/
//test addState add one state
TEST(addState, add_one_state){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.hasState(1));
}
//test addState add multiple state
TEST(addState, add_multiple_state){
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
  EXPECT_TRUE(fa.addState(2));
  EXPECT_TRUE(fa.addState(3));
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_TRUE(fa.hasState(3));
}
//test addState add same state
TEST(addState, add_same_state){
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_FALSE(fa.addState(1));
}
/*
  test removeState()
*/
//test removeState remove one state
TEST(removeState, remove_one_state){
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_FALSE(fa.hasState(1));
}
//test removeState remove multiple state
TEST(removeState, remove_two_state){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_TRUE(fa.removeState(2));
  EXPECT_TRUE(fa.removeState(3));
  EXPECT_FALSE(fa.hasState(1));
  EXPECT_FALSE(fa.hasState(2));
  EXPECT_FALSE(fa.hasState(3));
}
//test removeState remove same state
TEST(removeState, remove_same_state){
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_FALSE(fa.removeState(1));
}
//test removeState remove inexistent state
TEST(removeState, remove_inexistent_state){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeState(1));
}

/*
  test hasState()
*/
//test hasState has one state
TEST(hasState, has_one_state){
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_TRUE(fa.hasState(1));
}

/*
  test countStates()
*/
//test countStates count empty states
TEST(countStates, empty_states){
  fa::Automaton fa;
  EXPECT_EQ(fa.countStates(), 0UL);
}
//test countStates count one state
TEST(countStates, one_state){
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_EQ(fa.countStates(), 1UL);
}
//test countStates count multiple state
TEST(countStates, multiple_state){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  EXPECT_EQ(fa.countStates(), 3UL);
}
/*
  test setStateInitial() and isStateInitial()
*/
//test setStateInitial set one state initial
TEST(setStateInitial, set_one_state_initial){
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_FALSE(fa.isStateInitial(1));
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
}
//test setStateInitial set multiple state initial
TEST(setStateInitial, set_multiple_state_initial){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  EXPECT_FALSE(fa.isStateInitial(1));
  EXPECT_FALSE(fa.isStateInitial(2));
  EXPECT_FALSE(fa.isStateInitial(3));
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateInitial(3);
  EXPECT_TRUE(fa.isStateInitial(1));
  EXPECT_TRUE(fa.isStateInitial(2));
  EXPECT_TRUE(fa.isStateInitial(3));
}
//test setStateInitial set state already initial
TEST(setStateInitial, set_same_state_initial){
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(1);
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
}
//test setStateInitial set inexistent state initial
TEST(setStateInitial, set_inexistent_state_initial){
  fa::Automaton fa;
  fa.setStateInitial(1);
}
/*
  test setSateFinal() and isStateFinal()
*/
//test setStateFinal set one state final
TEST(setStateFinal, set_one_state_final){
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_FALSE(fa.isStateFinal(1));
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
}
//test setStateFinal set multiple state final
TEST(setStateFinal, set_multiple_state_final){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  EXPECT_FALSE(fa.isStateFinal(1));
  EXPECT_FALSE(fa.isStateFinal(2));
  EXPECT_FALSE(fa.isStateFinal(3));
  fa.setStateFinal(1);
  fa.setStateFinal(2);
  fa.setStateFinal(3);
  EXPECT_TRUE(fa.isStateFinal(1));
  EXPECT_TRUE(fa.isStateFinal(2));
  EXPECT_TRUE(fa.isStateFinal(3));
}
//test setStateFinal set state already final
TEST(setStateFinal, set_same_state_final){
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateFinal(1);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
}
//test setStateFinal set inexistent state final
TEST(setStateFinal, set_inexistent_state_final){
  fa::Automaton fa;
  fa.setStateFinal(1);
}
/*
  test addTransition() and hasTransition()
*/
//test addTransition add one transition
TEST(addTransition, add_one_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(1,'a', 2));
  EXPECT_TRUE(fa.hasTransition(1,'a', 2));
}
//test addTransition add multiple transition
TEST(addTransition, add_multiple_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  EXPECT_TRUE(fa.addTransition(1,'a', 2));
  EXPECT_TRUE(fa.addTransition(2,'b', 3));
  EXPECT_TRUE(fa.addTransition(3,'c', 1));

  EXPECT_TRUE(fa.hasTransition(1,'a', 2));
  EXPECT_TRUE(fa.hasTransition(2,'b', 3));
  EXPECT_TRUE(fa.hasTransition(3,'c', 1));
}
//test addTransition add transition with dest inexistent state
TEST(addTransition, add_transition_with_dest_inexistent_state){
  fa::Automaton fa;
  fa.addState(1);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.addTransition(1,'a', 2));
}
//test addTransition add transition with source inexistent state
TEST(addTransition, add_transition_with_source_inexistent_state){
  fa::Automaton fa;
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.addTransition(1,'a', 2));
}
//test addTransition add transition with inexistent symbol
TEST(addTransition, add_transition_with_inexistent_symbol){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  EXPECT_FALSE(fa.addTransition(1,'a', 2));
}
//test addTransition add transition with same source, symbol and dest
TEST(addTransition, add_transition_with_same_source_symbol_dest){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(1,'a', 2));
  EXPECT_FALSE(fa.addTransition(1,'a', 2));
}
//test addTransition add transition with same source and dest
TEST(addTransition, add_transition_with_same_source_dest){
  fa::Automaton fa;
  fa.addState(1);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(1,'a', 1));
}

/*
  test removeTransition()
*/
//test removeTransition remove one transition
TEST(removeTransition, remove_one_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a', 2);
  EXPECT_TRUE(fa.removeTransition(1,'a', 2));
  EXPECT_FALSE(fa.hasTransition(1,'a', 2));
}
//test removeTransition remove multiple transition
TEST(removeTransition, remove_multiple_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addTransition(1,'a', 2);
  fa.addTransition(2,'b', 3);
  fa.addTransition(3,'c', 1);

  EXPECT_TRUE(fa.removeTransition(1,'a', 2));
  EXPECT_TRUE(fa.removeTransition(2,'b', 3));
  EXPECT_TRUE(fa.removeTransition(3,'c', 1));

  EXPECT_FALSE(fa.hasTransition(1,'a', 2));
  EXPECT_FALSE(fa.hasTransition(2,'b', 3));
  EXPECT_FALSE(fa.hasTransition(3,'c', 1));
}
//test removeTransition remove inexistent transition
TEST(removeTransition, remove_inexistent_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.removeTransition(1,'a', 2));
}
//test removeTransition remove transition with inexistent value
TEST(removeTransition, remove_transition_with_inexistent_value){
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeTransition(1,'a', 2));
}
/*
  test hasTransition()
*/
//test hasTransitions has one transition
TEST(hasTransitions, has_one_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a', 2);
  EXPECT_TRUE(fa.hasTransition(1,'a',2));
}
//test hasTransitions has multiple transition
TEST(hasTransitions, has_multiple_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addTransition(1,'a', 2);
  fa.addTransition(2,'b', 3);
  fa.addTransition(3,'c', 1);

  EXPECT_TRUE(fa.hasTransition(1,'a',2));
  EXPECT_TRUE(fa.hasTransition(2,'b',3));
  EXPECT_TRUE(fa.hasTransition(3,'c',1));
}
//test hasTransitions has inexistent transition
TEST(hasTransitions, has_inexistent_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.hasTransition(1,'a',2));
}
//test hasTransitions has transition with inexistent value
TEST(hasTransitions, has_transition_with_inexistent_value){
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasTransition(1,'a',2));
}

/*
test countTransition
*/
//test countTransition no transitions
TEST(countTransition, no_transitions){
  fa::Automaton fa;
  EXPECT_EQ(fa.countTransitions(), 0ul);
}
//test countTransition one transition
TEST(countTransition, one_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a', 2);
  EXPECT_EQ(fa.countTransitions(), 1ul);
}
//test countTransition multiple transitions
TEST(countTransition, multiple_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a', 2);
  fa.addTransition(2,'a', 2);
  fa.addTransition(2,'a', 1);
  EXPECT_EQ(fa.countTransitions(), 3ul);
}
/*
test hasEpsilonTransition()
*/
//test hasEpsilonTransition no epsilon transition
TEST(hasEpsilonTransition, no_epsilon_transition){
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasEpsilonTransition());
}
//test hasEpsilonTransition one epsilon transition
TEST(hasEpsilonTransition, one_epsilon_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addTransition(1, fa::Epsilon, 2);
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

//test hasEpsilonTransition multiple epsilon transition
TEST(hasEpsilonTransition, multiple_epsilon_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addTransition(1, fa::Epsilon, 2);
  fa.addTransition(2, fa::Epsilon, 3);
  fa.addTransition(3, fa::Epsilon, 1);
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

/*
test isDeterministic()
*/
//test isDeterministic no initial state
TEST(isDeterministic, no_initial_state){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a', 2);
  EXPECT_FALSE(fa.isDeterministic());
}
//test isDeterministic no final state
TEST(isDeterministic, no_final_state){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a', 2);
  fa.setStateInitial(1);
  EXPECT_FALSE(fa.isDeterministic());
}
//test isDeterministic no transition
TEST(isDeterministic, no_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isDeterministic());
}
//test isDeterministic with deterministic transition
TEST(isDeterministic, one_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a', 2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isDeterministic());
}
//test isDeterministic with nondeterministic transition
TEST(isDeterministic, multiple_transition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a', 2);
  fa.addTransition(1,'a', 1);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_FALSE(fa.isDeterministic());
}
/*
test isComplete()
*/
//test isComplete incomplete automaton
TEST(isComplete, incomplete_automaton){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a', 2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_FALSE(fa.isComplete());
}
//test isComplete complete automaton
TEST(isComplete, complete_automaton){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1,'a', 2);
  fa.addTransition(1,'b', 2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.isComplete());
}
/*
test removeNonAccessibleStates()
*/
//test removeNonAccessibleStates non accessible state present
TEST(removeNonAccessibleStates, non_accessible_state_present){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addSymbol('a');
  fa.addTransition(1,'a', 2);
  fa.addTransition(3,'a', 2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(), 2ul);
}
//test removeNonAccessibleStates 0 non accessible state
TEST(removeNonAccessibleStates, non_accessible_state){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a', 2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.removeNonAccessibleStates();
  EXPECT_EQ(fa.countStates(), 2ul);
}
/*
test removeNonCoAccessibleStates()
*/
//test removeNonCoAccessibleStates non co accessible state present
TEST(removeNonCoAccessibleStates, non_co_accessible_state_present){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addSymbol('a');
  fa.addTransition(1,'a', 2);
  fa.addTransition(1,'a', 3);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countStates(), 2ul);
}
//test removeNonCoAccessibleStates 0 non co accessible state
TEST(removeNonCoAccessibleStates, non_co_accessible_state){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1,'a', 2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(fa.countStates(), 2ul);
}
/*
test removeEpsilonTransitions()
*/





int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
