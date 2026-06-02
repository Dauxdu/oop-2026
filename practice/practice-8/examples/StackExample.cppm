export module examples:StackExample;

import std;
import containers;

export void stack_example()
{
    std::println("\n--------------------------------");
    std::println("Stack Example");

    Stack<int> stack;

    stack.Push(10);
    stack.Push(1);
    stack.Push(20);

    auto enumerator = stack.GetEnumerator();

    std::println("Enumeration:");
    while (enumerator->MoveNext())
    {
        std::println("  Current: {}", enumerator->Current());
    }

    std::println("\nPost-enumeration operations:");
    std::println("  Pop()  → {}", stack.Pop());
    std::println("  Peek() → {}", stack.Peek());
    std::println("  Count  → {}", stack.Count());
    std::println("--------------------------------\n");
}
