//
// Created by danie on 02.06.2020.
//

#ifndef HACKATHON_GRAPH_H
#define HACKATHON_GRAPH_H

#include <memory>
#include <algorithm>
#include "Edge.h"
#include "Vertex.h"
#include "PointerIteratorWrapper.h"
#include "SimpleRange.h"
#include "../Logger/Log.h"

namespace Combinatorics
{
    class Graph
    {
        using Logger = DHBW_LOG::CoutLogger<LogLevel::INFO>;
    public:
        // Alias for container and iterator types
        template <typename T>
        using ContainerType = std::vector<T>;
        // use unique ptr for stable storage
        using EdgePtrContainer = ContainerType<std::unique_ptr<Edge>>;
        using EdgeIterator = PointerIteratorWrapper<Edge,EdgePtrContainer,false>;
        using EdgeConstIterator = PointerIteratorWrapper<Edge,EdgePtrContainer,true>;
        using VertexPtrContainer = ContainerType<std::unique_ptr<Vertex>>;
        using VertexIterator = PointerIteratorWrapper<Vertex,VertexPtrContainer,false>;
        using VertexConstIterator = PointerIteratorWrapper<Vertex,VertexPtrContainer,true>;
        using VertexConstRange = SimpleRange<VertexConstIterator>;
        using VertexRange = SimpleRange<VertexIterator>;
        using EdgeConstRange = SimpleRange<EdgeConstIterator>;
        using EdgeRange = SimpleRange<EdgeIterator>;

         // C'tor for empty graph
        explicit Graph();

        // C'tor for graph with n vertices
        explicit Graph(VertexId n);

        // get vertex by id
        Vertex const & getVertex(VertexId id) const;
        Vertex & getVertex(VertexId id);

        // get edge by id
        Edge const & getEdge(EdgeId id) const;
        Edge & getEdge(EdgeId id);

        // get number of vertices
        VertexId numVertices() const;

        // get number of edges
        EdgeId numEdges() const;

        // add a vertex and get it
        Vertex & addVertex();

        // ass k vertices
        void addVertices(VertexId k);

        // add a edge and get the id of the new edge. Parallel edges are not allowed
        Edge const & addEdge(Vertex & ep1, Vertex & ep2);

        // add a edge and get the id of the new edge. Parallel edges are not allowed
        Edge const & addEdge(VertexId ep1, VertexId ep2);

        // get iterator to the first vertex
        VertexIterator vertexBegin();
        VertexConstIterator vertexBegin() const;

        // get iterator to the last vertex
        VertexIterator vertexEnd();
        VertexConstIterator vertexEnd() const;

        // get iterator to the first edge
        EdgeIterator edgeBegin();
        EdgeConstIterator edgeBegin() const;

        // get iterator to the last edge
        EdgeIterator edgeEnd();
        EdgeConstIterator edgeEnd() const;

        // get range of edges
        EdgeRange edgeRange();
        EdgeConstRange edgeRange() const;

        // get range of vertices
        VertexRange vertexRange();
        VertexConstRange vertexRange() const;

        // prints the graph human readable on INFO level
        void printHumanReadable() const;

        // returns true if and only if there is an edge connecting v and w
        bool hasEdge(VertexId v, VertexId w) const;

        // returns true if and only if there is an edge connecting v and w
        bool hasEdge(Vertex const & v, Vertex const & w) const;

        // returns the EdgeId of the Edge {v,w} if it exists.
        // If no edge {v,w} exists INVALID_EDGE_ID is returned
        EdgeId findEdge(VertexId v, VertexId w) const;

        // returns the EdgeId of the Edge {v,w} if it exists.
        // If no edge {v,w} exists INVALID_EDGE_ID is returned
        EdgeId findEdge(Vertex const & v, Vertex const & w) const;


        // Remove edge {v,w}. This is an O(m) operation given the current graph implementation
        void removeEdge(VertexId v, VertexId w);

        // Remove edge e. This is an O(m) operation given the current graph implementation
        void removeEdge(EdgeId e);

        // Removes all edges inside an container c. Pass by copy is intended since we have to sort the container
        template <typename EdgeIdContainer>
        void removeEdges(EdgeIdContainer c);

        static VertexId INVALID_VERTEX_ID;
        static EdgeId INVALID_EDGE_ID;

    private:
        VertexPtrContainer _vertices;
        EdgePtrContainer   _edges;
        static Logger _logger;
        static inline Logger const & LOG() { return _logger; }
    };


    template<typename EdgeIdContainer>
    void Graph::removeEdges(EdgeIdContainer c)
    {
        std::sort(c.begin(),c.end(),[](EdgeId a, EdgeId b){return a > b;});
        for(auto e : c)
        {
            removeEdge(e);
        }
    }
}

#endif //HACKATHON_GRAPH_H
