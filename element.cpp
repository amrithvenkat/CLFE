#include "element.h"
#include "node.h"

#include<stdio.h>
#include<math.h>
#include<memory.h>

// Line element constructor
Element::Element(int nNo,Node* pN1, Node* pN2, Node* pN3, Node* pN4,int oE)
{
    m_nNo=nNo;
    m_nN=4;
    m_oE=oE;
    // m_dt=dt;

    // Memory allocation for node points
    m_pN = new Node*[m_nN];

    // Copy to node pointers
    m_pN[0]=pN1; // RL
    m_pN[1]=pN2; // RU
    m_pN[2]=pN3; // LL
    m_pN[3]=pN4; // LU

    InitResults();
    sprintf(Msg,"element %d created type : rectangle .\n",m_nNo);
    AppendLog(Msg);
}

// Circle element constructor
Element::Element(int nNo,Node* pN1,Node* pN2,Node* pN3,Node* pN4,Node* pN5)
{
    m_nNo=nNo;
    m_nN=5;
    // m_dt=dt;

    // Memory allocation for node points
    m_pN = new Node*[m_nN];

    // Copy to node pointers
    m_pN[0]=pN1; // center node    
    m_pN[1]=pN2; // outer node 1  
    m_pN[2]=pN3; // outer node 2  
    m_pN[3]=pN4; // inner node 1  
    m_pN[4]=pN5; // inner node 2  

    InitResults();

    sprintf(Msg,"element %d created type : circular tube .\n",m_nNo);
    AppendLog(Msg);
}


Element::~Element()
{
    sprintf(Msg,"element %d deleted",m_nNo);
    AppendLog(Msg);
}

void Element::InitResults()
{
    // m_dL=0.;
    m_dA=0.;
    // m_dt=0.;

    memset((void*)m_dL,0,sizeof(double)*2);
    memset((void*)m_dS,0,sizeof(double)*2);
    memset((void*)m_dI,0,sizeof(double)*3);
    memset((void*)m_dD,0,sizeof(double)*2);


}


int Element::SetData()
{
    // int s;
    // s=a;
    // if(a==2)
    // {
    double m_dhc[2],m_dvc[2]; // Center coordinate of horizontal line and vertical line in the rectangle
    for(int i=0;i<2;i++)
        {
        m_dhc[i]=(m_pN[0]->m_dx[i] + m_pN[2]->m_dx[i])/2.; // m_dhc[0] - x    m_dhc[1] - y // horizontal take x from this.
        m_dvc[i]=(m_pN[0]->m_dx[i] + m_pN[1]->m_dx[i])/2.; // m_dvc[0] - x    m_dvc[1] - y // vertical   take y from this.
        }
    
    
    double m_dLp[2]; // Length of element
    for(int i=0;i<2;i++)
        {
        m_dLp[i]= m_pN[1]->m_dx[i] - m_pN[0]->m_dx[i];

        }
    // Actual length of the element
    
    if(m_oE==1) // vertical element
    {
    m_dL[0] = sqrt(pow(m_pN[0]->m_dx[0]-m_pN[1]->m_dx[0],2)
               +pow(m_pN[0]->m_dx[1]-m_pN[1]->m_dx[1],2));  // length

    m_dL[1] = sqrt(pow(m_pN[0]->m_dx[0]-m_pN[2]->m_dx[0],2)
               +pow(m_pN[0]->m_dx[1]-m_pN[2]->m_dx[1],2));  // thickness

    m_dA = m_dL[0]*m_dL[1]; //area calculation

    m_dI[0]=(pow(m_dL[0],2))*m_dA;
    m_dI[1]=(pow(m_dL[1],2))*m_dA;

    
    }

    else if(m_oE==0)  // horizontal element
    {
    m_dL[0] = sqrt(pow(m_pN[0]->m_dx[0]-m_pN[2]->m_dx[0],2)
               +pow(m_pN[0]->m_dx[1]-m_pN[2]->m_dx[1],2));  // length

    m_dL[1] = sqrt(pow(m_pN[0]->m_dx[0]-m_pN[1]->m_dx[0],2)
               +pow(m_pN[0]->m_dx[1]-m_pN[1]->m_dx[1],2));  // thickness

    m_dA = m_dL[0]*m_dL[1]; //area calculation

    m_dI[0]=(pow(m_dL[1],2))*m_dA;
    m_dI[1]=(pow(m_dL[0],2))*m_dA;

    }

    // static moment
    m_dS[0]=m_dvc[1]*m_dA;
    m_dS[1]=m_dhc[0]*m_dA;


    // Ixy
    m_dI[2] = (m_dLp[0]*m_dLp[1]/12. + m_dhc[0]*m_dvc[1])*m_dA;



    // }

    // else if(a==5)
    // {
    // double m_dxc[2]; // center coordinates of tube 
    // m_dxc[0]=m_pN[0]->m_dx[0];
    // m_dxc[1]=m_pN[0]->m_dx[1];

    // //area of tube
    // // double m_diam[2]; // diameter lengths
    // m_dD[0]= sqrt(pow(m_pN[1]->m_dx[0]-m_pN[3]->m_dx[0],2)
    //            +pow(m_pN[1]->m_dx[1]-m_pN[3]->m_dx[1],2)); // outer diameter

    // m_dD[1]= sqrt(pow(m_pN[2]->m_dx[0]-m_pN[4]->m_dx[0],2)
    //            +pow(m_pN[2]->m_dx[1]-m_pN[4]->m_dx[1],2)); // inner diameter
    
    // m_dA = 3.14159*(pow(m_dD[0],2)-pow(m_dD[1],2))/4.; // area of tube

    // // static moment x , static moment y
    // for (int i=0;i<2;i++)
    //     m_dS[i] = m_dxc[(i+1)%2]*m_dA;  // using the center coordinate
    
    // // moment of inertia
    // // Ixx/Iyy
    // m_dI[0] = 3.14159*(pow(m_dD[0],4)-pow(m_dD[1],4))/64.;
    // m_dI[1] = m_dI[0];

    // // Ixy
    // //m_dI[2] = (m_dLp[0]*m_dLp[1]/12. + m_dxc[0]*m_dxc[1]*m_dA);
    // m_dI[2]=0;
    // }

    return 0;
}

int Element::SetData(int) //for the tube element
{
    double m_dxc[2]; // center coordinates of tube 
    m_dxc[0]=m_pN[0]->m_dx[0];
    m_dxc[1]=m_pN[0]->m_dx[1];

    //area of tube
    // double m_diam[2]; // diameter lengths
    m_dD[0]= sqrt(pow(m_pN[1]->m_dx[0]-m_pN[2]->m_dx[0],2)
               +pow(m_pN[1]->m_dx[1]-m_pN[2]->m_dx[1],2)); // outer diameter

    m_dD[1]= sqrt(pow(m_pN[3]->m_dx[0]-m_pN[4]->m_dx[0],2)
               +pow(m_pN[3]->m_dx[1]-m_pN[4]->m_dx[1],2)); // inner diameter

    m_dL[0]=0.;
    m_dL[1]=abs((m_dD[0]-m_dD[1]))/2.;
    
    m_dA = 3.14159*(pow(m_dD[0],2)-pow(m_dD[1],2))/4.; // area of tube

    // static moment x , static moment y
    for (int i=0;i<2;i++)
        m_dS[i] = m_dxc[(i+1)%2]*m_dA;  // using the center coordinate
    
    // moment of inertia
    // Ixx/Iyy
    m_dI[0] = 3.14159*(pow(m_dD[0],4)-pow(m_dD[1],4))/64.;
    m_dI[1] = m_dI[0];

    // Ixy
    //m_dI[2] = (m_dLp[0]*m_dLp[1]/12. + m_dxc[0]*m_dxc[1]*m_dA);
    m_dI[2]=0;

    return 0;
}


void Element::List()
{
    sprintf(Msg,"element %2d, t = %10.2f, %d nodes\n",m_nNo,m_dL[1],m_nN);
    AppendLog(Msg);

    // print the nodes data
    for (int i=0;i<m_nN;i++)
    {
        m_pN[i]->List();
    }

    if(m_nN==4) //for line elements print the length
    {
    sprintf(Msg,"  Length...................: %12.3e mm\n",m_dL[0]);
    AppendLog(Msg);
    }

    if(m_nN==5) // for circular elements
    {
    sprintf(Msg,"  Inner diameter...........: %12.3e mm\n",m_dD[1]);
    AppendLog(Msg);
    sprintf(Msg,"  Outer diameter...........: %12.3e mm\n",m_dD[0]);
    AppendLog(Msg);
    }

    // list of the element result values
    
    sprintf(Msg,"  Area.....................: %12.3e mm^2\n",m_dA);
    AppendLog(Msg);
    sprintf(Msg,"  Static moment x..........: %12.3e mm^3\n",m_dS[0]);
    AppendLog(Msg);
    sprintf(Msg,"  Static moment y..........: %12.3e mm^3\n",m_dS[1]);
    AppendLog(Msg);
    sprintf(Msg,"  Ixx......................: %12.3e mm^4\n",m_dI[0]);
    AppendLog(Msg);
    sprintf(Msg,"  Iyy......................: %12.3e mm^4\n",m_dI[1]);
    AppendLog(Msg);
    sprintf(Msg,"  Ixy......................: %12.3e mm^4\n",m_dI[2]);
    AppendLog(Msg);

}