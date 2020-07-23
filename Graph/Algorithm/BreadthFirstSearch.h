//
// Created by danie on 03.07.2020.
//

#ifndef GAMEFIELDGRAPH_BREADTHFIRSTSEARCH_H
#define GAMEFIELDGRAPH_BREADTHFIRSTSEARCH_H

#include <set>
#include <queue>
#include <cassert>
#include <list>
#include "../Graph-commons.h"
#include "../Graph.h"
#include "../VertexVector.h"

namespace Combinatorics
{
    class BreadthFirstSearch
    {
    public:

        BreadthFirstSearch(const Graph &g, VertexId start_id = VertexId(0));
        BreadthFirstSearch(const Graph &g, Vertex const & start_vertex);

        // BFS with some forbidden edges
        BreadthFirstSearch(const Graph &g, std::set<EdgeId> const & forbidden_edge, VertexId start_id = VertexId(0));

        // BFS with some forbidden edges
        BreadthFirstSearch(const Graph &g, std::set<EdgeId> const & forbidden_edge, Vertex const & start_vertex);

        // BFS with only a subset of edges allowed
        BreadthFirstSearch(const Graph &g, VertexVector<bool> const & allowed_edges, VertexId start_id = VertexId(0));

        // BFS with only a subset of edges allowed
        BreadthFirstSearch(const Graph &g, VertexVector<bool> const & allowed_edges, Vertex const & start_vertex);

        const Graph &getG() const;

        VertexId getStartId() const;

        const VertexVector<VertexId> &getPredecessorVector() const;

        const VertexVector<VertexId> &getDistVector() const;

        VertexId getPredecessor(VertexId t) const;

        VertexId getDist(VertexId t) const;

        VertexId getDist(Vertex const & t) const;

        VertexId getPredecessor(Vertex const & t) const;

        // Get the bfs path from start_vertex to t in form of an ordered list
        std::list<VertexId> getPath(VertexId t) const;

        // Get the bfs path from start_vertex to t in form of an ordered list
        std::list<VertexId> getPath(Vertex const & t) const;

        // returns true if and only if t is reachable from startId
        bool is_reachable(VertexId t) const;
        bool is_reachable(Vertex const & t) const;

    private:
        Graph const &_g;

        template <typename UnaryFunction>
        void run(VertexId start_id, UnaryFunction edge_is_allowed);

        ///// Result structures
        VertexId _start_id = Graph::INVALID_VERTEX_ID;
        VertexVector<VertexId> _predecessor;
        VertexVector<VertexId> _dist;
    };

    ///////////////////
    /// Implementation

    template <typename UnaryFunction>
    void BreadthFirstSearch::run(VertexId start_id, UnaryFunction edge_is_allowed)
    {
        assert(static_cast<size_t>(start_id) < static_cast<size_t>(_g.numVertices()));
        _start_id = start_id;
        std::queue<VertexId> q;
        q.push(start_id);
        _dist[start_id] = 0;

        while (!q.empty())
        {
            Vertex const & current =_g.getVertex(q.front());
            q.pop();
            for (EdgeId edge_id = EdgeId(0); edge_id < current.numEdges(); ++edge_id)
            {
                if (edge_is_allowed(edge_id))
                {
                    Vertex const &neighbour = current.getEdge(edge_id).getOtherEndpoint(current);
                    if (_dist[neighbour] == Graph::INVALID_VERTEX_ID)
                    {
                        // We found this vertex for the first time
                        _dist[neighbour] = _dist[current] + 1;
                        _predecessor[neighbour] = current.getId();
                        q.push(neighbour.getId());
                    }
                }
            }
        }
    }
}

#endif //GAMEFIELDGRAPH_BREADTHFIRSTSEARCH_H
