/*************************************************************************************************************
*  File    : graph.h                                                                        
*                                                                                                    
*  Abstract: This file contains the interface for the graph class.  We model the graph as a set of edges, and
*            a set of verticies.  Additionlly, as needed we build an adjacancy matrix and a distance matrix
*            for the graph.
*            Also include are the definitions of various structures useful for reading and writting binary
*            forms of a graph file.
*                                                                                                    
*  Signals :                                                                                         
*                                                                                                    
*  Slots   :                                                                                         
*                                                                                                    
*  Written : Created Jul 2016 (G.K.Huber)         
*************************************************************************************************************/
#pragma once

#include <QPoint>

#include<vector>
#include<map>

#include <stdint.h>

#include "randomgraph.h"
#include "node.h"
#include "edge.h"

#define CUR_VERSION 1

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// structs for writing and reading graph files:
// the file header structure...
typedef struct headerTag
{
    char            hdr_magic[4];        // GRPH
    unsigned char   hdr_version;         // current version is 1
    unsigned char   hdr_encoding;        // current encoding is 0 = LSB, (1 = MSB)
    unsigned char   hdr_size;            // 32-bit data = 0, 64-bit data = 1
    unsigned char   hdr_model;           // graph model, imported = 0, 
    uint32_t        node_offset;
    uint32_t        node_entry_count;
    uint32_t        node_entry_size;
    uint32_t        edge_offset;
    uint32_t        edge_entry_count;
    uint32_t        edge_entry_size;
    uint32_t        strtbl_offset;
    uint32_t        strtbl_len;
} fileHeader, *pfileHeader;

// structure representing a node record in the file...
typedef struct nodeTag
{
    uint32_t       node_ndx;              // index into the string table
    uint32_t       node_id;               // node ID
    uint32_t       node_x;                // initial x location for node
    uint32_t       node_y;                // initial y location or node
} nodeEntry, *pnodeEntry;

// structure representin an edge record in the file...
typedef struct edgeTag
{
    uint32_t       edge_ndx;              // index into the string table
    uint32_t       edge_src_ndx;          // source node ID
    uint32_t       edge_dst_ndx;          // destination node ID
    uint32_t       edge_isDirected;       // directed edge or not.
} edgeEntry, *pedgeEntry;


struct subset
{
    int    p;
    int    r;
};

class CGraph
{
public:
    CGraph(RandomGraph* pDisplay);
    ~CGraph();

    void clear();

    void   addNode(CNode*);
    CNode* addNode(int, std::string, QPoint);

    CEdge* addEdge(CNode*, CNode*, bool bDir = "false", std::string label="");
    CEdge* addEdge(int, int, bool bDir = "false", std::string label="");

    QString getMethod() {return m_qstMethod;}
    void setMethod(QString m) {m_qstMethod = m;}

    int              getOrder() {return m_vertices.size();}
    int              getSize() {return m_edges.size();}

    void             calcDegrees();
    void             calcDistances();
    int              getMinDeg() {return m_minDeg;}
    int              getMaxDeg() {return m_maxDeg;}
    int              getNodeDeg(int ndx) { return m_vertices.at(ndx)->getDegree();}
    float            getAvgDeg() {return m_avgDeg;}
    std::vector<int> getDegreeSequence();
    const char*      getAdjacencyMatrix();
    const char*      getDistanceMatrix();

    void  doKruskal(QGraphicsScene*);
    

    void printGraph();

    void redrawGraph(QGraphicsScene*);

    bool writeFile(QString);
    bool readFile(QString);

private:
    RandomGraph*                        m_pDisplay;        // back-pointer to main window.

    std::vector<CNode*>                 m_vertices;        // vertex set
    std::vector<CEdge*>                 m_edges;           // edge set

    // graph properties....
    QString                             m_qstMethod;
    int                                 m_minDeg;
    float                               m_avgDeg;
    int                                 m_maxDeg;
    char*                               m_aMatrix;         // adjacency matrix
    char*                               m_dMatrix;         // distance matrix

    CNode* findVertexByNdx(int ndx);
    int    getModelCode();
    void   buildAdjacencyMatrix();
    void   doBFS(int);
    
    // utility functions for Kruskal's algorithm
    int find   (struct subset*, int);
    void setUnion(struct subset*, int, int);
};



