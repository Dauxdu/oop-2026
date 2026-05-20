export module simple_usages:QueueUsages;

import std;
import containers;

export void queue_example()
{
    std::println("\n--------------------------------");
    std::println("Queue Example");

    Queue<int> queue;
    queue.Enqueue(10);
    queue.Enqueue(1);
    queue.Enqueue(20);

    auto enumerator = queue.GetEnumerator();
    std::println("Enumeration:");
    while (enumerator->MoveNext())
    {
        std::println("  Current: {}", enumerator->Current());
    }

    std::println("\nPost-enumeration operations:");
    std::println("  Dequeue() → {}", queue.Dequeue());
    std::println("  Peek()    → {}", queue.Peek());
    std::println("  Count     → {}", queue.Count());

    std::println("--------------------------------\n");
}