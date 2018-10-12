//
// Created by 王晓丰 on 2018/10/12.
//

#ifndef CTHINKUTILS_THINKGRAPH_H
#define CTHINKUTILS_THINKGRAPH_H

#include <stdio.h>
#include <stdbool.h>

#include "utils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ThinkVertex ThinkVertex;
typedef struct _ThinkEdge ThinkEdge;

typedef struct _ThinkVertex {
    void* m_pData;

    struct _ThinkVertex *m_pNext;
    ThinkEdge *m_pEdges;
};

typedef struct _ThinkEdge {
    unsigned int m_nLength;

    ThinkVertex* m_pSrc;
    ThinkVertex* m_pDest;

    struct _ThinkEdge* m_pNext;
};

typedef struct _ThinkGraph {
    ThinkVertex* m_pVertexs;
//    ThinkDestoryFunc m_pDestoryFunc;
} ThinkGraph;

typedef struct _ThinkShortestPath {
    void* m_pData;
    struct _ThinkShortestPath* m_pNext;
} ThinkShortestPath;

ThinkGraph* think_graph_new();
void think_graph_free(ThinkGraph** ppGraph, ThinkDestoryFunc pDescoryFunc);
void think_graph_shortest_path_free(ThinkShortestPath** ppPath);

ThinkVertex* think_graph_add_vertex(ThinkGraph* pGraph, void* pData);
ThinkVertex* think_graph_get_vertex(ThinkGraph* pGraph, void* pData);
void think_graph_remove_vertex(ThinkGraph* pGraph, void* pData, ThinkDestoryFunc pDescoryFunc);

ThinkEdge* think_graph_add_edge(ThinkGraph* pGraph, ThinkVertex* pSrc, ThinkVertex* pDest, unsigned int nLength);
ThinkEdge* think_graph_get_all_edge_from_me(ThinkGraph* pGraph, void* pData);
void think_graph_remove_edge(ThinkVertex* pVertex, ThinkEdge** ppEdge);

unsigned int think_graph_get_edge_length(ThinkGraph* pGraph, void* pSrc, void* pDest);
ThinkShortestPath* think_graph_shortest_path(ThinkGraph* pGraph, void* pSrc, void* pDest);


#ifdef __cplusplus
}
#endif

#endif //CTHINKUTILS_THINKGRAPH_H
