import std;
import counters;

void bounded_counter_example()
{
	std::println("\n--------------------------------");
	std::println("BoundedCounter Example");

	BoundedCounter counter(5);
	std::println("Type: {}", counter.get_type());
	std::println("Initial value: {}", counter.get_value());

	std::println("\nIncrementing:");
	for (int i = 0; i < 7; ++i)
	{
		counter.increment();
		std::println("  Step {}: value = {}, limit reached = {}", i + 1, counter.get_value(), counter.is_limit_reached());
	}

	std::println("\nResetting:");
	counter.reset();
	std::println("  After reset: value = {}", counter.get_value());
	std::println("--------------------------------\n");
}

void cyclic_counter_example()
{
	std::println("\n--------------------------------");
	std::println("CyclicCounter Example");

	CyclicCounter counter(4);
	std::println("Type: {}", counter.get_type());
	std::println("Initial value: {}", counter.get_value());

	std::println("\nIncrementing (cyclic behavior):");
	for (int i = 0; i < 7; ++i)
	{
		counter.increment();
		std::println("  Step {}: value = {}, limit reached = {}", i + 1, counter.get_value(), counter.is_limit_reached());
	}

	std::println("\nResetting:");
	counter.reset();
	std::println("  After reset: value = {}", counter.get_value());
	std::println("--------------------------------\n");
}

void step_counter_example()
{
	std::println("\n--------------------------------");
	std::println("StepCounter Example");

	StepCounter counter(9, 3);
	std::println("Type: {}", counter.get_type());
	std::println("Initial value: {}", counter.get_value());

	std::println("\nIncrementing by step:");
	for (int i = 0; i < 5; ++i)
	{
		counter.increment();
		std::println("  Step {}: value = {}, limit reached = {}", i + 1, counter.get_value(), counter.is_limit_reached());
	}

	std::println("\nResetting:");
	counter.reset();
	std::println("  After reset: value = {}", counter.get_value());
	std::println("--------------------------------\n");
}

int main()
{
	bounded_counter_example();
	cyclic_counter_example();
	step_counter_example();

	return 0;
}