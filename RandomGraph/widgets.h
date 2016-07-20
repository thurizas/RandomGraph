/*************************************************************************************************************
*  File    : widgets.h                                                                        
*                                                                                                    
*  Abstract: THis file contains tbe declaration of the three custom widgets to gather the properties used
*            for the three random graph models.
*                                                                                                    
*  Signals :                                                                                         
*                                                                                                    
*  Slots   :                                                                                         
*                                                                                                    
*  Written : Created Jul 2016 (G.K.Huber)         
*************************************************************************************************************/
#pragma once

#include <QHBoxLayout>
#include <QPushButton>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QCheckBox>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>


class ERWidget : public QWidget
{
    Q_OBJECT

public:
    ERWidget(QWidget* parent = nullptr, const char* name = nullptr);
    ~ERWidget();

    int  getNodeCnt();
    float getEdgeProb();
    bool doClear();

signals:


private:
    QLineEdit*   m_edtNodeCnt;
    QLineEdit*   m_edtEdgeProb;
    QCheckBox*   m_cbClear;
};



class BAWidget : public QWidget
{
    Q_OBJECT

public:
    BAWidget(QWidget* parent = nullptr, const char* name = nullptr);
    ~BAWidget();

    int getNodeCnt();
    int getNodesTooAdd();
    bool doClear();

signals:


private:
    QLineEdit*   m_edtNodeCnt;
    QLineEdit*   m_edtAddtNodes;
    QCheckBox*   m_cbClear;
};



class WSWidget : public QWidget
{
    Q_OBJECT

public:
    WSWidget(QWidget* parent = nullptr, const char* name = nullptr);
    ~WSWidget();

    int getNodeCnt();
    int getDegree();
    float getBetaParm();
    bool doClear();

signals:



private:
    QLineEdit*   m_edtNodeCnt;
    QLineEdit*   m_edtDegree;
    QLineEdit*   m_edtBetaPram;
    QCheckBox*   m_cbClear;

};
