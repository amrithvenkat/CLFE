#ifndef PROFILE_H_INCLUDED
#define PROFILE_H_INCLUDED

#include "base.h"

class Node;
class Element;


class Profile:public Base
{
    public:
        // Constructor and destructors
        Profile(const char* pName);
        ~Profile();

        // Attributes
        char m_pName[256]; //profile name

        //section values

        double  m_dA;       // Area
        double  m_dS[2];    // Static moment
        double  m_de[2];    // coordinates for center of mass
        double  m_dIu[3];   // moment of inertia - user coordinates
        double  m_dIc[3];   // moment of inertia - center of mass
        double  m_dIm[2];       // ... in main coordinates
        double  m_dAlpha;       // rotation angle

        Node** m_pNC;
        int m_nNC;

        Element** m_pEC;
        int m_nEC;


        // Member functions/methods
        int AddNodeContainer(int nLength);

        int AddElementContainer(int nLength);

        int AddNode(Node* pN);

        int AddElement(Element* pE);

        int CheckNode(Node* pN);

        int CheckElement(Element* pE);

        int DeleteNodes();

        int DeleteElements();

        void List();

        // Fuctions to calculate values

        void ResetSectValues();

        int CalcSectValues();
        
        void ListSectValues();

        double MTrans();


};

#endif //PROFILE_H_INCLUDED