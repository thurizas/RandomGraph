#include "graph.h"
#include "utility.h"

#include <QPoint>
#include <QMessageBox>
#include <QGraphicsItem>

#include <stdint.h>

#include <deque>
#include <iostream>
#include <fstream>

/************************************************************************************************************
 * function: ctor
 *
 * abstract: Constructor for the class CGraph
 *
 * input   :  pDislay -- [in] pointer to the main display window
 *
 * returns :  
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
CGraph::CGraph(RandomGraph* pDisplay) : m_pDisplay(pDisplay), m_aMatrix(nullptr), m_dMatrix(nullptr)
{ 

}



/************************************************************************************************************
 * function: dtor for the class CGraph
 *
 * abstract: destroys any memory that we are responsible for.  Delegates all work to the clear function
 *
 * input   :  
 *
 * returns :  
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
CGraph::~CGraph()
{
    clear();
}



/************************************************************************************************************
 * function: clear
 *
 * abstract: This function clears all interal data strucures of the graph, thus allowing a single instance
 *           of this class to be used for multiple graphs.
 *
 * input   :  void 
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CGraph::clear()
{
    std::vector<CNode*>::iterator      vIter;
    std::vector<CEdge*>::iterator      eIter;

    if(m_vertices.size() > 0)
    {
        vIter = m_vertices.begin();
        while(m_vertices.end() != vIter)
        {
            delete (*vIter);
            *vIter = nullptr;

            ++vIter;
        }

        m_vertices.erase(m_vertices.begin(), m_vertices.end());
    }

    if(m_edges.size() > 0)
    {
        eIter = m_edges.begin();
        while(m_edges.end() != eIter)
        {
            delete (*eIter);
            *eIter = nullptr;

            ++eIter;
        }

        m_edges.erase(m_edges.begin(), m_edges.end());
    }

    if(nullptr != m_dMatrix)
    {
        delete [] m_dMatrix;
        m_dMatrix = nullptr;
    }


    if(nullptr != m_aMatrix)
    {
        delete [] m_aMatrix;
        m_aMatrix = nullptr;
    }

    // reset property values...       
    m_minDeg = 0;
    m_avgDeg = 0;
    m_maxDeg = 0;
}



/************************************************************************************************************
 * function: addNode
 *
 * abstract:  This function adds a node to the vertex set
 *
 * input   :  pNode -- [in] poiner to an instance of CNode to add
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CGraph::addNode(CNode* pNode)
{
    if(nullptr != pNode)
    {
        m_vertices.push_back(pNode);
    }
}
 


/************************************************************************************************************
 * function: addNode
 *
 * abstract:  This is a convience overload of the above function.  Instead of providing a pointer to an
 *            existing CNode instance, we provide the necessary information to constuct a CNode object, and
 *            add that node to the graph
 *
 * input   :  ndx -- [in] the index for the node
 *            label -- [in] an stl::string object containing the label for the node
 *            pt -- [in] a QPoint object containing a suggested location for the new node
 *
 * returns :  a pointer to the newly created node.
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
CNode* CGraph::addNode(int ndx, std::string label, QPoint pt)
{
    CNode* pTemp = new CNode(ndx, label, pt, m_pDisplay->getScene());
    m_vertices.push_back(pTemp);

    return pTemp;
}



/************************************************************************************************************
 * function: addEdge
 *
 * abstract: The main function responsible for adding an edge between to nodes.  We take pointers to the 
 *           objects representing the source and destination nodes, create an edge object to represent teh 
 *           new edge and increment the respective degree counts on both nodes.  Other addEdge functions 
 *           delagate to this function
 *
 * input   : src -- [in] pointer to the object representing the source node
 *           dst -- [in] pointer to the object representing the destination node
 *
 * returns : void
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
CEdge* CGraph::addEdge(CNode* src, CNode* dst, bool bDir, std::string label)
{
    // we have an edge between `src' and `dst', increment the degree of each
    src->incDegree();
    dst->incDegree();

    CEdge*   pNewEdge = new CEdge(src , dst, label, bDir);
    m_edges.push_back(pNewEdge);
    return pNewEdge;
}
    


/************************************************************************************************************
 * function: addEdge
 *
 * abstract: This is a convience function, if we know the ID of the source and destination nodes, but do not 
 *           have pointers to them.  We find the nodes, and get pointers to the node objects and then 
 *           delagate the insertion process to the above function.
 *
 * input   : src -- [in] index of the source node
 *           dst -- [in] index of the destination node
 *
 * returns : void.  
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
CEdge* CGraph::addEdge(int src, int dst, bool bDir, std::string label)
{
    CNode*  pSrc = nullptr;
    CNode*  pDst = nullptr;

    if(nullptr != (pSrc = findVertexByNdx(src)))          // check to see if src is a valid node ID...
    {
        if(nullptr != (pDst = findVertexByNdx(dst)))      // check to see if dst is a valid node ID...
        {
            CEdge* pNewEdge =  addEdge(pSrc,pDst, bDir, label);
            return pNewEdge;
        }
    }

    return nullptr;
}



/************************************************************************************************************
 * function: printGraph
 *
 * abstract: an helper function, we dump the contents of the vertex and edge sets to stdout
 *
 * input   : void 
 *
 * returns : void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CGraph::printGraph()
{
    std::vector<CNode*>::iterator      vIter;
    std::vector<CEdge*>::iterator      eIter;

    if(m_vertices.size() > 0)
    {
        vIter = m_vertices.begin();
        while(m_vertices.end() != vIter)
        {
            (*vIter)->printNode();
            ++vIter;
        }
    }

    if(m_edges.size() > 0)
    {
        eIter = m_edges.begin();
        while(m_edges.end() != eIter)
        {
            (*eIter)->printEdge();
            ++eIter;
        }
    }
}



/************************************************************************************************************
 * function: redrawGraph
 *
 * abstract:  This function causes the graph to redraw itself on the scene.  This function is used to redraw
 *            if the structure of the graph has changed
 *
 * input   :  pscene -- [in] poiter to the QGraphicsScene that the graph is embedded into.
 *
 * returns :  
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CGraph::redrawGraph(QGraphicsScene* pscene)
{
    std::vector<CNode*>::iterator      vIter;
    std::vector<CEdge*>::iterator      eIter;

    if(m_vertices.size() > 0)
    {
        vIter = m_vertices.begin();
        while(m_vertices.end() != vIter)
        {
            (*vIter)->addToScene(m_pDisplay);
            ++vIter;
        }
    }

    if(m_edges.size() > 0)
    {
        eIter = m_edges.begin();
        while(m_edges.end() != eIter)
        {
            (*eIter)->addToScene(pscene);
            ++eIter;
        }
    }
}



/************************************************************************************************************
 * function: calcDegrees
 *
 * abstract:  This function calculates the minimum, average and maximum degree of the graph.
 *
 * input   :  void
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CGraph::calcDegrees()
{
    std::vector<CNode*>::iterator       vIter;

    if(m_vertices.size() > 0)
    {
        vIter = m_vertices.begin();
        m_minDeg = m_avgDeg = m_maxDeg = (*vIter)->getDegree();   // initialize to values of first node....
        if(m_vertices.size() > 1)                                 // more then a single node in the graph...
        {
            ++vIter;                                          
            while(m_vertices.end() != vIter)
            {
                int curDeg = (*vIter)->getDegree();

                if(curDeg < m_minDeg)  m_minDeg = curDeg;         // adjust minimum degree, if needed
                if(curDeg > m_maxDeg)  m_maxDeg = curDeg;         // adjust maximum degree, if needed
                m_avgDeg += curDeg;

                ++vIter;
            }
            m_avgDeg = ((float)m_avgDeg)/m_vertices.size();
        }
    }   
}



/************************************************************************************************************
 * function: calcDistances
 *
 * abstract:  This function calculates the shortest distance from a node to every other node.  We do this 
 *            via a breath-first search.  To do all-paths we just use every node in the graph, in turn, as 
 *            the starting node for the search.
 *            This function also ensures that an auxillary data structure, is created.  This data structure
 *            is a `distance matrix' when the element d_{ij} is the shortest distance between vertices i and 
 *            j.
 *            This function also builds the adjanency matrix, A, where the element a_{ij} is one if there is 
 *            and edge between verticies i and j, otherwise it is zero.  The adjancey matrix is used in the 
 *            BFS algorithm.
 *
 * input   :  void
 *
 * returns :  void
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CGraph::calcDistances()
{
    int   nodeCnt = m_vertices.size();
    
    // build the distance matrix
    if(nullptr == m_dMatrix)
    {    
        m_dMatrix = new char[nodeCnt*nodeCnt];
        memset((void*)m_dMatrix, 0, nodeCnt*nodeCnt);        
    }

    if(nullptr == m_aMatrix)
    {
        buildAdjacencyMatrix();
    }
    
    // iterate over all nodes in teh graph
    std::vector<CNode*>::iterator   vIter;
    vIter = m_vertices.begin();
    while(m_vertices.end() != vIter)
    {
        // initialize BFS related member variables...
        for(int vdx = 0; vdx < nodeCnt; vdx++)
        {
            m_vertices.at(vdx)->setDistance(-1);
            m_vertices.at(vdx)->setParent(-1);
        }

        int nodeID = (*vIter)->getIndex();                    // run BFS starting from that node
        doBFS(nodeID);

        // retreive results from graph and write into distance matrix
        for(int vdx = 0; vdx < nodeCnt; vdx++)
        {
            int distance = m_vertices.at(vdx)->getDistance();
            m_dMatrix[nodeID * nodeCnt + vdx] = distance;
        }

        ++vIter;
    }
}



/************************************************************************************************************
 * function: getDegreeSequence
 *
 * abstract:  This funciton builds, and returns a vector containing the degrees of each vertex in the graph.
 *            This function does not sort the vector (so it really isn't a degree sequence per se).
 *
 * input   :  void 
 *
 * returns : a standard vector containing the degrees of all nodes in teh graph 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
std::vector<int> CGraph::getDegreeSequence()
{
    std::vector<int>                 degSeq;
    std::vector<CNode*>::iterator    vIter;

    vIter = m_vertices.begin();
    while(m_vertices.end() != vIter)
    {
        degSeq.push_back((*vIter)->getDegree());
        ++vIter;
    }

    return degSeq;
}



/************************************************************************************************************
 * function: getAdjacencyMatrix
 *
 * abstract: returns the adjacency matrix for the current graph.  If one doesn't exist, we construct it first.
 *
 * input   :  void
 *
 * returns :  the adjacency matrix as a 2D-array of char's
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
const char* CGraph::getAdjacencyMatrix()
{
    if(nullptr == m_aMatrix)
        buildAdjacencyMatrix();

    return m_aMatrix;
}



/************************************************************************************************************
 * function: getDistanceMatrix
 *
 * abstract: returns the distance matrix for the current graph.  If one doesn't exist, we construct it first.
 *
 * input   :  void
 *
 * returns :  the distance matrix as a 2D-array of char's
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
const char* CGraph::getDistanceMatrix()
{
    if(nullptr == m_dMatrix)
        calcDistances();

    return m_dMatrix;
}



/************************************************************************************************************
 * function: readFile
 *
 * abstract:  This function reads a graph file, extracting the node and edge information and creaing a
 *            new graph structure and rendering it on the display surfact.  The file format is a binary
 *            format, with the following structure:
 *
 *                                    data type(size)
 *            header ...
 *               ... magic             char[]   (4 bytes)   (contains the value GRPH)
 *               ... version           uchar    (1 byte )   
 *               ... encoding          uchar    (1 byte )   (0 = LSB, little-endian, 1 = MSB, big endian)
 *               ... dataSize          uchar    (1 byte )   (0 = 32-bit data/ 1 = 64-bit data)
 *	             ... model             uchar    (1 byte)    (
 *               ... node offset       uint     (4 bytes)   (offset in file where node data starts
 *               ... node entry count  uint     (4 bytes)   (number of node entries
 *               ... node entry size   uint     (4 bytes)   (size of a node entry, should be 16 bytes)
 *               ... edge entry offset uint     (4 bytes)   (offst in file where edge data starts)
 *               ... edge enty count   uint     (4 bytes)   (number of edge entries)
 *               ... edge entry size   uint     (4 bytes)   (size of an edge entry, should be 16 bytes)
 *               ... strtbl offset     uint     (4 bytes)   (offset in file where string table starts)
 *               ... strtbl lengh      uint     (4 bytes)   (length, in bytes, of the string table)
 *           node set ...
 *               ... node_ndx          uint     (4 bytes)   (index into string table to get label
 *               ... node id           uint     (4 bytes)   (integer
 *               ... node_x            uint     (4 bytes)   (suggested x coordinate)
 *               ... node_y            uint     (4 bytes)   (suggested y coordinate)
 *           edge set ...
 *               ... edge_ndx          uint     (4 bytes)   (edge identifier)
 *               ... node_id_src       uint     (4 bytes)   (source node ID for edge)
 *               ... node_id_dst       uint     (4 bytes)   (destination node ID for edge)
 *               ... edge_is_directed  uint     (4 bytes)   (flag or directed edge or not)
 *           strtable ...
 *
 *           data types:
 *               char -- normal (signed) byte value
 *               uchar -- unsigned char
 *               uint -- unsigned 32-bi value
 *
 * input   : file -- [in] name of file to read 
 *
 * returns : void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
bool CGraph::readFile(QString file)
{
    QGraphicsScene*     pScene = m_pDisplay->getScene();
    bool                bRet = false;

    std::ifstream       fb;
    fb.open(file.toStdString().c_str(), std::ios::in | std::ios::binary);
    if(fb.is_open())
    {
        fileHeader        hdr;

        // read in header...
        fb.read((char*)&hdr, sizeof(hdr));

        if(0 == memcmp((void*)hdr.hdr_magic, (void*)"GRPH", 4))             // check the magic number, do we have a graph file...
        {
            if(CUR_VERSION == hdr.hdr_version)                              // check to see if we are using a current version...
            {
                char*     lpszStrTbl = new char[hdr.strtbl_len];

                // read in string table...
                fb.seekg(hdr.strtbl_offset, std::ios_base::beg);
                fb.read((char*)lpszStrTbl, hdr.strtbl_len);

                // jump back to the start of the node section and read in nodes.
                fb.clear();                                                 // clear error state incase last read hit EOF
                fb.seekg(hdr.node_offset, std::ios_base::beg);

                // read in nodes, and build them
                int nodeCnt = hdr.node_entry_count;
                for(int ndx = 0; ndx < nodeCnt; ndx++)
                {
                    nodeEntry    temp;
                    fb.read((char*)&temp, sizeof(nodeEntry));

                    int nodeID = temp.node_id;
                    QPoint   pt(temp.node_x, temp.node_y);

                    QString qstrLabel(&lpszStrTbl[temp.node_ndx]);

                    CNode*     pNode = new CNode(nodeID, qstrLabel.toStdString(), pt, pScene);
                    addNode(pNode);
                    pNode->addToScene(m_pDisplay);
                }

                fb.seekg(hdr.edge_offset, std::ios_base::beg);
                // read in edges, and build them
                int edgeCnt = hdr.edge_entry_count;
                for(int ndx = 0; ndx < edgeCnt; ndx++)
                {
                    edgeEntry   temp;
                    fb.read((char*)&temp, sizeof(edgeEntry));

                    int  src = temp.edge_src_ndx;
                    int  dst = temp.edge_dst_ndx;
                    int  dir = temp.edge_isDirected;
                    std::string strLabel;
                    strLabel = lpszStrTbl[temp.edge_ndx];

                    CEdge* pEdge = this->addEdge(src, dst, dir, strLabel);
                    pEdge->addToScene(m_pDisplay->getScene());
                }

                delete [] lpszStrTbl;
            }
            else
            {
                QMessageBox::critical(nullptr, "error", QString("%1 is an incorrect version").arg(file));
            }
        }
        else
        {
            QMessageBox::critical(nullptr, "error", QString("%1 is not a graph file").arg(file));
        }
        fb.close();

        bRet = true;
    }
    else
    {
        QMessageBox::critical(nullptr, "error", QString("Unable to open %1 for reading").arg(file));
    }
    
    return bRet;
}



/************************************************************************************************************
 * function: writeFile
 *
 * abstract: This function serializes the graph information to a file.  We use a pure binary format to help
 *           conserve disk space  The format of the output file is described in the function readFile
 *
 * input   :  file -- [in] a QString object with the file name to write to
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
bool CGraph::writeFile(QString file)
{
    unsigned int                      strtblSize = 0;
    unsigned int                      curLocation = 0;
    char*                             lpszStrTbl;
    std::vector<CNode*>::iterator     vIter;
    std::vector<CEdge*>::iterator     eIter;
    bool                              bRet = false;

    std::ofstream   fb;
    fb.open(file.toStdString().c_str(), std::ios::out | std::ios::binary);

    if(fb.is_open())
    {
        // calculate where blocks start...
        uint32_t nodeOffset = sizeof(fileHeader);
        uint32_t edgeOffset = sizeof(fileHeader) + m_vertices.size() * sizeof(nodeEntry);
        uint32_t strOffset = sizeof(fileHeader) + m_vertices.size() * sizeof(nodeEntry) + m_edges.size() * sizeof(edgeEntry);

        // calculate the size of the string table.....
        vIter = m_vertices.begin();
        while(m_vertices.end() != vIter)
        {
            strtblSize += (*vIter)->getLabel().length();
            ++vIter;
        }

        eIter = m_edges.begin();
        while(m_edges.end() != eIter)
        {
            strtblSize += (*eIter)->getLabel().length();
            ++eIter;
        }
        strtblSize = strtblSize + m_vertices.size() + m_edges.size() + 1;     // adding space for null terminators 

        // allocate space for string table and initialize...
        lpszStrTbl = new char[strtblSize];
        memset(lpszStrTbl, '\0', strtblSize);
        
        // construct and write header...
        fileHeader     hdr;
        memset((void*)&hdr, 0, sizeof(hdr));

        strncpy(hdr.hdr_magic, "GRPH", 4);         
        hdr.hdr_version = 1;          
        hdr.hdr_encoding = 0;         
        hdr.hdr_size = sizeof(fileHeader);             
        hdr.hdr_model = getModelCode();             
        hdr.node_offset = nodeOffset;
        hdr.node_entry_count = m_vertices.size();
        hdr.node_entry_size = sizeof(nodeEntry);
        hdr.edge_offset = edgeOffset;
        hdr.edge_entry_count = m_edges.size();
        hdr.edge_entry_size = sizeof(edgeEntry);
        hdr.strtbl_offset = strOffset;
        hdr.strtbl_len=strtblSize;

        fb.write((char*)&hdr, sizeof(hdr));
        
        // write out node infomation....
        vIter = m_vertices.begin();
        while(m_vertices.end() != vIter)
        {
            nodeEntry     temp;
            memset((void*)&temp, 0, sizeof(nodeEntry));

            temp.node_ndx = curLocation;
            temp.node_id = (*vIter)->getIndex();
            temp.node_x = (*vIter)->getTempLoc().x();
            temp.node_y = (*vIter)->getTempLoc().y();
            fb.write((char*)&temp, sizeof(nodeEntry));                        // write node info to file 

            std::string label = (*vIter)->getLabel();
            int len = label.length();

            memcpy(&lpszStrTbl[curLocation], label.c_str(), len);
            curLocation = curLocation + len + 1;                            // skip one character for the null terminator

            vIter++;
        }

        // write out edge information....
        eIter = m_edges.begin();
        while(m_edges.end() != eIter)
        {
            edgeEntry    temp;
            memset((void*)&temp, 0, sizeof(edgeEntry));

            temp.edge_ndx = curLocation;
            temp.edge_src_ndx = (*eIter)->getSrc()->getIndex();
            temp.edge_dst_ndx = (*eIter)->getDst()->getIndex();
            temp.edge_isDirected = (*eIter)->getDirected();
            fb.write((char*)&temp, sizeof(edgeEntry));


            std::string label = (*eIter)->getLabel();
            int len = label.length();

            memcpy(&lpszStrTbl[curLocation], label.c_str(), len);
            curLocation = curLocation + len + 1;                            // skip one character for the null terminator
            
            eIter++;
        }

        // write out string table...
        fb.write(lpszStrTbl, curLocation);

        // ...and done
        fb.close();

        bRet = true;
        delete [] lpszStrTbl;
    }
    else
    {
        QMessageBox::critical(nullptr, "error", QString("Unable to open %1 for writting").arg(file));
    }

    return bRet;
}



/************************************************************************************************************
 * function: doKruskal
 *
 * abstract: This function builds a spanning tree.  We use Kruskal's algorithm to build the tree.  Because
 *           we are working with unweighed graphs, we use a permutation of the edge set, picking edges 
 *           at random.  We accept edges as long as the do not induce a cycle or a loop.
 *
 * input   : pScene -- [in] a pointer to a QGrahicsScene that the accepted edges will be added to. 
 *
 * returns : void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CGraph::doKruskal(QGraphicsScene* pScene)
{
    std::vector<std::pair<int, int>>      edgeSet;
    unsigned int                          foundEdges = 0;
    // generate the edges in a complete graph...                                      
    for(unsigned int src = 0; src <= m_vertices.size()-2; src++)                   
    {
        for(unsigned int dst = src + 1; dst <= m_vertices.size()-1; dst++) 
        {
            edgeSet.push_back(std::pair<int,int>(src, dst));
        }
    }

    // generate a permutation of the edges...just to mix things up...
    std::next_permutation(edgeSet.begin(), edgeSet.end(), [](std::pair<int,int> lhs, std::pair<int,int> rhs)-> bool{return ((lhs.first + lhs.second) < (rhs.first + rhs.second));});

    // generate a spanning tree..
    struct subset* subsets = new struct subset[m_vertices.size()];
    for(unsigned int ndx = 0; ndx < m_vertices.size(); ndx++)
    {
        subsets[ndx].p = ndx;
        subsets[ndx].r = 0;
    }

    do
    {
        int edgeNdx = rand() % edgeSet.size();
        int src = edgeSet.at(edgeNdx).first;
        int dst = edgeSet.at(edgeNdx).second;

        int x = find(subsets, src);
        int y = find(subsets, dst);

        if(x != y)
        {
            CEdge* pEdge = addEdge(src, dst);
            pEdge->addToScene(pScene);

            setUnion(subsets, x, y);
            ++foundEdges;
        }
    } while(foundEdges < (m_vertices.size()-1));
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// private functions
/************************************************************************************************************
 * function: findVertexByNdx
 *
 * abstract:  This function finds a vertex in the vertex set by index (i.e. the identifer).  We do a linear
 *            search through the vertex set looking for the node that matches the index.
 *
 * input   :  ndx -- [in] index of the node to search for
 *
 * returns :  pointer to the node, or nullptr if no match is found 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
CNode* CGraph::findVertexByNdx(int ndx)
{
    std::vector<CNode*>::iterator   vIter;
    CNode*     pNode = nullptr;

    if(m_vertices.size() > 0)
    {
        vIter = m_vertices.begin();
        while(m_vertices.end() != vIter)
        {
            if((*vIter)->getIndex() == ndx)
            {
                pNode = (*vIter);
                break;
            }
        
            ++vIter;
        }
    }

    return pNode;
}



/************************************************************************************************************
 * function: getModelCode
 *
 * abstract:  This is a helper function that takes the model name as a string and returns the numeric code
 *            for the model
 *
 * input   :  void 
 *
 * returns :  the model code or -1 if the model could not be found
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
int CGraph::getModelCode()
{
    if(m_qstMethod == "imported")
        return 0;
    else if(m_qstMethod == "Erdos-Renyi")
        return 1;
    else if(m_qstMethod == "Barabasi-Albert")
        return 2;
    else if(m_qstMethod == "Watts-Strogatz")
        return 3;
    else
        return 0xFF;
}




/************************************************************************************************************
 * function: find
 *
 * abstract: recursive function to find the parent of a node in a given subset of nodes.  Used to cycle
 *           detecion in Kruskal's algorithm
 *
 * input   :  stuct subset subsets [] -- [in] array of subgraphs that we have build to date by using Kruskals
 *
 * returns :  int he parent node of the subgraph
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
int CGraph::find(struct subset subsets[], int ndx)
{
    if(subsets[ndx].p != ndx)
        subsets[ndx].p = find(subsets, subsets[ndx].p);

    return subsets[ndx].p;
}



/************************************************************************************************************
 * function: setUnion
 *
 * abstract: performs a union of two subgaphs (subtrees) during running of Kruskal's  
 *
 * input   :  struct subset subsets[] -- [in]array of subgraphs
 *            x -- [in] identifier of a node in a subset
 *            y -- [in] identifier of a node in a subset
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CGraph::setUnion(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot].r < subsets[yroot].r)
        subsets[xroot].p = yroot;
    else if (subsets[xroot].r > subsets[yroot].r)
        subsets[yroot].p = xroot;

    // If ranks are same, then make one as root and increment
    // its rank by one
    else
    {
        subsets[yroot].p = xroot;
        subsets[xroot].r++;
    }
}



/************************************************************************************************************
 * function: buildAdjacencyMatrix
 *
 * abstract: This function converts the edge set into an n-by-n (where n is the cardinality of the vertex set)
 *           matrix, where the a_{ij} element is a one if v_i and v_j are adjacent, zero otherwise  
 *           this datastructure is used when performing a breath-first search of the graph
 *
 * input   :  void 
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CGraph::buildAdjacencyMatrix()
{
    std::vector<CEdge*>::iterator        eIter;
    int nodeCnt = this->getOrder();

    if(nullptr == m_aMatrix)
    {
        m_aMatrix = new char[nodeCnt*nodeCnt];
        memset((void*)m_aMatrix, 0, sizeof(char)*nodeCnt*nodeCnt);
    }

    eIter = m_edges.begin();
    while(m_edges.end() != eIter)
    {
        (*eIter)->printEdge(); 
        int src = (*eIter)->getSrc()->getIndex();
        int dst = (*eIter)->getDst()->getIndex();

        m_aMatrix[src*nodeCnt + dst] = 1;

        bool   bDirected = (*eIter)->getDirected();
        if(!bDirected)                                // undirected edge, flip src and dst and add entry...
            m_aMatrix[dst*nodeCnt + src] = 1;

        ++eIter;
    }
}




/************************************************************************************************************
 * function: doBFS
 *
 * abstract: This function does a breath-first search starting at a prescribed vertex.  This function is used
 *           to calculate the distance from the distinguished vertex to all other reachable nodes.  This 
 *           function, modifies two member variables in the CNode class, it modifies the distance and the 
 *           parent variables.
 *
 * input   : void
 *
 * returns : void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CGraph::doBFS(int vStart)
{
    std::deque<int>         workingQueue;

    int nodeCnt = m_vertices.size();

    m_vertices.at(vStart)->setDistance(0);

    workingQueue.push_back(vStart);                             // enque the starting node

    while(workingQueue.size() > 0)
    {
        int current = workingQueue.front();                     // get first element in queue
        workingQueue.pop_front();

        int curDis = m_vertices.at(current)->getDistance(); 

        for(int vdx = 0; vdx < nodeCnt; vdx++)                  // scan across appropriate row in the adjacency matrix
        {
            if(1 == m_aMatrix[current*nodeCnt + vdx])           // got an edge, vdx is the node index of the neighbor
            {
                if(-1 == m_vertices.at(vdx)->getDistance())     // first time seeing this node
                {
                    m_vertices.at(vdx)->setDistance(curDis+1);  //update distance
                    m_vertices.at(vdx)->setParent(current);     // update parent

                    workingQueue.push_back(vdx);                // enqueue the node
                }
            }
        }
    }
}

