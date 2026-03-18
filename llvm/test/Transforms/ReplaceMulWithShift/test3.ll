; RUN: %opt -passes=replace-mul-with-shift -S %s -o test3.out
; RUN: %FileCheck %s --input-file=test3.out

; CHECK-LABEL: @mul_const_left
; CHECK: shl i32 %x, 2

define i32 @mul_const_left(i32 %x) {
entry:
  %1 = mul i32 4, %x
  ret i32 %1
}