#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <optional>
#include <ranges>
#include <algorithm>
#include "print.hpp"

constexpr char space = ' ';

using Graph = std::vector<std::vector<int>>;

std::optional<Graph> read_graph_from_file(string_like auto file_path)
{
    Graph res;
    std::ifstream in{static_cast<std::string>(file_path)};
    if (not in.is_open()) return std::nullopt;
    std::string line;
    int i = 0;
    while (std::getline(in, line))
    {
        res.emplace_back();
        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
        for (auto const & [index, ch] : std::ranges::views::enumerate(line))
        {
            if (ch == '1')
            {
                res[i].emplace_back(index);
            }
        }
        i++;
    }

    if (res.empty()) return std::nullopt;
    
    return res;
}


class graph
{
private:
    std::vector<int> visited, order;

    void dfs1(int v)
    {
        visited[v] = 1;
        for (int to : gr[v])
        {
            if (not visited[to])
            {
                dfs1(to);
            }
        }
        order.push_back(v);
    }

    void dfs2(int v, int component)
    {
        visited[v] = component;
        for (int to: g[v])
        {
            if (not visited[to])
            {
                dfs2(to, component);
            }
        }
    }

public:
    std::vector<std::vector<int>> g, gr;
    graph(int vertex_count)
    {
        g.resize(vertex_count);
        gr.resize(vertex_count);
    }

    void add_edge(int a, int b)
    {
        g[a].push_back(b);
        gr[b].push_back(a);
    }

    std::vector<int> find_scc()
    {
        visited.assign(g.size(), 0);
        for (auto v : std::views::iota(0ULL, g.size()))
            if (not visited[v])
                dfs1(v);
        std::reverse(order.begin(), order.end());

        visited.assign(g.size(), 0);
        int sccCount = 0;
        for (int v : order)
            if (not visited[v])
                dfs2(v, ++sccCount);
        return visited;
    }
};