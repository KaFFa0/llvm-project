; RUN: %opt -passes=replace-mul-with-shift -S %s -o test1.out
; RUN: %FileCheck %s --input-file=test1.out

; CHECK-LABEL: @mul_pow2
; CHECK: shl i32 %x, 3

define i32 @mul_pow2(i32 %x) {
entry:
  %1 = mul i32 %x, 8
  ret i32 %1
}