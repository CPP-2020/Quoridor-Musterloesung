//
// Created by danie on 02.06.2020.
//

#ifndef HACKATHON_EDGE_H
#define HACKATHON_EDGE_H

#include "Graph-commons.h"

namespace Combinatorics
{
    /**
     * \class Edge
     * Represents an edge between two vertices
     */
    class Edge
    {
        friend class Combinatorics::Graph;
    public:

        // C'tor
        explicit Edge(EdgeId id_, VertexId ep1_, VertexId ep2_, Graph const & graph_);

        Vertex const & getEndpoint1() const;
        Vertex const & getEndpoint2() const;

        // returns the endpoint which is not v
        Vertex const & getOtherEndpoint(Vertex const & v) const;

        // checks whether this edge is adjazant with v
        bool isAdjiazent(Vertex const & v) const;

        // checks whether this edge is adjazant with v
        bool isAdjiazent(VertexId v) const;

        // Checks whether this edge connects v and w
        bool connects(Vertex const & v, Vertex const & w) const;

        // Checks whether this edge connects v and w
        bool connects(VertexId v, VertexId w) const;

        // get id of edge
        EdgeId getId() const;

    private:
        EdgeId _id;
        VertexId const _ep1;
        VertexId const _ep2;
        Graph const &  _graph;
    };
    // overload print
    std::ostream & operator<<(std::ostream & out, Edge const & e);
}
#endif //HACKATHON_EDGE_H
