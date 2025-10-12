; ModuleID = 'main_module'
source_filename = "main_module"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"

@str_str = private constant [6 x i8] c"Hello\00"

define i32 @main() {
entry:
  %str = alloca [6 x ptr], align 8
  %str1 = alloca [6 x ptr], align 8
  store ptr @str_str, ptr %str1, align 8
  ret i32 0
}
