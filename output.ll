; ModuleID = 'main_module'
source_filename = "main_module"

define i32 @factorial(i32 %n) {
entry:
  %n1 = alloca i32, align 4
  store i32 %n, ptr %n1, align 4
  %n2 = load i32, ptr %n1, align 4
  %cmptmp = icmp sle i32 %n2, 1
  br i1 %cmptmp, label %then, label %else

then:                                             ; preds = %entry
  ret i32 1

else:                                             ; preds = %entry
  %n3 = load i32, ptr %n1, align 4
  %n4 = load i32, ptr %n1, align 4
  %subtmp = sub i32 %n4, 1
  %calltmp = call i32 @factorial(i32 %subtmp)
  %multmp = mul i32 %n3, %calltmp
  ret i32 %multmp

ifcont:                                           ; No predecessors!
  ret i32 0
}

define i32 @add(i32 %a, i32 %b) {
entry:
  %a1 = alloca i32, align 4
  store i32 %a, ptr %a1, align 4
  %b2 = alloca i32, align 4
  store i32 %b, ptr %b2, align 4
  %a3 = load i32, ptr %a1, align 4
  %b4 = load i32, ptr %b2, align 4
  %addtmp = add i32 %a3, %b4
  ret i32 %addtmp
}

define i32 @main() {
entry:
  %num = alloca i32, align 4
  store i32 5, ptr %num, align 4
  %fact = alloca i32, align 4
  %num1 = load i32, ptr %num, align 4
  %calltmp = call i32 @factorial(i32 %num1)
  store i32 %calltmp, ptr %fact, align 4
  %sum = alloca i32, align 4
  %num2 = load i32, ptr %num, align 4
  %fact3 = load i32, ptr %fact, align 4
  %calltmp4 = call i32 @add(i32 %num2, i32 %fact3)
  store i32 %calltmp4, ptr %sum, align 4
  %sum5 = load i32, ptr %sum, align 4
  %cmptmp = icmp sgt i32 %sum5, 100
  br i1 %cmptmp, label %then, label %else

then:                                             ; preds = %entry
  %sum6 = load i32, ptr %sum, align 4
  ret i32 %sum6

else:                                             ; preds = %entry
  ret i32 0

ifcont:                                           ; No predecessors!
  ret i32 0
}
