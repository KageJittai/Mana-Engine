#ifndef ASTAR_H
#define ASTAR_H

#include <queue>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

namespace Mana {

template<class GridGraphT>
class AStar
{
    using Node = typename GridGraphT::Node;

    GridGraphT mGraph;
    struct SearchData {
        SearchData(const Node cameFrom, int cost = 0) :
            mCameFrom(cameFrom), mCost(cost) { }

        const Node &cameFrom() const {
            return mCameFrom;
        }

        // Node we came from.
        Node mCameFrom;

        // Cost of getting to node
        int mCost;
    };

    using fScoredNode = std::pair<int, Node>;
    struct CompareFScoredNodes {
        bool operator() (const fScoredNode &a, const fScoredNode &b)
        {
            return a.first > b.first;
        }
    };

    struct NodeHasher {
        std::size_t operator() (const Node &node) const
        {
            return std::hash<decltype(node.id())>{}(node.id());
        }
    };

public:
    AStar(GridGraphT graph) :
        mGraph(graph)
    {
    }

    std::vector<Node> findPath(const Node &start, const Node &goal)
    {
        std::priority_queue<fScoredNode, std::vector<fScoredNode>, CompareFScoredNodes> frontier;
        std::unordered_map<Node, SearchData, NodeHasher> visited;

        visited.reserve(mGraph.maxSize());

        frontier.push(std::make_pair(0, start));
        visited.emplace(start, SearchData(start));
        //visited.insert({start, SearchData(start)});

        std::vector<Node> neighbors;
        while (!frontier.empty()) {
            auto current = std::move(frontier.top().second);
            frontier.pop();

            if (current == goal) {
                break;
            }

            // Get new neighbors
            neighbors.clear();
            mGraph.findNeighbors(current, neighbors);

            auto lastCost = visited.at(current).mCost;
            for (auto &next: neighbors) {
                if (!visited.count(next)) {
                    SearchData data(current, lastCost + mGraph.moveCost(current, next));
                    frontier.emplace(data.mCost + mGraph.heuristicDistance(next, goal), next);
                    //visited.insert({next, data});
                    visited.emplace(next, std::move(data));
                }
            }
        }

        std::vector<Node> ret;

        auto end = visited.find(goal);

        if (end != visited.end()) {
            auto last = end->first;
            while (last != start) {
                ret.push_back(last);
                last = visited.at(last).cameFrom();
            }

            ret.push_back(start);
        }

        return ret;
    }
};

}

#endif // ASTAR_H
