import os
import lit.formats

config.name = "ReplaceMulWithShiftTests"
config.test_format = lit.formats.ShTest()
config.suffixes = [".ll"]

config.test_source_root = os.path.dirname(__file__)

config.test_exec_root = os.path.join(config.test_source_root, "Output")

config.substitutions.append(("%opt", os.path.expanduser("~/llvm-project/build/bin/opt")))
config.substitutions.append(("%FileCheck", "FileCheck"))