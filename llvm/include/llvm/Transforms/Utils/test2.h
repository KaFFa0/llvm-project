//test2.h - Replace mul by shift
//
// Simple pass that replaces integer multiplication by power-of-two constants
// with equivalent left shifts

#ifndef LLVM_TRANSFORMS_UTILS_TEST2_H
#define LLVM_TRANSFORMS_UTILS_TEST2_H

#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"

namespace llvm {

struct ReplaceMulWithShiftPass : public PassInfoMixin<ReplaceMulWithShiftPass> {
  // New PassManager run hook
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // end namespace llvm

#endif // LLVM_TRANSFORMS_UTILS_TEST2_H