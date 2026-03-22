#include <gtest/gtest.h>

#include <data_struct/circular_queue_1.hpp>

#include <algorithm>
#include <chrono>
#include <numeric>
#include <print>
#include <random>
#include <ranges>
#include <thread>
#include <unordered_set>

static constexpr auto k_debugQueueEatenItem = 555555555;

template <typename TItem, std::size_t TVSize>
using QueueType = Ds::CircularQueueMpMcLf<TItem, TVSize, k_debugQueueEatenItem>;

namespace
{
    template <typename TItem, std::size_t TVSize>
    std::vector<TItem> consumeToVector(QueueType<TItem, TVSize>& queue)
    {
        std::vector<TItem> v;
        v.reserve(TVSize);
        for (auto item = queue.take(); item.has_value(); item = queue.take())
        {
            v.push_back(*item);
        }
        return v;
    }

    template <typename T>
    std::vector<T> toUnique(const std::vector<T>& v)
    {
        auto s = std::ranges::to<std::unordered_set<T>>(v);
        auto vv = std::ranges::to<std::vector<T>>(s);
        return vv;
    }

    // a - b
    template <typename T>
    std::vector<T> subtract(const std::vector<T>& a, const std::vector<T>& b)
    {
        std::vector<T> aMinusB;
        for (auto itemA : a)
        {
            if (!std::ranges::contains(b, itemA))
            {
                aMinusB.push_back(itemA);
            }
        }
        return aMinusB;
        // std::ranges::all_of(b, [](const auto bi) { return std::ranges::contains(a, bi); });
    }

    int indexOfMissingValue(const std::vector<int>& sortedItems)
    {
        if (sortedItems.empty())
        {
            return -1;
        }
        for (auto i = 0u; i < sortedItems.size() - 1; ++i)
        {
            if (sortedItems[i + 1] == k_debugQueueEatenItem)
            {
                continue;
            }
            if (sortedItems[i + 1] - sortedItems[i] > 1)
            {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    std::vector<int> getMissingValues(const std::vector<int>& sortedItems)
    {
        std::vector<int> missing;
        if (sortedItems.empty())
        {
            return missing;
        }
        for (auto i = 0u; i < sortedItems.size() - 1; ++i)
        {
            if (sortedItems[i + 1] == k_debugQueueEatenItem)
            {
                continue;
            }
            const auto missingCount = sortedItems[i + 1] - sortedItems[i] - 1;
            for (auto j = 0; j < missingCount; ++j)
            {
                missing.push_back(sortedItems[i] + j + 1);
            }
        }
        return missing;
    }

    int indexOfDuplicateValue(const std::vector<int>& sortedItems)
    {
        if (sortedItems.empty())
        {
            return -1;
        }
        for (auto i = 0u; i < sortedItems.size() - 1; ++i)
        {
            if (sortedItems[i + 1] == sortedItems[i])
            {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

    std::vector<int> getDuplicateValues(const std::vector<int>& sortedItems)
    {
        std::vector<int> dups;
        if (sortedItems.empty())
        {
            return dups;
        }
        for (auto i = 0u; i < sortedItems.size() - 1; ++i)
        {
            if (sortedItems[i + 1] == sortedItems[i])
            {
                dups.push_back(sortedItems[i]);
            }
        }
        return dups;
    }

    template <std::ranges::forward_range R>
    std::string toString(const R& a)
    {
        std::ostringstream oss;
        for (const auto& item : a)
        {
            oss << ' ' << std::to_string(item);
        }
        return oss.str();
    }
} // namespace

TEST(CircularQueue_1, BasicAssertions)
{
    QueueType<int, 4> queue;

    // TEST: Empty state.
    EXPECT_EQ(queue.isEmpty(), true);
    EXPECT_EQ(queue.count(), 0);

    // TEST: Adding items.
    queue.add(1);
    EXPECT_EQ(queue.isEmpty(), false);
    EXPECT_EQ(queue.count(), 1);

    queue.add(2);
    EXPECT_EQ(queue.isEmpty(), false);
    EXPECT_EQ(queue.count(), 2);

    // TEST: Taking items.
    auto item = queue.take();
    EXPECT_EQ(queue.isEmpty(), false);
    EXPECT_EQ(queue.count(), 1);
    EXPECT_EQ(item, 1);

    item = queue.take();
    EXPECT_EQ(queue.isEmpty(), true);
    EXPECT_EQ(queue.count(), 0);
    EXPECT_EQ(item, 2);
}

TEST(CircularQueue_1, FullAndEmptyQueue)
{
    QueueType<int, 4> queue;

    // TEST: Empty state.
    EXPECT_EQ(queue.isEmpty(), true);
    EXPECT_EQ(queue.isFull(), false);
    EXPECT_EQ(queue.count(), 0);

    // TEST: Taking from empty queue.
    auto item = queue.take();
    EXPECT_EQ(item.has_value(), false);

    // TEST: Full state.
    queue.add(1);
    queue.add(2);
    queue.add(3);
    queue.add(4);
    EXPECT_EQ(queue.isEmpty(), false);
    EXPECT_EQ(queue.isFull(), true);
    EXPECT_EQ(queue.count(), 4);

    // TEST: Adding to full queue.
    auto wasAdded = queue.add(5);
    EXPECT_EQ(wasAdded, false);
    EXPECT_EQ(queue.isEmpty(), false);
    EXPECT_EQ(queue.isFull(), true);
    EXPECT_EQ(queue.count(), 4);

    // TEST: Taking all items.
    item = queue.take();
    EXPECT_EQ(item, 1);
    item = queue.take();
    EXPECT_EQ(item, 2);
    item = queue.take();
    EXPECT_EQ(item, 3);
    item = queue.take();
    EXPECT_EQ(item, 4);

    // TEST: Taking from empty queue.
    item = queue.take();
    EXPECT_EQ(item.has_value(), false);
}

TEST(CircularQueue_1, Concurrency_1_Producer_1_Consumer)
{
    constexpr auto itemCount = 1000;
    constexpr auto workItemCount = 4;

    QueueType<int, itemCount> inputQueue;
    QueueType<int, workItemCount> workQueue;
    QueueType<int, itemCount> outputQueue;

    for (int i = 0; i < itemCount; ++i)
    {
        inputQueue.add(i);
    }

    // TEST: Multiple producers, multiple consumers.
    // Create and run producer and consumer threads.
    // Producers take items from the input queue and put them to the work queue.
    // Consumers take items from the work queue and put them to the output queue.

    std::atomic_bool shouldConsumersStop = false;
    constexpr auto threadCount = 10;

    std::thread producer{[&]()
            {
                std::random_device randDev;
                std::mt19937 randEngine{randDev()};
                std::uniform_int_distribution randDist{1, 10};
                for (auto item = inputQueue.take(); item.has_value(); item = inputQueue.take())
                {
                    while (!workQueue.add(*item))
                    {
                    }
                    // std::this_thread::sleep_for(std::chrono::milliseconds{randDist(randEngine)});
                }
            }};

    std::thread consumer{[&]()
            {
                std::random_device randDev;
                std::mt19937 randEngine{randDev()};
                std::uniform_int_distribution randDist{1, 10};
                while (true)
                {
                    auto item = workQueue.take();
                    if (item.has_value())
                    {
                        outputQueue.add(*item);
                    }
                    else if (shouldConsumersStop)
                    {
                        break;
                    }
                    // std::this_thread::sleep_for(std::chrono::milliseconds{randDist(randEngine)});
                }
            }};

    producer.join();
    shouldConsumersStop = true;
    consumer.join();

    // TEST: Input state after threads have finished.
    EXPECT_EQ(inputQueue.count(), 0);
    EXPECT_EQ(inputQueue.isEmpty(), true);

    // TEST: Output state after threads have finished.
    EXPECT_EQ(outputQueue.count(), itemCount);
    EXPECT_EQ(outputQueue.isFull(), true);

    // TEST: Output items are the same as input items.
    // The input items are/were an ordered sequence of numbers in [0, N].
    std::vector<int> outputItems;
    for (int i = 0; i < itemCount; ++i)
    {
        const auto item = outputQueue.take();
        outputItems.push_back(i);
    }
    std::sort(outputItems.begin(), outputItems.end());
    for (int i = 0; i < itemCount; ++i)
    {
        EXPECT_EQ(outputItems[i], i);
    }
}

TEST(CircularQueue_1, Concurrency_N_Consumer)
{
    constexpr auto consumerThreadCount = 10;
    constexpr auto consumerItemCount = 3000;
    constexpr auto itemCount = consumerThreadCount * consumerItemCount;

    auto inputQueuePtr = std::make_unique<QueueType<int, itemCount>>();
    auto& inputQueue = *inputQueuePtr;

    for (int i = 0; i < itemCount; ++i)
    {
        inputQueue.add(i);
    }

    // TEST: Multiple producers, multiple consumers.
    // Create and run producer and consumer threads.
    // Producers take items from the input queue and put them to the work queue.
    // Consumers take items from the work queue and put them to the output queue.

    std::vector<std::vector<int>> outputItems(consumerThreadCount);

    auto consumerFunc = [&](int threadIndex)
    {
        std::random_device randDev;
        std::mt19937 randEngine{randDev()};
        std::uniform_int_distribution randDist{1, 100};
        for (auto item = inputQueue.take(); item.has_value(); item = inputQueue.take())
        {
            outputItems[threadIndex].push_back(*item);
            // std::this_thread::sleep_for(std::chrono::milliseconds{randDist(randEngine)});
        }
    };

    std::vector<std::thread> consumers;
    for (int i = 0; i < consumerThreadCount; ++i)
    {
        consumers.emplace_back(std::thread{consumerFunc, i});
    }
    for (auto& consumer : consumers)
    {
        consumer.join();
    }

    // TEST: Input state after threads have finished.
    EXPECT_EQ(inputQueue.count(), 0);
    EXPECT_EQ(inputQueue.isEmpty(), true);

    // TEST: Output item count equal to input item count.
    auto flattenedOutputItems = std::ranges::to<std::vector<int>>(std::views::join(outputItems));
    EXPECT_EQ(flattenedOutputItems.size(), itemCount);

    // TEST: Consumers got different items (no overlap between consumers).
    auto flattenedOutputItemsSet = std::ranges::to<std::unordered_set<int>>(flattenedOutputItems);
    EXPECT_EQ(flattenedOutputItemsSet.size(), itemCount);

    // TEST: Consumers didn't get duplicate items.
    for (auto i = 0; i < consumerThreadCount; ++i)
    {
        auto outputItemsSet = std::ranges::to<std::unordered_set<int>>(outputItems[i]);
        EXPECT_EQ(outputItemsSet.size(), outputItems[i].size());
    }
}

TEST(CircularQueue_1, Concurrency_N_Producer)
{
    constexpr auto producerThreadCount = 3;
    constexpr auto producerItemCount = 3000;
    constexpr auto itemCount = producerThreadCount * producerItemCount;

    std::vector<std::vector<int>> inputItems(producerThreadCount);
    for (int i = 0, p = 0; p < producerThreadCount; ++p)
    {
        inputItems[p].resize(producerItemCount);
        for (int pi = 0; pi < producerItemCount; ++pi, ++i)
        {
            inputItems[p][pi] = i;
        }
    }

    auto outputQueuePtr = std::make_unique<QueueType<int, itemCount>>();
    auto& outputQueue = *outputQueuePtr;

    auto producerFunc = [&](int threadIndex)
    {
        std::random_device randDev;
        std::mt19937 randEngine{randDev()};
        std::uniform_int_distribution randDist{1, 100};
        for (auto item : inputItems[threadIndex])
        {
            while (!outputQueue.add(item))
            {
                // Empty.
            }
            // std::this_thread::sleep_for(std::chrono::milliseconds{randDist(randEngine)});
        }
    };

    std::vector<std::thread> producers;
    for (int i = 0; i < producerThreadCount; ++i)
    {
        producers.emplace_back(std::thread{producerFunc, i});
    }
    for (auto& producer : producers)
    {
        producer.join();
    }

    // TEST: Output state after threads have finished.
    EXPECT_EQ(outputQueue.count(), itemCount);
    EXPECT_EQ(outputQueue.isEmpty(), false);
    EXPECT_EQ(outputQueue.isFull(), true);

    // TEST:
    auto flattenedInputItems = std::ranges::to<std::vector<int>>(std::views::join(inputItems));
    auto outputItems = consumeToVector(outputQueue);
    std::ranges::sort(outputItems);
    for (int i = 0; i < itemCount; ++i)
    {
        EXPECT_EQ(outputItems[i], flattenedInputItems[i]);
    }
}

TEST(CircularQueue_1, Concurrency_N_Producer_M_Consumer)
{
    // TEST: Multiple producers, multiple consumers.
    // Create and run producer and consumer threads.
    // Producer P takes items from inputItems[P] and puts them to the work queue.
    // Consumer C takes items from the work queue and put them to the outputItems[C].

    constexpr auto producerItemCount = 300;
    constexpr auto producerThreadCount = 2;
    constexpr auto consumerThreadCount = 2;
    constexpr auto itemCount = producerThreadCount * producerItemCount;
    constexpr auto workItemCount = 4;

    std::vector<std::vector<int>> inputItems(producerThreadCount);
    for (int i = 0, p = 0; p < producerThreadCount; ++p)
    {
        inputItems[p].resize(producerItemCount);
        for (int pi = 0; pi < producerItemCount; ++pi, ++i)
        {
            inputItems[p][pi] = i;
        }
    }

    std::vector<std::vector<int>> outputItems(consumerThreadCount);

    auto workQueuePtr = std::make_unique<QueueType<int, workItemCount>>();
    auto& workQueue = *workQueuePtr;

    std::atomic_bool shouldConsumersStop = false;

    auto producerFunc = [&](int threadIndex)
    {
        // std::random_device randDev;
        // std::mt19937 randEngine{randDev()};
        // std::uniform_int_distribution randDist{1, 100};
        for (auto item : inputItems[threadIndex])
        {
            while (!workQueue.add(item))
            {
                // Empty.
            }
            // std::this_thread::sleep_for(std::chrono::milliseconds{randDist(randEngine)});
        }
    };

    auto consumerFunc = [&](int threadIndex)
    {
        // std::random_device randDev;
        // std::mt19937 randEngine{randDev()};
        // std::uniform_int_distribution randDist{1, 100};
        while (true)
        {
            const auto item = workQueue.take();
            if (item.has_value())
            {
                // if (*item == 555555555)
                //     outputItems[threadIndex].push_back(*item + 1);
                // else
                //     outputItems[threadIndex].push_back(*item);
                outputItems[threadIndex].push_back(*item);
            }
            else if (shouldConsumersStop && workQueue.isEmpty())
            {
                break;
            }
            // std::this_thread::sleep_for(std::chrono::milliseconds{randDist(randEngine)});
        }
    };

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for (int i = 0; i < consumerThreadCount; ++i)
    {
        consumers.emplace_back(std::thread{consumerFunc, i});
    }

    for (int i = 0; i < producerThreadCount; ++i)
    {
        producers.emplace_back(std::thread{producerFunc, i});
    }

    for (auto& producer : producers)
    {
        producer.join();
    }

    shouldConsumersStop = true;

    for (auto& consumer : consumers)
    {
        consumer.join();
    }

    // TEST: Work queue state after threads have finished.
    EXPECT_EQ(workQueue.count(), 0);
    EXPECT_EQ(workQueue.isEmpty(), true);

    auto inputItemsFlat = std::ranges::to<std::vector<int>>(std::views::join(inputItems));
    auto outputItemsFlat = std::ranges::to<std::vector<int>>(std::views::join(outputItems));
    auto outputItemsFlatSorted = outputItemsFlat;
    std::ranges::sort(outputItemsFlatSorted);
    auto outputItemsFlatSortedUnique = toUnique(outputItemsFlatSorted);

    auto isFailed = false;

    // TEST: Item counts match.
    if (inputItemsFlat.size() != outputItemsFlatSorted.size())
    {
        isFailed = true;
        std::println(
                "ERROR: Item count mismatch. In {} != out {}", inputItemsFlat.size(), outputItemsFlatSorted.size());
    }

    // TEST: Consumers got all items.
    if (const auto missingItems = subtract(inputItemsFlat, outputItemsFlatSortedUnique); !missingItems.empty())
    {
        isFailed = true;
        std::println("ERROR: Didn't receive all items. Missing: {}", toString(missingItems));
    }

    // TEST: Consumers didn't receive extra/bogus items.
    if (const auto extraItems = subtract(outputItemsFlatSortedUnique, inputItemsFlat); !extraItems.empty())
    {
        isFailed = true;
        std::println("ERROR: Received more (bogus) items. Extra: {}", toString(extraItems));
    }

    // TEST: No holes in the received sequence.
    if (const auto i = indexOfMissingValue(outputItemsFlatSorted); i != -1)
    {
        isFailed = true;
        std::println("ERROR: Hole at index {}. Items: {} ", i,
                toString(std::ranges::subrange(outputItemsFlatSorted.begin() + i,
                        outputItemsFlatSorted.begin() +
                                std::min(i + 5, static_cast<int>(outputItemsFlatSorted.size())))));
    }

    if (const auto missing = getMissingValues(outputItemsFlatSorted); !missing.empty())
    {
        isFailed = true;
        std::println("ERROR: Missing values: {}", toString(missing));
    }

    // TEST: No duplicates in the received sequence.
    if (const auto i = indexOfDuplicateValue(outputItemsFlatSorted); i != -1)
    {
        isFailed = true;
        std::println("ERROR: Duplicate at index {}. Items: {} ", i,
                toString(std::ranges::subrange(outputItemsFlatSorted.begin() + i,
                        outputItemsFlatSorted.begin() +
                                std::min(i + 5, static_cast<int>(outputItemsFlatSorted.size())))));
    }

    if (const auto dups = getDuplicateValues(outputItemsFlatSorted); !dups.empty())
    {
        isFailed = true;
        std::println("ERROR: Duplicate values: {}", toString(dups));
    }

    // TEST: Consumers didn't get duplicate items.
    for (auto i = 0; i < consumerThreadCount; ++i)
    {
        auto outputItemsUnique = toUnique(outputItems[i]);
        if (outputItemsUnique.size() < outputItems[i].size())
        {
            isFailed = true;
            std::println("ERROR: Consumer {} received duplicate items.", i);
        }

        std::ranges::sort(outputItems[i]);
        if (const auto dups = getDuplicateValues(outputItems[i]); !dups.empty())
        {
            isFailed = true;
            std::println("ERROR: Consumer {} duplicate values: {}", i, toString(dups));
        }
    }

    EXPECT_FALSE(isFailed);

    // TEST: Input and output items are the same.
    for (int i = 0; i < itemCount; ++i)
    {
        EXPECT_EQ(outputItemsFlatSorted[i], inputItemsFlat[i]);
    }
}

TEST(CircularQueue_1, Concurrency_N_Producer_M_Consumer_Multiqueue)
{
    // TEST: Multiple producers, multiple consumers.
    // Create and run producer and consumer threads.
    // Producers take items from the input queue and put them to the work queue.
    // Consumers take items from the work queue and put them to the output queue.

    constexpr auto producerThreadCount = 5;
    constexpr auto consumerThreadCount = 5;
    constexpr auto itemCount = 500;
    constexpr auto workItemCount = 4;

    auto inputQueuePtr = std::make_unique<QueueType<int, itemCount>>();
    auto workQueuePtr = std::make_unique<QueueType<int, workItemCount>>();
    auto outputQueuePtr = std::make_unique<QueueType<int, itemCount>>();

    auto& inputQueue = *inputQueuePtr;
    auto& workQueue = *workQueuePtr;
    auto& outputQueue = *outputQueuePtr;

    for (int i = 0; i < itemCount; ++i)
    {
        inputQueue.add(i);
    }

    std::atomic_bool shouldConsumersStop = false;

    auto producerFunc = [&]()
    {
        std::random_device randDev;
        std::mt19937 randEngine{randDev()};
        std::uniform_int_distribution randDist{1, 100};
        for (auto item = inputQueue.take(); item.has_value(); item = inputQueue.take())
        {
            while (!workQueue.add(*item))
            {
                // Empty.
            }
            // std::this_thread::sleep_for(std::chrono::milliseconds{randDist(randEngine)});
        }
    };

    auto consumerFunc = [&]()
    {
        std::random_device randDev;
        std::mt19937 randEngine{randDev()};
        std::uniform_int_distribution randDist{1, 100};
        while (true)
        {
            auto item = workQueue.take();
            if (item.has_value())
            {
                while (!outputQueue.add(*item))
                {
                    // Empty.
                }
            }
            else if (shouldConsumersStop)
            {
                break;
            }
            // std::this_thread::sleep_for(std::chrono::milliseconds{randDist(randEngine)});
        }
    };

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for (int i = 0; i < consumerThreadCount; ++i)
    {
        consumers.emplace_back(consumerFunc);
    }

    for (int i = 0; i < producerThreadCount; ++i)
    {
        producers.emplace_back(producerFunc);
    }

    for (auto& producer : producers)
    {
        producer.join();
    }

    shouldConsumersStop = true;

    for (auto& consumer : consumers)
    {
        consumer.join();
    }

    // TEST: Input state after threads have finished.
    EXPECT_EQ(inputQueue.count(), 0);
    EXPECT_EQ(inputQueue.isEmpty(), true);

    // TEST: Work queue state after threads have finished.
    EXPECT_EQ(workQueue.count(), 0);
    EXPECT_EQ(workQueue.isEmpty(), true);

    // TEST: Output state after threads have finished.
    EXPECT_EQ(outputQueue.count(), itemCount);
    EXPECT_EQ(outputQueue.isFull(), true);

    // TEST: Output items are the same as input items.
    // The input items are/were an ordered sequence of numbers in [0, N].
    std::vector<int> outputItems;
    for (int i = 0; i < itemCount; ++i)
    {
        const auto item = outputQueue.take();
        outputItems.push_back(i);
    }
    std::sort(outputItems.begin(), outputItems.end());
    for (int i = 0; i < itemCount; ++i)
    {
        EXPECT_EQ(outputItems[i], i);
    }
}
