; ModuleID = 'main_module'
source_filename = "main_module"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"

define i32 @main() {
entry:
  %x = alloca i32, align 4
  store i32 5, ptr %x, align 4
  %y = alloca i32, align 4
  %x1 = load i32, ptr %x, align 4
  %cmptmp = icmp sgt i32 %x1, 3
  %selecttmp = select i1 %cmptmp, i32 10, i32 20
  store i32 %selecttmp, ptr %y, align 4
  %y2 = load i32, ptr %y, align 4
  ret i32 %y2
}
