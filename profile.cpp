#include "profile.h"
#include "node.h"
#include "element.h"

#include<stdio.h>
#include<math.h>
#include<string.h>

Profile::Profile(const char* pName):Base()
{
    strcpy(m_pName,pName);

    m_pNC=0;
    m_nNC=0;

    m_pEC=0;
    m_nEC=0;

    ResetSectValues();

}


Profile::~Profile()
{
    // if node and element exists then delete
    if (m_pNC) delete [] m_pNC;
    if (m_pEC) delete [] m_pEC;

}

void Profile::ResetSectValues()
{
    m_dA=0.;
    memset((void*)m_dS,0,sizeof(double)*2);
    memset((void*)m_de,0,sizeof(double)*2);
    memset((void*)m_dIu,0,sizeof(double)*3);
    memset((void*)m_dIc,0,sizeof(double)*3);
    memset((void*)m_dIm,0,sizeof(double)*2);
  
}


void Profile::List()
{
    sprintf(Msg,"Profile '%s' (node space: %d, element space: %d)\n",
        m_pName,m_nNC,m_nEC);
    AppendLog(Msg);


    for(int i=0; i<m_nNC;i++)
    {
        Node* pN = m_pNC[i];
        if(pN) pN->List();
    }

    for(int i=0; i<m_nEC;i++)
    {
        Element* pE = m_pEC[i];
        if(pE) pE->List();
    }

    ListSectValues();
}

int Profile::AddNodeContainer(int nLength)
{
    DeleteNodes();

    m_pNC = new Node* [nLength];

    if(!m_pNC) return 0;

    memset((void*)m_pNC,0,sizeof(Node*)*nLength);

    m_nNC = nLength;

    return nLength;

}

int Profile::AddElementContainer(int nLength)
{
    DeleteElements();

    m_pEC = new Element* [nLength];

    if(!m_pEC) return 0;

    memset((void*)m_pEC,0,sizeof(Element*)*nLength);

    m_nEC = nLength;

    return nLength;
    
}

int Profile::DeleteNodes()
{
    if(!m_pNC) return 0;

    for(int i=0;i<m_nNC;i++)
    {
        Node* pN = m_pNC[i];
        if(pN) delete pN;

    }
    delete [] m_pNC;
    m_pNC=0;
    m_nNC=0;

    return 0;
}

int Profile::DeleteElements()
{
    if(!m_pEC) return 0;

    for(int i=0;i<m_nEC;i++)
    {
        Element* pE = m_pEC[i];
        if(pE) delete pE;

    }
    delete [] m_pEC;
    m_pEC=0;
    m_nEC=0;

    return 0;
}

int Profile::AddNode(Node* pN)
{
    if(!m_pNC) return -1;
    if(!pN) return -2;

    int nRet = CheckNode(pN);
    if(nRet<0)
    {
        sprintf(Msg,"Error : Node %d invalid",pN->m_nNo);
        AppendLog(Msg);
        return -3;
    }

    else if(nRet>0)
    {
        delete m_pNC[pN->m_nNo -1];
    }

    m_pNC[pN->m_nNo-1]=pN;

    return 1;

}

int Profile::CheckNode(Node* pN)
{
    if(!pN) return -2;

    if(pN->m_nNo < 1 || pN->m_nNo > m_nNC) return -1;

    if(m_pNC[pN->m_nNo-1]) return 1;

    return 0;

}

int Profile::AddElement(Element* pE)
{
    if(!m_pEC) return -1;
    if(!pE) return -2;

    int nRet = CheckElement(pE);
    if(nRet<0)
    {
        sprintf(Msg,"Error : Element %d invalid",pE->m_nNo);
        AppendLog(Msg);
        return -3;
    }

    else if(nRet>0)
    {
        delete m_pEC[pE->m_nNo -1];
    }

    m_pEC[pE->m_nNo-1]=pE;

    return 1;

}

int Profile::CheckElement(Element* pE)
{
    if(!pE) return -2;

    if(pE->m_nNo < 1 || pE->m_nNo > m_nEC) return -1;

    if(m_pEC[pE->m_nNo-1]) return 1 ;

    return 0;

}

int Profile::CalcSectValues()
{

    ResetSectValues();
    // printf("%d",pE->m_nN);
    
    for (int i=0;i<m_nEC;i++)
    {
        Element* pE = m_pEC[i];
        printf("%d",i);
        if(!pE) continue;
        // printf("checkpoint");
        printf("%d,",pE->m_nN);

        if(pE->m_nN == 4) 
        pE->SetData(); // invoke for rectangle element

        else
        pE->SetData(1); // invoke for tube element

        m_dA += pE->m_dA;

        for(int j=0;j<2;j++) m_dS[j]+= pE->m_dS[j];
        for(int j=0;j<3;j++) m_dIu[j]+= pE->m_dI[j];

    }
    
        m_de[0] = m_dS[1]/m_dA;
        m_de[1] = m_dS[0]/m_dA;

        // for(int k=0;k<2;k++)
        // {
        //     m_de[k]= m_dS[(k+1)%2]/m_dA;
        // }

        MTrans();

    return 0;

}

double Profile::MTrans()
{
    m_dIc[0]= m_dIu[0]-m_de[1]*m_de[1]*m_dA;
    m_dIc[1]= m_dIu[1]-m_de[0]*m_de[0]*m_dA;
    m_dIc[2]= m_dIu[2]-m_de[0]*m_de[1]*m_dA;
    
    double  dIdel = m_dIc[0] - m_dIc[1];
    double  dSum  = m_dIc[0] + m_dIc[1];
    double  dIsqr = sqrt(dIdel*dIdel + 4.*m_dIc[2]*m_dIc[2]);

    m_dIm[0] = 0.5*(dSum + dIsqr);
    m_dIm[1] = 0.5*(dSum - dIsqr);

    // calculate the rotation angle
    m_dAlpha = 0.5*atan2(2.*m_dIc[2],dIdel);

    return m_dAlpha;
}


void Profile::ListSectValues()
{
// (char*): cast operator
    AppendLog((char*)"Section values:\n");
    sprintf(Msg," Area.................: %10.2f mm^2\n",m_dA);
    AppendLog(Msg);
    sprintf(Msg," Static moment x......: %10.2f mm^3\n",m_dS[0]);
    AppendLog(Msg);
    sprintf(Msg," Static moment y......: %10.2f mm^3\n",m_dS[1]);
    AppendLog(Msg);

    sprintf(Msg," Centroid x...........: %10.1f mm\n",m_de[0]);
    AppendLog(Msg);
    sprintf(Msg," Centroid y...........: %10.1f mm\n",m_de[1]);
    AppendLog(Msg);

    AppendLog((char*)"Moment of inertia in user coordinates:\n");
    sprintf(Msg," Ix...................: %10.2f mm^4\n",m_dIu[0]);
    AppendLog(Msg);
    sprintf(Msg," Iy...................: %10.2f mm^4\n",m_dIu[1]);
    AppendLog(Msg);
    sprintf(Msg," Ixy..................: %10.2f mm^4\n",m_dIu[2]);
    AppendLog(Msg);

    AppendLog((char*)"Moment of inertia in centroid coordinates:\n");
    sprintf(Msg," Ix...................: %10.2f mm^4\n",m_dIc[0]);
    AppendLog(Msg);
    sprintf(Msg," Iy...................: %10.2f mm^4\n",m_dIc[1]);
    AppendLog(Msg);
    sprintf(Msg," Ixy..................: %10.2f mm^4\n",m_dIc[2]);
    AppendLog(Msg);

    AppendLog((char*)"Moment of intertia in main coordinates:\n");
    sprintf(Msg," Ieta.................: %10.2f mm^4\n",m_dIm[0]);
    AppendLog(Msg);
    sprintf(Msg," Izeta................: %10.2f mm^4\n",m_dIm[1]);
    AppendLog(Msg);
    sprintf(Msg," alpha................: %10.2f °\n",m_dAlpha*45./atan(1.));
    AppendLog(Msg);
}
