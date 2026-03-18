; RUN: %opt -passes=replace-mul-with-shift -S %s -o test2.out
; RUN: %FileCheck %s --input-file=test2.out

; CHECK-LABEL: @mul_not_pow2
; CHECK: mul i32 %x, 6

define i32 @mul_not_pow2(i32 %x) {
entry:
  %1 = mul i32 %x, 6
  ret i32 %1
}