#include "node.h"

#include<stdio.h>

Node::Node(int nNo,double x,double y):Base()
{
    // Node number
    m_nNo=nNo;

    // Node coordinates
    m_dx[0]= x;
    m_dx[1]= y;

    // printing to log
    sprintf(Msg,"> node created at :  ( x = %10.3f, y = %10.3f)\n",
        m_dx[0],m_dx[1]);
    AppendLog(Msg);

}

Node::~Node()
{

    // printing to log
    sprintf(Msg,"> node deleted at : ( x = %10.3f, y = %10.3f)\n",
        m_dx[0],m_dx[1]);
    AppendLog(Msg);

}

void Node::List()
{
    // printing to log
    sprintf(Msg,"> node coordinates   ( x = %10.3f, y = %10.3f)\n",
        m_dx[0],m_dx[1]);
    AppendLog(Msg);


}