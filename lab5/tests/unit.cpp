#include <gtest/gtest.h>
#include "../include/Queue.hpp"
#include "../include/MapDynamicMemoryResource.hpp"

// Глобальные переменные для отслеживания вызовов new/delete
size_t allocation_count = 0;
size_t deallocation_count = 0;

// Переопределение операторов new и delete
void* operator new(size_t size) {
    ++allocation_count;
    return std::malloc(size);
}

void operator delete(void* ptr) noexcept {
    ++deallocation_count;
    std::free(ptr);
}

TEST(QueueTest, DefaultConstructor) {
    Queue<int> Queue;
    EXPECT_TRUE(Queue.Empty());
    EXPECT_EQ(Queue.Size(), 0);
}

TEST(QueueTest, PushAndTop) {
    Queue<int> Queue;
    Queue.Push(1);
    Queue.Push(2);
    Queue.Push(3);
    EXPECT_EQ(Queue.Top(), 3);
    EXPECT_EQ(Queue.Size(), 3);
}

TEST(QueueTest, Pop) {
    Queue<int> Queue;
    Queue.Push(1);
    Queue.Push(2);
    Queue.Push(3);
    
    Queue.Pop();
    EXPECT_EQ(Queue.Top(), 2);
    EXPECT_EQ(Queue.Size(), 2);

    Queue.Pop();
    EXPECT_EQ(Queue.Top(), 1);
    EXPECT_EQ(Queue.Size(), 1);

    Queue.Pop();
    EXPECT_TRUE(Queue.Empty());
}

TEST(QueueTest, Iterator) {
    Queue<int> Queue;
    Queue.Push(1);
    Queue.Push(2);
    Queue.Push(3);

    auto it = Queue.Begin();
    EXPECT_EQ(*it, 3);
    ++it;
    EXPECT_EQ(*it, 2);
    ++it;
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(it, Queue.End());
}

TEST(QueueTest, CopyConstructor) {
    Queue<int> Queue;
    Queue.Push(1);
    Queue.Push(2);
    Queue.Push(3);

    Queue<int> copied_Queue(Queue);
    EXPECT_EQ(copied_Queue.Size(), 3);
    EXPECT_EQ(copied_Queue.Top(), 3);

    copied_Queue.Pop();
    EXPECT_EQ(copied_Queue.Top(), 2);
    EXPECT_EQ(copied_Queue.Size(), 2);
}

TEST(QueueTest, MoveConstructor) {
    Queue<int> Queue;
    Queue.Push(1);
    Queue.Push(2);
    Queue.Push(3);

    Queue<int> moved_Queue(std::move(Queue));
    EXPECT_EQ(moved_Queue.Size(), 3);
    EXPECT_EQ(moved_Queue.Top(), 3);

    EXPECT_TRUE(Queue.Empty());
}

TEST(QueueTest, Emplace) {
    Queue<std::pair<int, int>> Queue;
    Queue.Emplace(1, 2);
    Queue.Emplace(3, 4);

    EXPECT_EQ(Queue.Size(), 2);
    EXPECT_EQ(Queue.Top().first, 3);
    EXPECT_EQ(Queue.Top().second, 4);
}

TEST(QueueTest, IteratorRangeConstructor) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    Queue<int> Queue(vec.begin(), vec.end());

    EXPECT_EQ(Queue.Size(), 5);
    EXPECT_EQ(Queue.Top(), 5);
}

TEST(MapDynamicMemoryResourceTest, AllocationDeallocation) {
    MapDynamicMemoryResource pool;
    std::pmr::polymorphic_allocator<int> allocator(&pool);

    {
        Queue<int, std::pmr::polymorphic_allocator<int>> Queue(allocator);
        Queue.Push(1);
        Queue.Push(2);
    }

    // Все блоки должны быть деаллоцированы
    EXPECT_EQ(pool.get_used_blocks_count(), 0);
    EXPECT_GE(pool.get_free_blocks_count(), 1);
}

TEST(MapDynamicMemoryResourceTest, ReuseFreedMemory) {
    MapDynamicMemoryResource pool;
    std::pmr::polymorphic_allocator<int> allocator(&pool);

    Queue<int, std::pmr::polymorphic_allocator<int>> Queue1(allocator);
    for (int i = 0; i < 20; ++i) {
        Queue1.Push(i);
    }

    EXPECT_EQ(pool.get_used_blocks_count(), 1);
    EXPECT_EQ(pool.get_free_blocks_count(), 1);

    Queue<int, std::pmr::polymorphic_allocator<int>> Queue2(allocator);
    for (int i = 0; i < 10; ++i) {
        Queue2.Push(i);
    }

    EXPECT_EQ(pool.get_used_blocks_count(), 2);
    EXPECT_EQ(pool.get_free_blocks_count(), 0);
}

TEST(MapDynamicMemoryResourceTest, MemoryCleanupOnDestruction) {
    allocation_count = 0;
    deallocation_count = 0;

    {
        MapDynamicMemoryResource memory_resource;
        
        void* ptr1 = memory_resource.allocate(64);
        void* ptr2 = memory_resource.allocate(128);
    }

    // Проверяем, что все выделенные области памяти освобождены
    EXPECT_EQ(allocation_count, deallocation_count);
}

TEST(QueueTest, LargePushAndPop) {
    MapDynamicMemoryResource pool;
    std::pmr::polymorphic_allocator<int> allocator(&pool);
    
    Queue<int, std::pmr::polymorphic_allocator<int>> Queue(allocator);
    const int large_count = 1000;
    
    for (int i = 0; i < large_count; ++i) {
        Queue.Push(i);
    }
    
    EXPECT_EQ(Queue.Size(), large_count);

    for (int i = large_count - 1; i >= 0; --i) {
        EXPECT_EQ(Queue.Top(), i);
        Queue.Pop();
    }
    
    EXPECT_TRUE(Queue.Empty());
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}