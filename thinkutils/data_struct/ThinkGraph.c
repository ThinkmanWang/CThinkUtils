#include "ThinkGraph.h"

#include <stdlib.h>


static ThinkVertex* think_graph_vertex_new(void* pData);
static void think_graph_vertex_free(ThinkVertex** ppVertex, ThinkDestoryFunc pDestoryFunc);
static ThinkEdge* think_graph_edge_new(ThinkVertex* pSrc, ThinkVertex* pDest, unsigned int nLength);
static void think_graph_edge_free(ThinkEdge** ppEdge);
static void think_graph_remove_all_edge(ThinkVertex* pVertex);
static void think_graph_remove_all_edge_to_vertex(ThinkGraph* pGraph, ThinkVertex* pVertex);

ThinkGraph* think_graph_new()
{
    ThinkGraph* pGraph = (ThinkGraph*) malloc(sizeof(ThinkGraph));
    pGraph->m_pVertexs = NULL;

    return pGraph;
}

void think_graph_free(ThinkGraph** ppGraph, ThinkDestoryFunc pDescoryFunc)
{
    return_if_fail(ppGraph != NULL);
    return_if_fail(*ppGraph != NULL);

    //free all vertex and edge
    ThinkVertex* pCur = (*ppGraph)->m_pVertexs;
    while (pCur) {
        ThinkVertex* pNext = pCur->m_pNext;

        think_graph_vertex_free(&pCur, pDescoryFunc);

        pCur = pNext;
    }

    free(*ppGraph);
    *ppGraph = NULL;
}

void think_graph_shortest_path_free(ThinkShortestPath** ppPath)
{
    return_if_fail(ppPath != NULL);
    return_if_fail(*ppPath != NULL);

    ThinkShortestPath* pCur = *ppPath;
    while (pCur) {
        ThinkShortestPath* pNext = pCur->m_pNext;

        free(pCur);
        pCur = NULL;

        pCur = pNext;
    }

    *ppPath = NULL;
}

static ThinkVertex* think_graph_vertex_new(void* pData)
{
    return_val_if_fail(pData != NULL, NULL);

    ThinkVertex* pVertex = (ThinkVertex*) malloc(sizeof(ThinkVertex));
    pVertex->m_pData = pData;
    pVertex->m_pNext = NULL;
    pVertex->m_pEdges = NULL;

    return pVertex;
}

static void think_graph_vertex_free(ThinkVertex** ppVertex, ThinkDestoryFunc pDestoryFunc)
{
    return_if_fail(ppVertex != NULL);
    return_if_fail(*ppVertex != NULL);

    ThinkEdge* pCur = (*ppVertex)->m_pEdges;
    while (pCur) {
        ThinkEdge* pNext = pCur->m_pNext;

        think_graph_edge_free(&pCur);

        pCur = pNext;
    }

    if (pDestoryFunc) {
        (pDestoryFunc)((*ppVertex)->m_pData);
    }

    *ppVertex = NULL;
}

static ThinkEdge* think_graph_edge_new(ThinkVertex* pSrc, ThinkVertex* pDest, unsigned int nLength)
{
    return_val_if_fail(pSrc != NULL, NULL);
    return_val_if_fail(pDest != NULL, NULL);
    return_val_if_fail(nLength > 0, NULL);

    ThinkEdge* pEdge = (ThinkEdge*) malloc(sizeof(ThinkEdge));
    pEdge->m_pNext = NULL;
    pEdge->m_nLength = nLength;
    pEdge->m_pSrc = pSrc;
    pEdge->m_pDest = pDest;

    ThinkEdge* pCur = pSrc->m_pEdges;
    ThinkEdge* pParent = pCur;
    if (NULL == pCur) {
        pSrc->m_pEdges = pEdge;
    } else {
        while (pCur) {
            pParent = pCur;
            pCur = pCur->m_pNext;
        }

        pParent->m_pNext = pEdge;
    }

    return pEdge;
}

static void think_graph_edge_free(ThinkEdge** ppEdge)
{
    return_if_fail(ppEdge != NULL);
    return_if_fail(*ppEdge != NULL);

    free(*ppEdge);
    *ppEdge = NULL;
}





ThinkVertex* think_graph_add_vertex(ThinkGraph* pGraph, void* pData)
{
    return_val_if_fail(pGraph != NULL, NULL);
    return_val_if_fail(pData != NULL, NULL);

    ThinkVertex* pExists = think_graph_get_vertex(pGraph, pData);
    if (pExists) {
        return pExists;
    }

    ThinkVertex* pVertex = think_graph_vertex_new(pData);
    ThinkVertex* pCur = pGraph->m_pVertexs;
    ThinkVertex* pParent = pCur;
    if (NULL == pCur) {
        pGraph->m_pVertexs = pVertex;
    } else {
        while (pCur) {
            pParent = pCur;
            pCur = pCur->m_pNext;
        }

        pParent->m_pNext = pVertex;
    }

    return pVertex;
}

ThinkVertex* think_graph_get_vertex(ThinkGraph* pGraph, void* pData)
{
    return_val_if_fail(pGraph != NULL, NULL);
    return_val_if_fail(pData != NULL, NULL);

    ThinkVertex* pCur = pGraph->m_pVertexs;
    while (pCur) {
        if (pCur->m_pData == pData) {
            return pCur;
        }
    }

    return NULL;
}

void think_graph_remove_vertex(ThinkGraph* pGraph, void* pData, ThinkDestoryFunc pDescoryFunc)
{
    return_if_fail(pGraph != NULL);
    return_if_fail(pGraph->m_pVertexs != NULL);
    return_if_fail(pData != NULL);

    ThinkVertex* pExists = think_graph_get_vertex(pGraph, pData);
    if (NULL == pExists) {
        return;
    }

    ThinkVertex* pParent = pGraph->m_pVertexs;
    ThinkVertex* pVertexRemove = NULL;

    if (pParent->m_pData == pData) {
        pVertexRemove = pParent;
    } else {
        pVertexRemove = pParent->m_pNext;
    }

    while (pVertexRemove) {
        if (pVertexRemove->m_pData == pData) {
            break;
        }

        pParent = pVertexRemove;
        pVertexRemove = pVertexRemove->m_pNext;

    }

    //remove pCur from pGraph->m_pVertexs
    if (pGraph->m_pVertexs == pVertexRemove) {
        pGraph->m_pVertexs = pVertexRemove->m_pNext;
    } else {
        pParent->m_pNext = pVertexRemove->m_pNext;
    }

    //free all edge for pVertexRemove
    think_graph_remove_all_edge(pVertexRemove);

    //remove all edges that to pVertexRemove
    think_graph_remove_all_edge_to_vertex(pGraph, pVertexRemove);

    //free memory for this vertex
    think_graph_vertex_free(&pVertexRemove, pDescoryFunc);
}

static void think_graph_remove_all_edge(ThinkVertex* pVertex)
{
    return_if_fail(pVertex != NULL);

    ThinkEdge* pEdgeRemove = pVertex->m_pEdges;
    while (pEdgeRemove) {
        ThinkEdge* pEdgeTemp = pEdgeRemove->m_pNext;

        think_graph_edge_free(&pEdgeRemove);
        pEdgeRemove = pEdgeTemp;
    }
}

static void think_graph_remove_all_edge_to_vertex(ThinkGraph* pGraph, ThinkVertex* pVertex)
{
    return_if_fail(pGraph != NULL);
    return_if_fail(pVertex != NULL);

    ThinkVertex* pVertecCur = pGraph->m_pVertexs;
    while (pVertecCur) {
        ThinkEdge* pEdgeParent = pVertecCur->m_pEdges;
        ThinkEdge* pEdgeCur = pEdgeParent;

        while (pEdgeCur) {
            if (pEdgeCur->m_pDest == pVertex) {
                ThinkEdge* pEdgeRemove = pEdgeCur;

                if (pEdgeCur == pVertecCur->m_pEdges) {
                    pVertecCur->m_pEdges = pEdgeCur->m_pNext;

                    pEdgeCur = pEdgeCur->m_pNext;
                    pEdgeParent = pEdgeCur;
                } else {
                    pEdgeParent->m_pNext = pEdgeCur->m_pNext;
                }

                think_graph_edge_free(&pEdgeRemove);

                continue;
            }

            pEdgeParent = pEdgeCur;
            pEdgeCur = pEdgeCur->m_pNext;
        }

        pVertecCur = pVertecCur->m_pNext;
    }
}

ThinkEdge* think_graph_add_edge(ThinkGraph* pGraph, ThinkVertex* pSrc, ThinkVertex* pDest, unsigned int nLength)
{
    return_val_if_fail(pGraph != NULL, NULL);
    return_val_if_fail(pSrc != NULL, NULL);
    return_val_if_fail(pDest != NULL, NULL);
    return_val_if_fail(nLength > 0, NULL);

    ThinkEdge* pEdge = think_graph_edge_new(pSrc, pDest, nLength);
    ThinkEdge* pCur = pSrc->m_pEdges;
    if (NULL == pCur) {
        pSrc->m_pEdges = pEdge;
    } else {
        while (pCur->m_pNext) {
            pCur = pCur->m_pNext;
        }

        pCur->m_pNext = pEdge;
    }

    return pEdge;
}

ThinkEdge* think_graph_get_all_edge_from_me(ThinkGraph* pGraph, void* pData)
{
    return_val_if_fail(pGraph != NULL, NULL);
    return_val_if_fail(pData != NULL, NULL);

    ThinkVertex* pVertex = think_graph_get_vertex(pGraph, pData);
    if (pVertex) {
        return pVertex->m_pEdges;
    }

    return NULL;
}

void think_graph_remove_edge(ThinkVertex* pVertex, ThinkEdge** ppEdge)
{
    return_if_fail(pVertex != NULL);
    return_if_fail(ppEdge != NULL);
    return_if_fail(*ppEdge != NULL);

    ThinkEdge* pCur = pVertex->m_pEdges;
    ThinkEdge* pParent = NULL;
    while (pCur && pCur != *ppEdge) {
        pParent = pCur;
        pCur = pCur->m_pNext;
    }

    if (pCur) {
        if (NULL == pParent) {
            pVertex->m_pEdges = pCur->m_pNext;
        } else {
            pParent->m_pNext = pCur->m_pNext;
        }

        think_graph_edge_free(ppEdge);
    }

}


unsigned int think_graph_get_edge_length(ThinkGraph* pGraph, void* pSrc, void* pDest)
{
    return_val_if_fail(pGraph != 0, 0);
    return_val_if_fail(pSrc != 0, 0);
    return_val_if_fail(pDest != 0, 0);

    ThinkVertex* pVertexSrc = think_graph_get_vertex(pGraph, pSrc);
    ThinkVertex* pVertexDest = think_graph_get_vertex(pGraph, pDest);

    ThinkEdge* pCur = pVertexSrc->m_pEdges;
    while (pCur) {
        if (pCur->m_pDest == pVertexDest) {
            return pCur->m_nLength;
        }

        pCur = pCur->m_pNext;
    }

    return 0;
}

ThinkShortestPath* think_graph_shortest_path(ThinkGraph* pGraph, void* pSrc, void* pDest)
{
    return NULL;
}
