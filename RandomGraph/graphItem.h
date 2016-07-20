#pragma once

#include <QGraphicsItem>

class CGraphItem
{
public:
    CGraphItem() { }

    virtual QGraphicsItem*  getItem() = 0;

private:

};