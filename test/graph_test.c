
#include <stdio.h>
#include <stdlib.h>

#include "ThinkGraph.h"
#include "log.h"
#include "ThinkStringBuilder.h"

//typedef char* (*ThinkToStringFunc) (void* pData, char* pStr, unsigned int nMax);
char* to_string(void* pData, char* pStr, unsigned int nMax)
{
    snprintf(pStr, nMax, "%d", (int)pData);
    return pStr;
}

void test1()
{
    ThinkGraph* pGraph = think_graph_new();

    think_graph_add_vertex(pGraph, (void*)1);
    think_graph_add_vertex(pGraph, (void*)2);
    think_graph_add_vertex(pGraph, (void*)3);
    think_graph_add_vertex(pGraph, (void*)4);
    think_graph_add_vertex(pGraph, (void*)5);
    think_graph_add_vertex(pGraph, (void*)6);

    think_graph_add_edge(pGraph, (void*)1, (void*)1, 4);
    think_graph_add_edge(pGraph, (void*)1, (void*)2, 4);
    think_graph_add_edge(pGraph, (void*)1, (void*)3, 2);

    think_graph_add_edge(pGraph, (void*)2, (void*)3, 5);
    think_graph_add_edge(pGraph, (void*)2, (void*)4, 10);

    think_graph_add_edge(pGraph, (void*)3, (void*)5, 3);

    think_graph_add_edge(pGraph, (void*)4, (void*)6, 11);

    think_graph_add_edge(pGraph, (void*)5, (void*)4, 4);


    log_debug("Vertex size: %d", think_graph_vertex_size(pGraph));
    log_debug("Edge size: %d", think_graph_edge_size(pGraph));

    think_graph_print(pGraph, to_string);

    think_graph_free(&pGraph, NULL);
}

void test2()
{
    ThinkGraph* pGraph = think_graph_new();

    think_graph_add_vertex(pGraph, (void*)1);
    think_graph_add_vertex(pGraph, (void*)2);
    think_graph_add_vertex(pGraph, (void*)3);
    think_graph_add_vertex(pGraph, (void*)4);
    think_graph_add_vertex(pGraph, (void*)5);
    think_graph_add_vertex(pGraph, (void*)6);

    think_graph_add_edge(pGraph, (void*)1, (void*)1, 4);
    think_graph_add_edge(pGraph, (void*)1, (void*)2, 4);
    think_graph_add_edge(pGraph, (void*)1, (void*)3, 2);

    think_graph_add_edge(pGraph, (void*)2, (void*)3, 5);
    think_graph_add_edge(pGraph, (void*)2, (void*)4, 10);

    think_graph_add_edge(pGraph, (void*)3, (void*)5, 3);

    think_graph_add_edge(pGraph, (void*)4, (void*)6, 11);

    think_graph_add_edge(pGraph, (void*)5, (void*)4, 4);

    think_graph_remove_vertex(pGraph, (void*)1, NULL);

    log_debug("Vertex size: %d", think_graph_vertex_size(pGraph));
    log_debug("Edge size: %d", think_graph_edge_size(pGraph));

    think_graph_print(pGraph, to_string);

    think_graph_free(&pGraph, NULL);
}

void test3()
{
    ThinkGraph* pGraph = think_graph_new();

    think_graph_add_vertex(pGraph, (void*)1);
    think_graph_add_vertex(pGraph, (void*)2);
    think_graph_add_vertex(pGraph, (void*)3);
    think_graph_add_vertex(pGraph, (void*)4);
    think_graph_add_vertex(pGraph, (void*)5);
    think_graph_add_vertex(pGraph, (void*)6);

    think_graph_add_edge(pGraph, (void*)1, (void*)2, 4);
    think_graph_add_edge(pGraph, (void*)1, (void*)3, 2);

    think_graph_add_edge(pGraph, (void*)2, (void*)3, 5);
    think_graph_add_edge(pGraph, (void*)2, (void*)4, 10);

    think_graph_add_edge(pGraph, (void*)3, (void*)5, 3);

    think_graph_add_edge(pGraph, (void*)4, (void*)6, 11);

    think_graph_add_edge(pGraph, (void*)5, (void*)4, 4);

    log_debug("1--2: %d", think_graph_get_edge_length(pGraph, (void*)1, (void*)2));
    think_graph_remove_edge(pGraph, (void*)1, (void*)2);

    log_debug("Vertex size: %d", think_graph_vertex_size(pGraph));
    log_debug("Edge size: %d", think_graph_edge_size(pGraph));

    think_graph_print(pGraph, to_string);

    think_graph_free(&pGraph, NULL);
}

void test4()
{
    ThinkGraph* pGraph = think_graph_new();

    think_graph_add_vertex(pGraph, (void*)1);
    think_graph_add_vertex(pGraph, (void*)2);
    think_graph_add_vertex(pGraph, (void*)3);
    think_graph_add_vertex(pGraph, (void*)4);
    think_graph_add_vertex(pGraph, (void*)5);
    think_graph_add_vertex(pGraph, (void*)6);

    think_graph_add_edge(pGraph, (void*)1, (void*)2, 4);
    think_graph_add_edge(pGraph, (void*)1, (void*)2, 5);
    think_graph_add_edge(pGraph, (void*)1, (void*)3, 2);

    think_graph_add_edge(pGraph, (void*)2, (void*)3, 5);
    think_graph_add_edge(pGraph, (void*)2, (void*)4, 10);

    think_graph_add_edge(pGraph, (void*)3, (void*)5, 3);

    think_graph_add_edge(pGraph, (void*)4, (void*)6, 11);

    think_graph_add_edge(pGraph, (void*)5, (void*)4, 4);
    think_graph_add_edge(pGraph, (void*)5, (void*)6, 11);

    log_debug("Vertex size: %d", think_graph_vertex_size(pGraph));
    log_debug("Edge size: %d", think_graph_edge_size(pGraph));

//    think_graph_print(pGraph, to_string);
    char* pszGraph = think_graph_print_to_string(pGraph, to_string);
    if (pszGraph) {
        log_debug(pszGraph);

        free(pszGraph);
        pszGraph = NULL;
    }

    void* pSrc = (void*)1;
    void* pDest = (void*)6;

    ThinkShortestPath* pPath = think_graph_shortest_path(pGraph, pSrc, pDest);
    ThinkStringBuilder* pSB = think_stringbuilder_create();

    think_stringbuilder_appendf(pSB, "Shortest path from %d to %d is %d. And path is: ", (int) pSrc, (int) pDest, pPath->m_nDistance);
    ThinkShortestPathNode* pNode = pPath->m_pNodes;
    while (pNode) {
        think_stringbuilder_appendf(pSB, " %d --> ", (int) pNode->m_pData);
        pNode = pNode->m_pNext;
    }
    think_stringbuilder_append(pSB, " NULL ");

    char* pszStr = think_stringbuilder_strdup(pSB);
    think_stringbuilder_free(pSB);

    log_debug("%s", pszStr);
    free(pszStr);
    pszStr = NULL;

    think_graph_shortest_path_free(&pPath);
    think_graph_free(&pGraph, NULL);
}

int main(int argc, char** argv)
{

    test4();

    return 0;
}
