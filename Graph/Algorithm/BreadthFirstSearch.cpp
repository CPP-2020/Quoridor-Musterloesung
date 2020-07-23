//
// Created by danie on 03.07.2020.
//

#include "BreadthFirstSearch.h"
#include <queue>
#include <cassert>

namespace Combinatorics
{
    BreadthFirstSearch:: BreadthFirstSearch(const Graph &g_, VertexId start_id)
    :
        _g(g_),
        _predecessor(g_,Graph::INVALID_VERTEX_ID),
        _dist(g_,Graph::INVALID_VERTEX_ID)
    {
        run(start_id,[](EdgeId e){return true;});
    }

    BreadthFirstSearch::BreadthFirstSearch(const Graph &g_, std::set<EdgeId> const &forbidden_edge, VertexId start_id)
    :
            _g(g_),
            _predecessor(g_,Graph::INVALID_VERTEX_ID),
            _dist(g_,Graph::INVALID_VERTEX_ID)
    {
        run(start_id,[&forbidden_edge](EdgeId e){return forbidden_edge.find(e) == forbidden_edge.end();});
    }

    BreadthFirstSearch::BreadthFirstSearch(const Graph &g_, VertexVector<bool> const &allowed_edges, VertexId start_id)
            :
            _g(g_),
            _predecessor(g_,Graph::INVALID_VERTEX_ID),
            _dist(g_,Graph::INVALID_VERTEX_ID)
    {
        run(start_id,[&allowed_edges](EdgeId e){return allowed_edges[e];});
    }

    BreadthFirstSearch::BreadthFirstSearch(const Graph &g, Vertex const & start_vertex)
    :
        BreadthFirstSearch(g,start_vertex.getId())
    {}

    BreadthFirstSearch::BreadthFirstSearch(const Graph &g, std::set<EdgeId> const &forbidden_edge,
                                           Vertex const &start_vertex)
            :
            BreadthFirstSearch(g,forbidden_edge,start_vertex.getId())
    {}

    BreadthFirstSearch::BreadthFirstSearch(const Graph &g, VertexVector<bool> const &allowed_edges,
                                           Vertex const &start_vertex)
            :
            BreadthFirstSearch(g,allowed_edges,start_vertex.getId())
    {}

    const Graph &BreadthFirstSearch::getG() const
    {
        return _g;
    }

    VertexId BreadthFirstSearch::getStartId() const
    {
        return _start_id;
    }

    const VertexVector<VertexId> &BreadthFirstSearch::getPredecessorVector() const
    {
        return _predecessor;
    }

    const VertexVector<VertexId> &BreadthFirstSearch::getDistVector() const
    {
        return _dist;
    }

    bool BreadthFirstSearch::is_reachable(VertexId t) const
    {
        return _dist[t] != Graph::INVALID_VERTEX_ID;
    }

    bool BreadthFirstSearch::is_reachable(Vertex const & t) const
    {
        return is_reachable(t.getId());
    }

    std::list<VertexId> BreadthFirstSearch::getPath(VertexId t) const
    {
        if (! is_reachable(t))
        {
            throw std::runtime_error("BFS: Invalid getPath command to non-reachable t");
        }

        std::list<VertexId> res;
        VertexId current = t;
        while (current != getStartId())
        {
            res.push_front(current);
            current = getPredecessor(current);
        }
        res.push_front(getStartId());
        return res;
    }

    std::list<VertexId> BreadthFirstSearch::getPath(Vertex const &t) const
    {
        return getPath(t.getId());
    }

    VertexId BreadthFirstSearch::getPredecessor(VertexId t) const
    {
        assert(t < _g.numVertices());
        return _predecessor[t];
    }

    VertexId BreadthFirstSearch::getPredecessor(Vertex const & t) const
    {
        return getPredecessor(t.getId());
    }

    VertexId BreadthFirstSearch::getDist(VertexId t) const
    {
        assert(t < _g.numVertices());
        return _dist[t];
    }

    VertexId BreadthFirstSearch::getDist(Vertex const & t) const
    {
        return getDist(t.getId());
    }
}


