#include "ThinkGraph.h"

#include <stdlib.h>

#include "ThinkStringBuilder.h"

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
    ThinkVertex* pParent = NULL;

    while (pCur) {
        pParent = pCur;
        pCur = pCur->m_pNext;
    }

    if (NULL == pParent) {
        pGraph->m_pVertexs = pVertex;
    } else {
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

        pCur = pCur->m_pNext;
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


    ThinkVertex* pVertexRemove = NULL;
    ThinkVertex* pCur = pGraph->m_pVertexs;
    ThinkVertex* pParent = NULL;
    while (pCur) {
        if (pCur->m_pData == pData) {
            pVertexRemove = pCur;
            break;
        }

        pParent = pCur;
        pCur = pCur->m_pNext;
    }

    if (NULL == pParent) {
        pGraph->m_pVertexs = pVertexRemove->m_pNext;
    } else {
        pParent->m_pNext = pVertexRemove->m_pNext;
    }

    //remove all edges that to pVertexRemove
    think_graph_remove_all_edge_to_vertex(pGraph, pVertexRemove);

    //free memory for this vertex
    think_graph_vertex_free(&pVertexRemove, pDescoryFunc);
}

unsigned int think_graph_vertex_size(ThinkGraph* pGraph)
{
    return_val_if_fail(pGraph != NULL, 0);

    ThinkVertex* pCur = pGraph->m_pVertexs;
    unsigned int nSize = 0;
    while (pCur) {
        nSize++;
        pCur = pCur->m_pNext;
    }

    return nSize;
}

unsigned int think_graph_vertex_edge_size(ThinkVertex* pVertex)
{
    return_val_if_fail(pVertex != NULL, 0);

    ThinkEdge* pCur = pVertex->m_pEdges;
    unsigned int nSize = 0;
    while (pCur) {
        nSize++;
        pCur = pCur->m_pNext;
    }

    return nSize;
}

unsigned int think_graph_edge_size(ThinkGraph* pGraph)
{
    return_val_if_fail(pGraph != NULL, 0);

    ThinkVertex* pCur = pGraph->m_pVertexs;
    unsigned int nSize = 0;
    while (pCur) {
        nSize += think_graph_vertex_edge_size(pCur);
        pCur = pCur->m_pNext;
    }

    return nSize;
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
        ThinkEdge* pEdgeParent = NULL;
        ThinkEdge* pEdgeCur = pVertecCur->m_pEdges;

        while (pEdgeCur) {
            if (pEdgeCur->m_pDest == pVertex) {
                ThinkEdge* pEdgeRemove = pEdgeCur;

                if (NULL == pEdgeParent) {
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

ThinkEdge* think_graph_edge_exists(ThinkGraph* pGraph, void* pSrc, void* pDest)
{
    return_val_if_fail(pGraph != NULL, NULL);
    return_val_if_fail(pSrc != NULL, NULL);
    return_val_if_fail(pDest != NULL, NULL);

    ThinkVertex* pVertexSrc = think_graph_get_vertex(pGraph, pSrc);

    ThinkEdge* pCur = pVertexSrc->m_pEdges;
    while (pCur) {
        if (pCur->m_pDest->m_pData == pDest) {
            return pCur;
        }

        pCur = pCur->m_pNext;
    }

    return NULL;
}

ThinkEdge* think_graph_add_edge(ThinkGraph* pGraph, void* pSrc, void* pDest, unsigned int nLength)
{
    return_val_if_fail(pGraph != NULL, NULL);
    return_val_if_fail(pSrc != NULL, NULL);
    return_val_if_fail(pDest != NULL, NULL);
    return_val_if_fail(pSrc != pDest, NULL);
    return_val_if_fail(nLength > 0, NULL);

    ThinkVertex* pVertexSrc = think_graph_get_vertex(pGraph, pSrc);
    ThinkVertex* pVertexDest = think_graph_get_vertex(pGraph, pDest);

    ThinkEdge* pEdgeExists = think_graph_edge_exists(pGraph, pSrc, pDest);
    if (pEdgeExists) {
        think_graph_remove_edge_plus(pVertexSrc, &pEdgeExists);
    }

    return think_graph_add_edge_plus(pGraph, pVertexSrc, pVertexDest, nLength);
}

ThinkEdge* think_graph_add_edge_plus(ThinkGraph* pGraph, ThinkVertex* pSrc, ThinkVertex* pDest, unsigned int nLength)
{
    return_val_if_fail(pGraph != NULL, NULL);
    return_val_if_fail(pSrc != NULL, NULL);
    return_val_if_fail(pDest != NULL, NULL);
    return_val_if_fail(pSrc->m_pData != pDest->m_pData, NULL);
    return_val_if_fail(nLength > 0, NULL);

    ThinkEdge* pEdgeExists = think_graph_edge_exists(pGraph, pSrc->m_pData, pDest->m_pData);
    if (pEdgeExists) {
        think_graph_remove_edge_plus(pSrc, &pEdgeExists);
    }

    return think_graph_edge_new(pSrc, pDest, nLength);
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

ThinkEdge* think_graph_get_edge(ThinkGraph* pGraph, void* pSrc, void* pDest)
{
    return_val_if_fail(pGraph != NULL, NULL);
    return_val_if_fail(pSrc != NULL, NULL);
    return_val_if_fail(pDest != NULL, NULL);

    ThinkVertex* pVertex = think_graph_get_vertex(pGraph, pSrc);
    return_val_if_fail(pVertex != NULL, NULL);

    ThinkEdge* pCur = pVertex->m_pEdges;
    while (pCur && pCur->m_pDest->m_pData != pDest) {
        pCur = pCur->m_pNext;
    }

    return pCur;
}

void think_graph_remove_edge(ThinkGraph* pGraph, void* pSrc, void* pDest)
{
    return_if_fail(pGraph != NULL);
    return_if_fail(pSrc != NULL);
    return_if_fail(pDest != NULL);

    ThinkVertex* pVertex = think_graph_get_vertex(pGraph, pSrc);
    return_if_fail(pVertex != NULL);

    ThinkEdge* pEdge = think_graph_get_edge(pGraph, pSrc, pDest);
    return_if_fail(pEdge != NULL);

    think_graph_remove_edge_plus(pVertex, &pEdge);
}

void think_graph_remove_edge_plus(ThinkVertex* pVertex, ThinkEdge** ppEdge)
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


int think_graph_get_edge_length(ThinkGraph* pGraph, void* pSrc, void* pDest)
{
    return_val_if_fail(pGraph != 0, -1);
    return_val_if_fail(pSrc != 0, -1);
    return_val_if_fail(pDest != 0, -1);

    if (pSrc == pDest) {
        return 0;
    }

    ThinkVertex* pVertexSrc = think_graph_get_vertex(pGraph, pSrc);

    ThinkEdge* pCur = pVertexSrc->m_pEdges;
    while (pCur) {
        if (pCur->m_pDest->m_pData == pDest) {
            return pCur->m_nLength;
        }

        pCur = pCur->m_pNext;
    }

    return -1;
}

void think_graph_print(ThinkGraph* pGraph, ThinkToStringFunc pToStringFunc)
{
    return_if_fail(pGraph);
    return_if_fail(pToStringFunc != NULL);

    ThinkVertex* pVertexCur = pGraph->m_pVertexs;
    while (pVertexCur) {
        if (NULL == pVertexCur->m_pData) {
            continue;
        }

        char szVal[128];

        (pToStringFunc)(pVertexCur->m_pData, szVal, 128);
        printf("%s --> ", szVal);

        ThinkEdge* pEdgeCur = pVertexCur->m_pEdges;
        while (pEdgeCur) {
            (pToStringFunc)(pEdgeCur->m_pDest->m_pData, szVal, 128);
            printf(" %s|%d --> ", szVal, pEdgeCur->m_nLength);
            pEdgeCur = pEdgeCur->m_pNext;
        }

        pVertexCur = pVertexCur->m_pNext;
        printf(" NULL\n");
    }
    printf("\n\n");
}

char* think_graph_print_to_string(ThinkGraph* pGraph, ThinkToStringFunc pToStringFunc)
{
    return_val_if_fail(pGraph, NULL);
    return_val_if_fail(pToStringFunc != NULL, NULL);

    ThinkStringBuilder* pSB = think_stringbuilder_create();
    think_stringbuilder_append(pSB, "\n\n");

    ThinkVertex* pVertexCur = pGraph->m_pVertexs;
    while (pVertexCur) {
        if (NULL == pVertexCur->m_pData) {
            continue;
        }

        char szVal[128];

        (pToStringFunc)(pVertexCur->m_pData, szVal, 128);
        think_stringbuilder_appendf(pSB, "%s --> ", szVal);

        ThinkEdge* pEdgeCur = pVertexCur->m_pEdges;
        while (pEdgeCur) {
            (pToStringFunc)(pEdgeCur->m_pDest->m_pData, szVal, 128);
            think_stringbuilder_appendf(pSB, " %s|%d --> ", szVal, pEdgeCur->m_nLength);
            pEdgeCur = pEdgeCur->m_pNext;
        }

        pVertexCur = pVertexCur->m_pNext;
        think_stringbuilder_appendf(pSB, " NULL\n");
    }
    think_stringbuilder_appendf(pSB, "\n\n");

    char* pszRet = think_stringbuilder_strdup(pSB);
    think_stringbuilder_free(pSB);

    return pszRet;
}

//-----------------------------------------------------------------------
//for shortest path
//-----------------------------------------------------------------------
static int think_graph_get_vertex_position(ThinkGraph* pGraph, void* pData);
static ThinkVertex* think_graph_get_vertex_by_position(ThinkGraph* pGraph, unsigned int nPos);

#define ARRAY_CEL 4
#define ARRAY_CEL_UNVISITED 3

static int** shortest_init_status_array(unsigned int nRow, unsigned int nCel);
static int shortest_next_pos(int** ppStatus, unsigned int nRow);
static unsigned int shortest_vertex_unvisited(int** ppStatus, unsigned int nRow);
static int shortest_get_cur_shortest_distance(int** ppStatus, int nSrc, int nDest);
static int shortest_is_visited(int** ppStatus, int nPos);
static ThinkShortestPath* think_graph_shortest_path_new();
static void think_graph_shortest_path_node_prepand(ThinkShortestPath* pPath, void* pData);
static ThinkShortestPathNode* think_graph_shortest_path_node_new(void* pData);

static int think_graph_get_vertex_position(ThinkGraph* pGraph, void* pData)
{
    return_val_if_fail(pGraph != NULL, -1);
    return_val_if_fail(pData != NULL, -1);

    ThinkVertex* pCur = pGraph->m_pVertexs;
    int nPos = 0;
    while (pCur) {
        if (pCur->m_pData == pData) {
            return nPos;
        }

        nPos++;
        pCur = pCur->m_pNext;
    }

    return -1;
}

static ThinkVertex* think_graph_get_vertex_by_position(ThinkGraph* pGraph, unsigned int nPos)
{
    return_val_if_fail(pGraph != NULL, NULL);

    ThinkVertex* pCur = pGraph->m_pVertexs;
    for (unsigned int i = 0; i < nPos; ++i) {
        if (pCur) {
            pCur = pCur->m_pNext;
        } else {
            return NULL;
        }
    }

    return pCur;
}

void think_graph_shortest_path_free(ThinkShortestPath** ppPath)
{
    return_if_fail(ppPath != NULL);
    return_if_fail(*ppPath != NULL);

    ThinkShortestPathNode* pCur = (*ppPath)->m_pNodes;
    while (pCur) {
        ThinkShortestPathNode* pTemp = pCur;
        pCur = pCur->m_pNext;

        free(pTemp);
    }

    free(*ppPath);
    *ppPath = NULL;
}

static int** shortest_init_status_array(unsigned int nRow, unsigned int nCel)
{
    int** ppArray = (int**) malloc(sizeof(int*) * nRow);
    for(int i=0; i < nRow; i++ )
    {
        ppArray[i] = (int *) malloc(sizeof(int) * 4 );
    }

    for (unsigned int i = 0; i < nRow; ++i) {
        for (unsigned int j = 0; j < nCel; ++j) {
            if (0 == j) {
                ppArray[i][j] = i;
            } else if (1 == j) {
                ppArray[i][j] = INT32_MAX;
            } else if (2 == j) {
                ppArray[i][j] = -1;
            } else {
                ppArray[i][j] = 0;
            }
        }
    }

    return ppArray;
}

static unsigned int shortest_vertex_unvisited(int** ppStatus, unsigned int nRow)
{
    unsigned int nCount = 0;
    for (unsigned int i = 0; i < nRow; ++i) {
        if (0 == ppStatus[i][ARRAY_CEL_UNVISITED]) {
            nCount++;
        }
    }

    return nCount;
}

static int shortest_next_pos(int** ppStatus, unsigned int nRow)
{
    unsigned int nUnvisited = shortest_vertex_unvisited(ppStatus, nRow);
    if (nUnvisited < 2) {
        return -1;
    }

    int nPos = -1;
    int nMin = INT32_MAX;
    for (unsigned int i = 0; i < nRow; ++i) {
        if (1 == shortest_is_visited(ppStatus, i)) {
            continue;
        }

        if (ppStatus[i][1] <= nMin) {
            nPos = i;
            nMin = ppStatus[i][1];
        }
    }

    return nPos;
}

static int shortest_is_visited(int** ppStatus, int nPos)
{
    return ppStatus[nPos][3];
}

static int shortest_get_cur_shortest_distance(int** ppStatus, int nSrc, int nDest)
{
    return_val_if_fail(ppStatus[nSrc][1] == 0, INT32_MAX);
    return ppStatus[nDest][1];
}

/**
see video: https://www.youtube.com/watch?v=pVfj6mxhdMw
vertex	shortest	pre_vertex	visited
A	0	-1	1
B	4	A	1
C	2	A	1
D	9	E	1
E	5	C	1
F	20	D	0

 */

ThinkShortestPath* think_graph_shortest_path(ThinkGraph* pGraph, void* pSrc, void* pDest)
{
    return_val_if_fail(pGraph != NULL, NULL);
    return_val_if_fail(pSrc != NULL, NULL);
    return_val_if_fail(pDest != NULL, NULL);

    int nSrc = think_graph_get_vertex_position(pGraph, pSrc);
    int nDest = think_graph_get_vertex_position(pGraph, pDest);

    return_val_if_fail(nSrc >= 0, NULL);
    return_val_if_fail(nDest >= 0, NULL);

    //init status table
    unsigned int nRow = think_graph_vertex_size(pGraph);
    unsigned int nCel = ARRAY_CEL;

    int** ppStatus = shortest_init_status_array(nRow, nCel);
    ppStatus[nSrc][1] = 0;
    ppStatus[nSrc][2] = -1;

    int nCurPos = shortest_next_pos(ppStatus, nRow);
    while (nCurPos >= 0) {
        if (1 == shortest_is_visited(ppStatus, nCurPos)) {
            ppStatus[nCurPos][3] = 1;
            nCurPos = shortest_next_pos(ppStatus, nRow);
            continue;
        }

        int nCurPosDistance = shortest_get_cur_shortest_distance(ppStatus, nSrc, nCurPos);
        for (unsigned int i = 0; i < nRow; ++i) {
            int nCurMin = shortest_get_cur_shortest_distance(ppStatus, nSrc, i);


            ThinkVertex* pVertexSrc = think_graph_get_vertex_by_position(pGraph, (unsigned int) nCurPos);
            ThinkVertex* pVertexDest = think_graph_get_vertex_by_position(pGraph, i);
            int nDestence = think_graph_get_edge_length(pGraph, pVertexSrc->m_pData, pVertexDest->m_pData);

            if (-1 == nDestence) {
                continue;
            }

            if (nCurPosDistance + nDestence < nCurMin) {
                ppStatus[i][1] = nCurPosDistance + nDestence;
                ppStatus[i][2] = nCurPos;
            }
        }

        ppStatus[nCurPos][3] = 1;
        nCurPos = shortest_next_pos(ppStatus, nRow);
    }

//    for (unsigned int i = 0; i < nRow; ++i) {
//        for (int j = 0; j < ARRAY_CEL; ++j) {
//            printf("%d ", ppStatus[i][j]);
//        }
//
//        printf("\n");
//    }

    ThinkShortestPath* pPath = think_graph_shortest_path_new();
    pPath->m_nDistance = shortest_get_cur_shortest_distance(ppStatus, nSrc, nDest);
    if (pPath->m_nDistance != INT32_MAX) {
        int nPos = (unsigned int)nDest;
        while (ppStatus[nPos][2] != -1) {
            ThinkVertex* pVertex = think_graph_get_vertex_by_position(pGraph, (unsigned int)nPos);
            think_graph_shortest_path_node_prepand(pPath, pVertex->m_pData);

            nPos = ppStatus[nPos][2];
        }

        //prepend start vertex
        ThinkVertex* pVertex = think_graph_get_vertex_by_position(pGraph, (unsigned int)nPos);
        think_graph_shortest_path_node_prepand(pPath, pVertex->m_pData);
    }

    return pPath;
}

static void think_graph_shortest_path_node_prepand(ThinkShortestPath* pPath, void* pData)
{
    ThinkShortestPathNode* pNode = think_graph_shortest_path_node_new(pData);
    if (NULL == pPath->m_pNodes) {
        pPath->m_pNodes = pNode;
    } else {
        pNode->m_pNext = pPath->m_pNodes;
        pPath->m_pNodes = pNode;
    }
}

static ThinkShortestPathNode* think_graph_shortest_path_node_new(void* pData)
{
    ThinkShortestPathNode* pNode = (ThinkShortestPathNode*) malloc(sizeof(ThinkShortestPathNode));
    pNode->m_pData = pData;
    pNode->m_pNext = NULL;

    return pNode;
}


static ThinkShortestPath* think_graph_shortest_path_new()
{
    ThinkShortestPath* pPath = (ThinkShortestPath*) malloc(sizeof(ThinkShortestPath));
    pPath->m_nDistance = INT32_MAX;
    pPath->m_pNodes = NULL;

    return pPath;
}