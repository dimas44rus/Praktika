#include "tester.h"

void fillDemoIntStack(elem<int>*& stack) {
    for (int i = 0; i < 10; i++) { // цикл как на слайде 11
        push(stack, i);
    }
}

void fillDemoStudentStack(elem<Student>*& stack) {
    push(stack, Student{ "Алексей", 5 });
    push(stack, Student{ "Мария", 4 });
    push(stack, Student{ "Дмитрий", 5 });
}
