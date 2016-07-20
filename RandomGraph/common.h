#pragma once


typedef struct tagProps
{
    int         nModel;               // 1 - Erdos/Renyai
    int         cntNodes;             // used in all models
    int         nodesToAdd;           // used in Barabasi / Albert only
    int         degree;               // used in Watts / Strogatz only
    float       edgeProb;             // used in Erdos/Renyai model only
    float       beta;                 // used in Watts / Strogatz only
} modelProps, * pModelProps;