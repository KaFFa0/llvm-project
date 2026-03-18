//test2.cpp - Replace mul by shift
//
// Replace integer mul by shift when multiplier is a power of two.

#include "llvm/Transforms/Utils/test2.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/PatternMatch.h"
#include "llvm/ADT/APInt.h"

using namespace llvm;
using namespace llvm::PatternMatch;

PreservedAnalyses ReplaceMulWithShiftPass::run(Function &F, FunctionAnalysisManager &AM) {
  bool Changed = false;

  for (BasicBlock &BB : F) {
    for (auto It = BB.begin(), End = BB.end(); It != End; ) {
      Instruction *I = &*It++;
      if (auto *BO = dyn_cast<BinaryOperator>(I)) {
        if (BO->getOpcode() != Instruction::Mul)
          continue;

        Value *L = BO->getOperand(0);
        Value *R = BO->getOperand(1);

        if (!L->getType()->isIntegerTy() || !R->getType()->isIntegerTy())
          continue;

        ConstantInt *C = nullptr;
        Value *Other = nullptr;

        if ((C = dyn_cast<ConstantInt>(R)))
          Other = L;
        else if ((C = dyn_cast<ConstantInt>(L)))
          Other = R;
        else
          continue;

        const APInt &V = C->getValue();
        if (V.isZero())
          continue;
        if (!V.isPowerOf2())
          continue;

        unsigned ShiftAmt = V.exactLogBase2();

        IRBuilder<> B(BO);
        Constant *ShiftCI = ConstantInt::get(Other->getType(), ShiftAmt);
        Value *Sh = B.CreateShl(Other, ShiftCI);

        BO->replaceAllUsesWith(Sh);
        BO->eraseFromParent();
        Changed = true;
      }
    }
  }

  return Changed ? PreservedAnalyses::none() : PreservedAnalyses::all();
}