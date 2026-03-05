Запуск:

(из ~/llvm-project/)

./bin/clang++ -std=c++17 ../clang/examples/VarPrefix/test/SampleInput.cpp \
  -Xclang -load -Xclang ./lib/VarPrefix.so \
  -Xclang -plugin -Xclang var-prefix
  
Запуск тестов:
также из корня

lit -v clang/examples/VarPrefix/test/