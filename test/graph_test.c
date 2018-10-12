
#include <stdio.h>
#include <stdlib.h>

#include "ThinkGraph.h"

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


    think_graph_add_edge(pGraph, (void*)1, (void*)2, 4);
    think_graph_add_edge(pGraph, (void*)1, (void*)3, 2);

    think_graph_add_edge(pGraph, (void*)2, (void*)3, 5);
    think_graph_add_edge(pGraph, (void*)2, (void*)4, 10);

    think_graph_add_edge(pGraph, (void*)3, (void*)5, 3);

    think_graph_add_edge(pGraph, (void*)4, (void*)6, 11);

    think_graph_add_edge(pGraph, (void*)5, (void*)4, 4);

    think_graph_print(pGraph, to_string);

    think_graph_free(&pGraph, NULL);
}

int main(int argc, char** argv)
{

    test1();


    return 0;
}
