#ifndef ELEMENT_H_INCLUDED
#define RLEMENT_H_INCLUDED

#include "base.h"

class Node;

class Element:public Base
{
    public:
        // Constructor and Destructors
        Element(int nNo,Node** pN, int nNX);
        
        //Construtor for line elements
        Element(int nNo,Node* pN1, Node* pN2, Node* pN3, Node* pN4,int oE);
        
        // Constructor for circular elements
        Element(int nNo,Node* pN1,Node* pN2,Node* pN3,Node* pN4,Node* pN5);
       
        ~Element();

        // Attributes
        int m_nNo;        // Element number
        Node** m_pN;      // Node pointer
        int m_nN;        // Number of node instances
        int m_oE;       //orientation of the rectangle element

        // results Attributes
        double m_dL[2];    // lengths  
        double m_dA;    // area
        double m_dS[2]; // static moments
        double m_dI[3]; // moment of inertia
        double m_dD[2]; // diameters of tube

        // Functions/methods
        void List();
        void InitResults();
        int SetData();
        int SetData(int);


};

#endif // ELEMENT_H_INCLUDED
