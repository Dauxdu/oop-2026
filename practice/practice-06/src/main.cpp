import std;
import String;
import Formatter;
import StringBuilder;

int main()
{
	std::println("\n--------------------------------");
	std::println("String Example");

	String s_default;
	String s_str("Hello, RAII!");
	String s_copy(s_str);

	std::println("  Default → size: {}, str: '{}'", s_default.size(), s_default.str());
	std::println("  String  → size: {}, str: '{}'", s_str.size(), s_str.str());
	std::println("  Copy    → size: {}, value: {}", s_copy.size(), s_copy);

	std::println("Оператор []");

	std::println("  Original string → '{}'", s_str);
	s_str[1] = 'a';
	std::println("  Modified [1]    → '{}'", s_str);

	std::println("\n--------------------------------");
	std::println("StringBuilder Example");

	StringBuilder builder;
	builder.reserve(64);

	builder.append("Result: ");
	builder.append(42);
	builder.append(" + ");
	builder.append(3.14f);

	std::println("  Capacity → {}", builder.capacity());
	std::println("  Size     → {}", builder.size());
	std::println("  Buffer   → '{}'", builder.str());
}