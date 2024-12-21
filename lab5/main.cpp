#include <iostream>
#include <string>
#include <memory_resource>
#include "include/Queue.hpp"
#include "include/MapDynamicMemoryResource.hpp"

struct ComplexType {
    int id;
    std::string name;
    double value;

    ComplexType(int id_, const std::string& name_, double value_)
        : id(id_), name(name_), value(value_) {}
};

void DemonstrateQueue() {
    std::cout << "=== Queue with int ===" << std::endl;
    Queue<int> intQueue;
    intQueue.Push(10);
    intQueue.Push(20);
    intQueue.Push(30);

    std::cout << "Queue size: " << intQueue.Size() << std::endl;
    while (!intQueue.Empty()) {
        std::cout << "Top: " << intQueue.Top() << std::endl;
        intQueue.Pop();
    }

    std::cout << "\n=== Queue with ComplexType ===" << std::endl;
    Queue<ComplexType> complexQueue;
    complexQueue.Emplace(1, "First", 100.0);
    complexQueue.Emplace(2, "Second", 200.5);
    complexQueue.Emplace(3, "Third", 300.75);

    std::cout << "Queue size: " << complexQueue.Size() << std::endl;
    while (!complexQueue.Empty()) {
        const ComplexType& top = complexQueue.Top();
        std::cout << "Top: { id: " << top.id 
                  << ", name: " << top.name 
                  << ", value: " << top.value << " }" << std::endl;
        complexQueue.Pop();
    }

    std::cout << "\n=== Queue with custom allocator ===" << std::endl;
    MapDynamicMemoryResource memoryResource;
    std::pmr::polymorphic_allocator<int> allocator(&memoryResource);
    Queue<int, std::pmr::polymorphic_allocator<int>> allocQueue(allocator);

    allocQueue.Push(100);
    allocQueue.Push(200);
    allocQueue.Push(300);

    std::cout << "Queue size (with custom allocator): " << allocQueue.Size() << std::endl;
    while (!allocQueue.Empty()) {
        std::cout << "Top: " << allocQueue.Top() << std::endl;
        allocQueue.Pop();
    }

    std::cout << "Allocator used blocks: " << memoryResource.get_used_blocks_count() << std::endl;
    std::cout << "Allocator free blocks: " << memoryResource.get_free_blocks_count() << std::endl;
}

int main() {
    DemonstrateQueue();
    return 0;
}
