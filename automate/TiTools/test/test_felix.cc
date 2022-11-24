#include "gtest/gtest.h"

#include "Automaton.h"

/*
 * Example_Test
*/

TEST(AutomatonExampleTest, Default) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isValid());
}

/*
 * addSymbol
*/

TEST(Automaton_addSymbol, validCase) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
}

TEST(Automaton_addSymbol, validCaseBis) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('1'));
}

TEST(Automaton_addSymbol, symbolAlreadyExists) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_FALSE(fa.addSymbol('a'));
}

TEST(Automaton_addSymbol, invalidSymbolEpsilon) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol(fa::Epsilon));
}

TEST(Automaton_addSymbol, invalidSymbolEpsilonBis) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol('\0'));
}

/*
 * removeSymbol
*/

TEST(Automaton_removeSymbol, validCase) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.hasSymbol('a'));
}

TEST(Automaton_removeSymbol, symbolDoesNotExist) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('a'));
}

TEST(Automaton_removeSymbol, invalidSymbol) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol(fa::Epsilon));
  EXPECT_FALSE(fa.removeSymbol('\0'));
}

TEST(Automaton_removeSymbol, trnasitionsUsingtheSymbol) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(0);
  fa.addState(1);
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'b', 0);
  EXPECT_TRUE(fa.removeSymbol('a'));
  EXPECT_FALSE(fa.hasTransition(0, 'a', 1));
  EXPECT_TRUE(fa.hasTransition(1, 'b', 0));
  EXPECT_TRUE(fa.removeSymbol('b'));
  EXPECT_FALSE(fa.hasTransition(1, 'b', 0));
}

/*
 * hasSymbol
*/

TEST(Automaton_hasSymbol, validCase) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_TRUE(fa.hasSymbol('a'));
}

TEST(Automaton_hasSymbol, symbolDoesNotExist) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasSymbol('a'));
}

/*
 * countSymbols
*/

TEST(Automaton_countSymbols, oneSymbol) {
  fa::Automaton fa;
  fa.addSymbol('a');
  EXPECT_EQ((size_t)1, fa.countSymbols());

}

TEST(Automaton_countSymbols, multipleSymbols) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  EXPECT_EQ((size_t)2, fa.countSymbols());
}

TEST(Automaton_countSymbols, noSymbol) {
  fa::Automaton fa;
  EXPECT_EQ((size_t)0, fa.countSymbols());
}

/*
 * addState
*/

TEST(Automaton_addState, validCase) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
}

TEST(Automaton_addState, stateAlreadyExists) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_FALSE(fa.addState(1));
}

TEST(Automaton_addState, negativeState) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addState(-1));
}

/*
 * removeState
*/

TEST(Automaton_removeState, validCase) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_FALSE(fa.hasState(1));
}

TEST(Automaton_removeState, checkTransitions) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1, 'a', 2);
  fa.addTransition(1, 'b', 1);
  fa.addTransition(2, 'b', 1);
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_FALSE(fa.hasState(1));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(1, 'b', 1));
  EXPECT_FALSE(fa.hasTransition(2, 'b', 1));
}

TEST(Automaton_removeState, stateDoesNotExist) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeState(1));
}

/*
 * hasState
*/

TEST(Automaton_hasState, validCase) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_TRUE(fa.hasState(1));
}

TEST(Automaton_hasState, stateDoesNotExist) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasState(1));
}

TEST(Automaton_hasState, negativeState) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasState(-1));
}

/*
 * countStates
*/

TEST(Automaton_countStates, oneState) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_EQ((size_t)1, fa.countStates());
}

TEST(Automaton_countStates, multipleStates) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  EXPECT_EQ((size_t)2, fa.countStates());
}

TEST(Automaton_countStates, noState) {
  fa::Automaton fa;
  EXPECT_EQ((size_t)0, fa.countStates());
}

/*
 * setStateInitial
*/

TEST(Automaton_setStateInitial, validCase) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
}

TEST(Automaton_setStateInitial, stateIsFinal) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateFinal(1);
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
  EXPECT_TRUE(fa.isStateFinal(1));
}

/*
 * isStateInitial
*/

TEST(Automaton_isStateInitial, validCase) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
}


TEST(Automaton_isStateInitial, stateNotInitial) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_FALSE(fa.isStateInitial(1));
}

TEST(Automaton_isStateInitial, stateDoesNotExist) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateInitial(1));
}

/*
 * setStateFinal
*/

TEST(Automaton_setStateFinal, validCase) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
}

TEST(Automaton_setStateFinal, stateDoesNotExist) {
  fa::Automaton fa;
  fa.setStateFinal(1);
  EXPECT_FALSE(fa.isStateFinal(1));
}

TEST(Automaton_setStateFinal, stateIsInitial) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(1);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateInitial(1));
  EXPECT_TRUE(fa.isStateFinal(1));
}

/*
 * isStateFinal
*/

TEST(Automaton_isStateFinal, validCase) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
}

TEST(Automaton_isStateFinal, stateNotFinal) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_FALSE(fa.isStateFinal(1));
}

TEST(Automaton_isStateFinal, stateDoesNotExist) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isStateFinal(1));
}

TEST(Automaton_isStateFinal, plentyStatesOneFinal) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
}

TEST(Automaton_isStateFinal, plentyStatesNoFinal) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  EXPECT_FALSE(fa.isStateFinal(1));
}

/*
 * hasTransition
*/
TEST(Automaton_hasTransition, validCase) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1, 'a', 2);
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(Automaton_hasTransition, stateFromDoesNotExist) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1, 'a', 2);
  EXPECT_FALSE(fa.hasTransition(3, 'a', 2));
}

TEST(Automaton_hasTransition, stateToDoesNotExist) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1, 'a', 2);
  EXPECT_FALSE(fa.hasTransition(1, 'b', 3));
}

TEST(Automaton_hasTransition, symbolDoesNotExist) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1, 'a', 2);
  EXPECT_FALSE(fa.hasTransition(1, 'b', 2));
}

/*
 * addTransition
*/

TEST(Automaton_addTransition, validCase) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(Automaton_addTransition, stateFromDoesNotExist) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.addTransition(3, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(3, 'a', 2));
}

TEST(Automaton_addTransition, stateToDoesNotExist) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.addTransition(1, 'a', 3));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 3));
}

TEST(Automaton_addTransition, symbolDoesNotExist) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.addTransition(1, 'b', 2));
  EXPECT_FALSE(fa.hasTransition(1, 'b', 2));
}

TEST(Automaton_addTransition, transitionAlreadyExists) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_FALSE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(Automaton_addTransition, transitionSameSymbolButDifferentStateTo){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'a', 3));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 3));
}

TEST(Automaton_addTransition, epsilonTransition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.hasTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

TEST(Automaton_addTransition, epsilonTransitionAlreadyExist){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 2));
  EXPECT_FALSE(fa.addTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.hasTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

TEST(Automaton_addTransition, epsilonTransitionSameStateTo){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 3));
  EXPECT_TRUE(fa.hasTransition(1, fa::Epsilon, 2));
  EXPECT_TRUE(fa.hasTransition(1, fa::Epsilon, 3));
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

TEST(Automaton_addTransition, plentyTransitionsInAutomatonAndAddingEpsilon){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  EXPECT_TRUE(fa.addTransition(1, 'a', 2));
  EXPECT_TRUE(fa.addTransition(1, 'b', 3));
  EXPECT_TRUE(fa.addTransition(1, 'c', 2));
  EXPECT_TRUE(fa.addTransition(1, fa::Epsilon, 3));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
  EXPECT_TRUE(fa.hasTransition(1, 'b', 3));
  EXPECT_TRUE(fa.hasTransition(1, 'c', 2));
  EXPECT_TRUE(fa.hasTransition(1, fa::Epsilon, 3));
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

/*
 * removeTransition
*/

TEST(Automaton_removeTransition, validCase) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1, 'a', 2);
  EXPECT_TRUE(fa.removeTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
}

TEST(Automaton_removeTransition, stateFromDoesNotExist) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1, 'a', 2);
  EXPECT_FALSE(fa.removeTransition(3, 'a', 2));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(Automaton_removeTransition, stateToDoesNotExist) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1, 'a', 2);
  EXPECT_FALSE(fa.removeTransition(1, 'a', 3));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(Automaton_removeTransition, symbolDoesNotExist) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1, 'a', 2);
  EXPECT_FALSE(fa.removeTransition(1, 'b', 2));
  EXPECT_TRUE(fa.hasTransition(1, 'a', 2));
}

TEST(Automaton_removeTransition, transitionDoesNotExist) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.removeTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
}

TEST(Automaton_removeTransition, epsilonTransition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1, fa::Epsilon, 2);
  EXPECT_TRUE(fa.removeTransition(1, fa::Epsilon, 2));
  EXPECT_FALSE(fa.hasTransition(1, fa::Epsilon, 2));
  EXPECT_FALSE(fa.hasEpsilonTransition());
}

TEST(Automaton_removeTransition, plentyTransitions){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addTransition(1, 'a', 2);
  fa.addTransition(2, 'b', 1);
  fa.addTransition(1, 'c', 2);
  EXPECT_TRUE(fa.removeTransition(1, 'a', 2));
  EXPECT_TRUE(fa.removeTransition(2, 'b', 1));
  EXPECT_TRUE(fa.removeTransition(1, 'c', 2));
  EXPECT_FALSE(fa.hasTransition(1, 'a', 2));
  EXPECT_FALSE(fa.hasTransition(2, 'b', 1));
  EXPECT_FALSE(fa.hasTransition(1, 'c', 2));
}

/*
 * countTransitions
*/

TEST(Automaton_countTransitions, validCase) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1, 'a', 2);
  EXPECT_EQ(fa.countTransitions(), 1ul);
}

TEST(Automaton_countTransitions, noTransition) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_EQ(fa.countTransitions(), 0ul);
}

TEST(Automaton_countTransitions, epsilonTransition){
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1, fa::Epsilon, 2);
  EXPECT_EQ(fa.countTransitions(), 1ul);
}

/*
 * hasEpsilonTransition
*/

TEST(Automaton_hasEpsilonTransition, validCase) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1, fa::Epsilon, 2);
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

TEST(Automaton_hasEpsilonTransition, noTransition) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.hasEpsilonTransition());
}

TEST(Automaton_hasEpsilonTransition, noEpsilonTransition) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addTransition(1, 'a', 2);
  EXPECT_FALSE(fa.hasEpsilonTransition());
}

/*
 * isDeterministic
*/

TEST(Automaton_isDeterministic, validCase) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.setStateFinal(0);
  fa.setStateInitial(0);
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(Automaton_isDeterministic, oneStatebutNotInitial) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.isDeterministic());
}


TEST(Automaton_isDeterministic, noTransitionButDeterministic){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.isDeterministic());
}

TEST(Automaton_isDeterministic, noTransitionNotDeterministic){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.isDeterministic());
}

TEST(Automaton_isDeterministic, plentyInitialStates){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.setStateInitial(1);
  EXPECT_FALSE(fa.isDeterministic());
}


TEST(Automaton_isDeterministic, plentyTransitions){
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.addState(1);
  fa.addState(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'b', 2);
  fa.addTransition(0, 'b', 0);
  EXPECT_TRUE(fa.isDeterministic());
  fa.addTransition(0, 'a', 2);
  EXPECT_FALSE(fa.isDeterministic());
  fa.removeTransition(0, 'a', 2);
}




/*
 * isComplete
*/

TEST(Automaton_isComplete, validCase) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.setStateFinal(0);
  fa.setStateInitial(0);
  fa.addTransition(0, 'a', 0);
  fa.addTransition(0, 'b', 0);
  EXPECT_TRUE(fa.isComplete());
}

TEST(Automaton_isComplete, oneStateButNoTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.setStateFinal(0);
  fa.setStateInitial(0);
  EXPECT_FALSE(fa.isComplete());
}

TEST(Automaton_isComplete, noTransition) {
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.setStateFinal(0);
  fa.setStateInitial(0);
  EXPECT_FALSE(fa.isComplete());
}

/*
 * createComplete
*/

TEST(Automaton_createComplete, validCase){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'b', 0);
  EXPECT_FALSE(fa.isComplete());
  fa::Automaton fa2 = fa.createComplete(fa);
  EXPECT_TRUE(fa2.isComplete());
  EXPECT_EQ((size_t)2, fa2.countSymbols());
  EXPECT_EQ((size_t)fa.countTransitions()+4, fa2.countTransitions());
  EXPECT_TRUE(fa2.hasTransition(0, 'a', 1));
  EXPECT_TRUE(fa2.hasTransition(1, 'b', 0));
  EXPECT_TRUE(fa2.isValid());
}

TEST(Automaton_createComplete, alreadyComplete){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'b', 0);
  EXPECT_FALSE(fa.isComplete());
  fa::Automaton fa2 = fa.createComplete(fa);
  EXPECT_TRUE(fa2.isComplete());
  EXPECT_EQ((size_t)2, fa2.countSymbols());
  EXPECT_EQ((size_t)fa.countTransitions()+4, fa2.countTransitions());
  EXPECT_TRUE(fa2.hasTransition(0, 'a', 1));
  EXPECT_TRUE(fa2.hasTransition(1, 'b', 0));
  EXPECT_TRUE(fa2.isValid());
  fa::Automaton fa3 = fa.createComplete(fa2);
  EXPECT_TRUE(fa3.isComplete());
  EXPECT_TRUE(fa3.isValid());
}

/*
 * createComplement
*/

TEST(Automaton_createComplement, validCase){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.setStateFinal(0);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 0);
  fa.addTransition(0, 'b', 1);
  fa.addTransition(1, 'a', 0);
  fa::Automaton complFa = fa.createComplement(fa);
  EXPECT_TRUE(complFa.isComplete());
  EXPECT_FALSE(complFa.isStateFinal(0));
  EXPECT_FALSE(complFa.isStateFinal(1));
  EXPECT_TRUE(complFa.isValid());
}


/*
 * createMirror
*/

TEST(Automaton_createMirror, validCase){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateFinal(2);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(1, 'b', 2);
  fa.addTransition(0, 'b', 0);
  fa.addTransition(1, 'a', 1);
  fa.addTransition(2, 'a', 0);
  fa::Automaton mirrorFa = fa.createMirror(fa);
  EXPECT_FALSE(mirrorFa.isStateInitial(0));
  EXPECT_TRUE(mirrorFa.isStateFinal(0));
  EXPECT_FALSE(mirrorFa.isStateFinal(2));
  EXPECT_TRUE(mirrorFa.isStateInitial(2));
  EXPECT_TRUE(mirrorFa.hasTransition(1, 'a', 0));
  EXPECT_FALSE(mirrorFa.hasTransition(0, 'a', 1));
  EXPECT_TRUE(mirrorFa.hasTransition(2, 'b', 1));
  EXPECT_FALSE(mirrorFa.hasTransition(1, 'b', 2));
  EXPECT_TRUE(mirrorFa.hasTransition(0, 'b', 0));
  EXPECT_TRUE(mirrorFa.hasTransition(1, 'a', 1));
  EXPECT_TRUE(mirrorFa.hasTransition(0, 'a', 2));
  EXPECT_FALSE(mirrorFa.hasTransition(2, 'a', 0));
  EXPECT_TRUE(mirrorFa.isValid());
}

TEST(Automaton_createMirror, onlyOneState){
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.setStateFinal(0);
  fa.setStateInitial(0);
  fa::Automaton mirrorFa = fa.createMirror(fa);
  EXPECT_TRUE(mirrorFa.isStateFinal(0));
  EXPECT_TRUE(mirrorFa.isStateInitial(0));
  EXPECT_TRUE(mirrorFa.isValid());
}

/*
 * isLanguageEmpty
*/

TEST(Automaton_isLanguageEmpty, validCase){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateFinal(1);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(0, 'b', 0);
  fa.addTransition(1, 'a', 1);
  EXPECT_FALSE(fa.isLanguageEmpty());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_isLanguageEmpty, onlyOneStateFinalAndInitial){
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateFinal(0);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  EXPECT_FALSE(fa.isLanguageEmpty());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_isLanguageEmpty, onlyOneStateFinalButNotInitial){
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.isLanguageEmpty());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_isLanguageEmpty, onlyOneStateNotFinalButInitial){
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.isLanguageEmpty());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_isLanguageEmpty, onlyOneStateNeitherFinalNorInitial){
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  EXPECT_TRUE(fa.isLanguageEmpty());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_isLanguageEmpty, noFinalStates){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(0, 'b', 0);
  fa.addTransition(1, 'a', 1);
  EXPECT_TRUE(fa.isLanguageEmpty());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_isLanguageEmpty, noPathToFinalState){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(0);
  fa.setStateFinal(2);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(0, 'b', 0);
  fa.addTransition(1, 'a', 1);
  EXPECT_TRUE(fa.isLanguageEmpty());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_isLanguageEmpty, noInitialStates){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.setStateFinal(1);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(0, 'b', 0);
  fa.addTransition(1, 'a', 1);
  EXPECT_TRUE(fa.isLanguageEmpty());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_isLanguageEmpty, plentyInitialStatesValid){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(0, 'b', 0);
  fa.addTransition(1, 'a', 0);
  fa.addTransition(1, 'b', 2);
  fa.addTransition(2, 'a', 3);
  EXPECT_FALSE(fa.isLanguageEmpty());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_isLanguageEmpty, noTransitions){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addSymbol('a');
  fa.addSymbol('b');
  EXPECT_TRUE(fa.isLanguageEmpty());
  EXPECT_TRUE(fa.isValid());
}

/*
 * removeNonAccessibleStates
*/

TEST(Automaton_removeNonAccessibleStates, validCase){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(0);
  fa.setStateFinal(3);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(0, 'b', 0);
  fa.addTransition(1, 'a', 3);
  fa.removeNonAccessibleStates();
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.hasState(3));
  EXPECT_FALSE(fa.hasState(2));
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_removeNonAccessibleStates, noTransitionsOnlyOneStateAndInitial){
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateInitial(0);
  fa.addSymbol('a');
  fa.removeNonAccessibleStates();
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_EQ(1u, fa.countStates());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_removeNonAccessibleStates, noTransitionsOnlyOneStateButNotInitial){
  fa::Automaton fa;
  fa.addState(1);
  fa.addSymbol('a');
  fa.removeNonAccessibleStates();
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.isStateInitial(1));
  EXPECT_EQ(1u, fa.countStates());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_removeNonAccessibleStates, noTransitionsMultipleStates){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.setStateInitial(2);
  fa.setStateInitial(4);
  fa.addSymbol('a');
  fa.removeNonAccessibleStates();
  EXPECT_FALSE(fa.hasState(0));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_TRUE(fa.hasState(4));
  EXPECT_EQ(2u, fa.countStates());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_removeNonAccessibleStates, onlyOneStateAndIsInitial){
  fa::Automaton fa;
  fa.addState(0);
  fa.addSymbol('a');
  fa.setStateInitial(0);
  fa.addTransition(0, 'a', 0);
  fa.removeNonAccessibleStates();
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_removeNonAccessibleStates, onlyOneStateButNotInitial){
  fa::Automaton fa;
  fa.addState(1);
  fa.addSymbol('a');
  fa.addTransition(0, 'a', 0);
  fa.removeNonAccessibleStates();
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_TRUE(fa.isStateInitial(1));
  EXPECT_EQ(1u, fa.countStates());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_removeNonAccessibleStates, multipleStatesButNoInitial){
 fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.setStateFinal(4);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(1, 'a', 2);
  fa.addTransition(1, 'b', 1);
  fa.addTransition(2, 'a', 4);
  fa.removeNonAccessibleStates();
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_FALSE(fa.hasState(1));
  EXPECT_FALSE(fa.hasState(2));
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_FALSE(fa.hasState(4));
  EXPECT_TRUE(fa.isValid());
}

/**
* removeNonCoAccessibleStates
*/

TEST(Automaton_removeNonCoAccessibleStates, validCase){
 fa::Automaton fa;
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateFinal(3);
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addTransition(0, 'a', 1);
  fa.addTransition(0, 'b', 0);
  fa.addTransition(1, 'a', 3);
  fa.removeNonCoAccessibleStates();
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_TRUE(fa.hasState(1));
  EXPECT_FALSE(fa.hasState(2));
  EXPECT_TRUE(fa.hasState(3));
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_removeNonCoAccessibleStates, noTransitionsOnlyOneStateAndFinal){
  fa::Automaton fa;
  fa.addState(0);
  fa.setStateFinal(0);
  fa.addSymbol('a');
  fa.removeNonCoAccessibleStates();
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_EQ(1u, fa.countStates());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_removeNonCoAccessibleStates, noTransitionsOnlyOneStateButNotFinal){
  fa::Automaton fa;
  fa.addState(1);
  fa.addSymbol('a');
  fa.removeNonCoAccessibleStates();
  EXPECT_FALSE(fa.hasState(0));
  EXPECT_EQ(1u, fa.countStates());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_removeNonCoAccessibleStates, noTransitionsMultipleStates){
  fa::Automaton fa;
  fa.addState(0);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.setStateFinal(2);
  fa.setStateFinal(4);
  fa.addSymbol('a');
  fa.removeNonCoAccessibleStates();
  EXPECT_FALSE(fa.hasState(0));
  EXPECT_TRUE(fa.hasState(2));
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_TRUE(fa.hasState(4));
  EXPECT_EQ(2u, fa.countStates());
  EXPECT_TRUE(fa.isValid());
}

TEST(Automaton_removeNonCoAccessibleStates, noTransitionsMultipleStatesButNoFinals){
    fa::Automaton fa;
  fa.addState(0);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addSymbol('a');
  fa.removeNonCoAccessibleStates();
  EXPECT_TRUE(fa.hasState(0));
  EXPECT_EQ(1u, fa.countStates());
  EXPECT_TRUE(fa.isValid());
}





/**
* createProduct
*/

TEST(Automaton_createProduct, validCase){
  fa::Automaton fa1;
  fa1.addState(1);
  fa1.addState(2);
  fa1.addState(3);
  fa1.setStateInitial(1);
  fa1.setStateInitial(3);
  fa1.setStateFinal(2);
  fa1.addSymbol('a');
  fa1.addSymbol('b');
  fa1.addTransition(1, 'a', 2);
  fa1.addTransition(2, 'a', 3);
  fa1.addTransition(3, 'b', 2);
  fa1.addTransition(3, 'b', 3);

  fa::Automaton fa2;
  fa2.addState(4);
  fa2.addState(5);
  fa2.setStateInitial(4);
  fa2.setStateFinal(5);
  fa2.addSymbol('a');
  fa2.addSymbol('b');
  fa2.addTransition(4, 'a', 4);
  fa2.addTransition(4, 'b', 5);
  fa2.addTransition(5, 'a', 4);

  fa::Automaton fa3 = fa::Automaton::createProduct(fa1, fa2);





  // std::ostream& os = std::cout;
  // fa3.prettyPrint(os);

  EXPECT_TRUE(fa3.isValid());

}





int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  // fa::Automaton fa;
  // std::ostream& os = std::cout;
  // fa.addState(0);
  // fa.addState(1);
  // fa.setStateFinal(1);
  // fa.setStateInitial(0);
  // fa.addSymbol('a');
  // fa.addTransition(0, 'a', 1);
  // fa.prettyPrint(os);
  return RUN_ALL_TESTS();
}
