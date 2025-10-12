; ModuleID = 'main_module'
source_filename = "main_module"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"

define i32 @main() {
entry:
  %a = alloca i32, align 4
  store i32 5, ptr %a, align 4
  %b = alloca i32, align 4
  store i32 10, ptr %b, align 4
  %max = alloca i32, align 4
  %a1 = load i32, ptr %a, align 4
  %b2 = load i32, ptr %b, align 4
  %cmptmp = icmp sgt i32 %a1, %b2
  %a3 = load i32, ptr %a, align 4
  %b4 = load i32, ptr %b, align 4
  %selecttmp = select i1 %cmptmp, i32 %a3, i32 %b4
  store i32 %selecttmp, ptr %max, align 4
  %max5 = load i32, ptr %max, align 4
  %cmptmp6 = icmp ne i32 %max5, 10
  br i1 %cmptmp6, label %then, label %else

then:                                             ; preds = %entry
  ret i32 1

else:                                             ; preds = %entry
  br label %ifcont

ifcont:                                           ; preds = %else
  ret i32 0
}
