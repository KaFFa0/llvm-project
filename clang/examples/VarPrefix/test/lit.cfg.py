import os
import lit.formats

config.name = "VarPrefixTests"
config.test_format = lit.formats.ShTest()
config.suffixes = ['.test']

config.test_source_root = os.path.dirname(__file__)
config.test_exec_root = os.path.dirname(__file__)


# Поменяй на путь к твоему clang -cc1
config.clang_cc1 = "/home/kaffa/llvm-project/build/bin/clang"
# Путь к твоему VarPrefix.so
config.var_prefix_so = "/home/kaffa/llvm-project/build/lib/VarPrefix.so"

# Для использования в RUN строках
config.substitutions.append(('%clang_cc1', config.clang_cc1))
config.substitutions.append(('%var_prefix_so', config.var_prefix_so))