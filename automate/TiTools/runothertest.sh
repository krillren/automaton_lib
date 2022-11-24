#!/usr/bin/env bash

# compilation de gtest et d'Automaton.cc
make preparemasstest

reussi=0
alltest=0

for i in ./test/*.* ; do

   alltest=$((alltest + 1))

   if [ "$i" = "./test/*.*" ];then
      echo "Aucun test dans le dossier test"
      exit 1
   fi

   var=$(cut -d / -f3 <<< "$i") 
   name=$(cut -d . -f1 <<< "$var")
   type=$(cut -d . -f2 <<< "$var")

   printf "\n\n"
   echo "Run test : '$var'"
   echo '##########################################################'
   if [ "$type" = "o" ];then
      g++ -std=c++17 -o "./build/$name.out" "$i" ./build/Automaton_for_test.o ./build/gtest_for_test.o 
   elif [ "$type" = "cc" ];then
      g++ -std=c++17 -c -o "./build/$name.o" "$i" -I../googletest/googletest/include -I../googletest/googletest -I.. -lpthread
      g++ -std=c++17 -o "./build/$name.out" "./build/$name.o" ./build/Automaton_for_test.o ./build/gtest_for_test.o 
   fi

   "./build/$name.out"

   if [ "$?" = "0" ];then
      echo "Test '$var' : OK"
      reussi=$((reussi+1))
   else
      echo "Test '$var' : KO"
   fi
   
done


echo "$reussi tests reussis sur $alltest tests"