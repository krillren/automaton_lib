
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
//git test

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
