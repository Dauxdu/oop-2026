import std;
import collections;
import interface;

void stack_test()
{
	std::println("Stack Example");

	Stack<int> stack;
	stack.Push(10);
	stack.Push(1);
	stack.Push(20);

	auto it = stack.GetEnumerator();
	while (it->MoveNext())
	{
		std::println("{}", it->Current());
	}

	std::println("Pop {}", stack.Pop());
	std::println("Peek {}", stack.Peek());
	std::println("Count {}", stack.Count());
	std::println("-------------------------\n");
}

int main()
{
	stack_test();
	return 0;
};