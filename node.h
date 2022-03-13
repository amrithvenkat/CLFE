#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include "base.h"

class Node:public Base
{
    public:
        //Constructor and destructor
        Node(int nNo=0,double x=0.,double y=0.);
        ~Node();

        //Attributes
        // Node number
        int m_nNo;

        // Node coordinates
        double m_dx[2];

        //Methods/functions
        // List method on node
        void List();


};

#endif // NODE_H_INCLUDED
