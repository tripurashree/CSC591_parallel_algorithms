#include "../include/performance.h"
#include "../include/bfs.h"
#include "../include/graph.h"
#include <iostream>
#include <chrono> // Include for timing

bool verify_results(const std::vector<int> &serial_result, const std::vector<int> &parallel_result)
{
    if (serial_result != parallel_result)
    {
        std::cout << "Results mismatch.\n";
        return false;
    }
    std::cout << "Results match.\n";
    return true;
}

void compare_bfs_performance(const std::vector<Node> &node_list, const std::vector<Edge> &edge_list, unsigned int source_node_no)
{
    // Measure execution time for serial BFS
    auto start_serial = std::chrono::high_resolution_clock::now();
    std::vector<int> serial_result = serial_bfs(node_list, edge_list, source_node_no);
    auto end_serial = std::chrono::high_resolution_clock::now();
    auto serial_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_serial - start_serial).count();

    std::cout << "Serial BFS execution time: " << serial_duration << " ms\n";

    size_t thread_counts[] = {4, 8, 10, 12, 16}; // Number of threads
    std::cout << "Thread Count | Execution Time (ms) | Speedup | Efficiency\n";
    std::cout << "-----------------------------------------------------------\n";

    for (size_t i = 0; i < sizeof(thread_counts) / sizeof(thread_counts[0]); ++i)
    {
        // Measure execution time for parallel BFS
        auto start_parallel = std::chrono::high_resolution_clock::now();
        auto parallel_result = parallel_bfs(node_list, edge_list, source_node_no, thread_counts[i]);
        auto end_parallel = std::chrono::high_resolution_clock::now();
        auto parallel_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_parallel - start_parallel).count();

        // Verify results
        verify_results(serial_result, parallel_result);

        // Calculate speedup and efficiency
        double speedup = static_cast<double>(serial_duration) / parallel_duration;
        double efficiency = speedup / thread_counts[i];

        // Display results
        std::cout << thread_counts[i] << "           | " << parallel_duration << " ms          | "
                  << speedup << "      | " << efficiency * 100 << "%\n";
    }
}