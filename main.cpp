#include <iostream>
#include <vector>
#include <fstream>
#include <optional>
#include "graph.hpp"

void dfs(std::vector<std::vector<int>> & graph, int v, std::vector<int> & visited)
{
    visited[v] = 1;

    for (auto to : graph[v])
        if (not visited[to])
            dfs(graph, to, visited);
}

int get_count_of_components(Graph & graph)
{
    std::vector<int> visited;
    visited.resize(graph.size());
    
    int comp_count = 0;
    for (auto const & [index, _] : std::views::enumerate(graph))
    {
        if (not visited[index])
        {
            comp_count++;
            dfs(graph, index, visited);
        }
    }
    return comp_count;
}

std::optional<Graph> get_components(Graph & graph)
{
    std::vector<int> vis;
    Graph res;
    vis.resize(graph.size());
    std::vector<int> comp;
    for (auto const & [index, el] : std::views::enumerate(graph))
    {
        if (vis[index]) continue;

        dfs(graph, index, vis);
        for (auto const & [i, v] : std::views::enumerate(vis) | std::views::drop(index))
        {
            if (v) comp.emplace_back(std::move(i));
        }
        res.emplace_back(std::move(comp));
        comp.clear();
    }
    if (res.empty()) return std::nullopt;
    return res;
}

int main(int, char**)
{
    std::optional<Graph> g;
    g = read_graph_from_file("C:\\Users\\1\\asd_45\\graph.txt");
    if (not g.has_value()) return -1;
    print(g.value());
    
    graph g_obj(g.value().size());
    for (auto i : std::views::iota(0ULL, g.value().size()))
        for (auto j : g.value()[i])
            g_obj.add_edge(i, j);    

    print("g_obj.g\n");
    print(g_obj.g);
    print("g_obj.gr\n");
    print(g_obj.gr);

    std::vector<int> nums;
    auto scc = g_obj.find_scc();
    for (auto i : std::views::iota(0ULL, g.value().size()))
        nums.push_back(i);
    print("scc\n");
    print(nums);
    print(scc);
    return 0;
}
