#include "f_profile.h"
#include "node.h"
#include "element.h"

#include<stdio.h>

f_profile::f_profile(const char* pName,double hi,double bi,double ti, //iprofile
                    double hu,double bu,double tu,double su,          //uprofile
                    double dit,double tt                              //tube profile
                    ):Profile(pName)
{
    m_dhi=hi;
    m_dbi=bi;
    m_dti=ti;

    m_dhu=hu;
    m_dbu=bu;
    m_dtu=tu;
    m_dsu=su;

    m_ddit=dit;
    m_dtt=tt;


    m_nErr=Check();
}

// f_profile::f_profile(const char* pName,double hu,double bu,double tu,double su):Profile(pName)
// {
//     m_dhu=hu;
//     m_dbu=bu;
//     m_dtu=tu;
//     m_dsu=su;

//     m_nErr=Check();

// }
        
// f_profile::f_profile(const char* pName,double dit,double tt):Profile(pName)
// {
//     m_ddit=dit;
//     m_dtt=tt;

//     m_nErr=Check();
// }


int f_profile::Check(){

    int nErr=0;

    if(m_dti>m_dhi)
    {
        nErr++;
    }
    if(m_dti>m_dbi)
    {
        nErr++;
    }

    if(m_dtu>m_dbu)
    {
        nErr++;
    }
    if(m_dsu>m_dhu)
    {
        nErr++;
    }

    if(m_dtt>m_ddit)
    {
        nErr++;
    }

return nErr;
    
}



int f_profile::Create()
{
if (m_nErr > 0)
    {
        sprintf(Msg,"*** error: invalid input data, %d errors\n",m_nErr);
        AppendLog(Msg);
        return 0;
    }

    // create the containers
    AddNodeContainer(50);
    AddElementContainer(14);

    // create Node instances

    Node*   pNA[50];
    
    pNA[0]  = new Node( 1, (0.5*m_dhu-m_dti+m_dhi)                          ,  -(0.5*m_dbi)                     );
    pNA[1]  = new Node( 2, (0.5*m_dhu-m_dti+m_dhi)                          ,   (0.5*m_dbi)                     );
    pNA[2]  = new Node( 3, (0.5*m_dhu-2*m_dti+m_dhi)                        ,  -(0.5*m_dbi)                     );
    pNA[3]  = new Node( 4, (0.5*m_dhu-2*m_dti+m_dhi)                        ,   (0.5*m_dbi)                     );
    pNA[4]  = new Node( 5, (0.5*m_dhu-2*m_dti+m_dhi)                        ,  -(0.5*m_dti)                     );
    pNA[5]  = new Node( 6, (0.5*m_dhu-2*m_dti+m_dhi)                        ,   (0.5*m_dti)                     );
    pNA[6]  = new Node( 7, (0.5*m_dhu)                                      ,  -(0.5*m_dti)                     );
    pNA[7]  = new Node( 8, (0.5*m_dhu)                                      ,   (0.5*m_dti)                     );
    pNA[8]  = new Node( 9, (0.5*m_dhu)                                      ,  -(0.5*m_dbi)                     );
    pNA[9]  = new Node(10, (0.5*m_dhu)                                      ,   (0.5*m_dbi)                     );
    pNA[10] = new Node(11, (0.5*m_dhu-m_dti)                                ,  -(0.5*m_dbi)                     );
    pNA[11] = new Node(12, (0.5*m_dhu-m_dti)                                ,   (0.5*m_dbi)                     );
    pNA[12] = new Node(13, (0.5*m_dhu)                                      ,  -(0.5*m_dbi+m_dbu-m_dsu)         );
    pNA[13] = new Node(14, (0.5*m_dhu)                                      ,  -(0.5*m_dbi+m_dbu)               );
    pNA[14] = new Node(15, (0.5*m_dhu-m_dtu)                                ,  -(0.5*m_dbi)                     );
    pNA[15] = new Node(16, (0.5*m_dhu-m_dtu)                                ,  -(0.5*m_dbi+m_dbu-m_dsu)         );
    pNA[16] = new Node(17, (0.5*m_dhu)                                      ,   (0.5*m_dbi+m_dbu-m_dsu)         );
    pNA[17] = new Node(18, (0.5*m_dhu)                                      ,   (0.5*m_dbi+m_dbu)               );
    pNA[18] = new Node(19, (0.5*m_dhu-m_dtu)                                ,   (0.5*m_dbi)                     );
    pNA[19] = new Node(20, (0.5*m_dhu-m_dtu)                                ,   (0.5*m_dbi+m_dbu-m_dsu)         );
    pNA[20] = new Node(21,-(0.5*m_dhu-m_dtu)                                ,   (0.5*m_dbi+m_dbu-m_dsu)         );
    pNA[21] = new Node(22,-(0.5*m_dhu-m_dtu)                                ,   (0.5*m_dbi)                     );
    pNA[22] = new Node(23,-(0.5*m_dhu)                                      ,   (0.5*m_dbi+m_dbu)               );
    pNA[23] = new Node(24,-(0.5*m_dhu)                                      ,   (0.5*m_dbi+m_dbu-m_dsu)         );
    pNA[24] = new Node(25,-(0.5*m_dhu)                                      ,   (0.5*m_dbi)                     );
    pNA[25] = new Node(26,-(0.5*m_dhu-m_dti)                                ,   (0.5*m_dbi)                     );
    pNA[26] = new Node(27,-(0.5*m_dhu-m_dti)                                ,  -(0.5*m_dbi)                     );
    pNA[27] = new Node(28,-(0.5*m_dhu-m_dtu)                                ,  -(0.5*m_dbi)                     );
    pNA[28] = new Node(29,-(0.5*m_dhu-m_dtu)                                ,  -(0.5*m_dbi+m_dbu-m_dsu)         );
    pNA[29] = new Node(30,-(0.5*m_dhu)                                      ,  -(0.5*m_dbi)                     );
    pNA[30] = new Node(31,-(0.5*m_dhu)                                      ,  -(0.5*m_dbi+m_dbu-m_dsu)         );
    pNA[31] = new Node(32,-(0.5*m_dhu)                                      ,  -(0.5*m_dbi+m_dbu)               );
    pNA[32] = new Node(33,-(0.5*m_dhu)                                      ,  -(0.5*m_dti)                     );
    pNA[33] = new Node(34,-(0.5*m_dhu)                                      ,   (0.5*m_dti)                     );
    pNA[34] = new Node(35,-(0.5*m_dhu-2*m_dti+m_dhi)                        ,  -(0.5*m_dti)                     );
    pNA[35] = new Node(36,-(0.5*m_dhu-2*m_dti+m_dhi)                        ,   (0.5*m_dti)                     );
    pNA[36] = new Node(37,-(0.5*m_dhu-2*m_dti+m_dhi)                        ,  -(0.5*m_dbi)                     );
    pNA[37] = new Node(38,-(0.5*m_dhu-2*m_dti+m_dhi)                        ,   (0.5*m_dbi)                     );
    pNA[38] = new Node(39,-(0.5*m_dhu-m_dti+m_dhi)                          ,   (0.5*m_dbi)                     );
    pNA[39] = new Node(40,-(0.5*m_dhu-m_dti+m_dhi)                          ,  -(0.5*m_dbi)                     );
    pNA[40] = new Node(41,-(0.5*m_dhu-m_dti+m_dhi-0.5*m_dti)                ,   (0.5*m_dbi+m_dtt+0.5*m_ddit)    );
    pNA[41] = new Node(42,-(0.5*m_dhu-m_dti+m_dhi-0.5*m_dti)                ,   (0.5*m_dbi)                     );
    pNA[42] = new Node(43,-(0.5*m_dhu-m_dti+m_dhi-0.5*m_dti)                ,   (0.5*m_dbi+2*m_dtt+m_ddit)      );
    pNA[43] = new Node(44,-(0.5*m_dhu-m_dti+m_dhi-0.5*m_dti+0.5*m_ddit)     ,   (0.5*m_dbi+m_dtt+0.5*m_ddit)    );
    pNA[44] = new Node(45,-(0.5*m_dhu-m_dti+m_dhi-0.5*m_dti-0.5*m_ddit)     ,   (0.5*m_dbi+m_dtt+0.5*m_ddit)    );
    pNA[45] = new Node(46, (0.5*m_dhu-m_dti+m_dhi-0.5*m_dti)                ,   (0.5*m_dbi)                     );
    pNA[46] = new Node(47, (0.5*m_dhu-m_dti+m_dhi-0.5*m_dti)                ,   (0.5*m_dbi)                     );
    pNA[47] = new Node(48, (0.5*m_dhu-m_dti+m_dhi-0.5*m_dti)                ,   (0.5*m_dbi+2*m_dtt+m_ddit)      );
    pNA[48] = new Node(49, (0.5*m_dhu-m_dti+m_dhi-0.5*m_dti+0.5*m_ddit)     ,   (0.5*m_dbi+m_dtt+0.5*m_ddit)    );
    pNA[49] = new Node(50, (0.5*m_dhu-m_dti+m_dhi-0.5*m_dti-0.5*m_ddit)     ,   (0.5*m_dbi+m_dtt+0.5*m_ddit)    );
   
   
   // store the instances
    for (int i=0;i<50;i++)
    {
        AddNode(pNA[i]);
    }


    // create Element instances
    Element* pEA[14];
    pEA[0]   = new Element( 1,  pNA[0]  ,pNA[1]    ,pNA[2]  ,pNA[3]     ,1      );
    pEA[1]   = new Element( 2,  pNA[4]  ,pNA[5]    ,pNA[6]  ,pNA[7]     ,0      );
    pEA[2]   = new Element( 3,  pNA[8]  ,pNA[9]    ,pNA[10] ,pNA[11]    ,1      );
    pEA[3]   = new Element( 4,  pNA[9]  ,pNA[16]   ,pNA[18] ,pNA[19]    ,1      );
    pEA[4]   = new Element( 5,  pNA[16] ,pNA[17]   ,pNA[23] ,pNA[22]    ,0      );
    pEA[5]   = new Element( 6,  pNA[21] ,pNA[20]   ,pNA[24] ,pNA[23]    ,1      );
    pEA[6]   = new Element( 7,  pNA[12] ,pNA[8]    ,pNA[15] ,pNA[14]    ,1      );
    pEA[7]   = new Element( 8,  pNA[13] ,pNA[12]   ,pNA[31] ,pNA[30]    ,0      );
    pEA[8]   = new Element( 9,  pNA[28] ,pNA[27]   ,pNA[30] ,pNA[29]    ,1      );
    pEA[9]   = new Element( 10, pNA[26] ,pNA[25]   ,pNA[29] ,pNA[24]    ,1      );
    pEA[10]  = new Element( 11, pNA[32] ,pNA[33]   ,pNA[34] ,pNA[35]    ,0      );
    pEA[11]  = new Element( 12, pNA[36] ,pNA[37]   ,pNA[39] ,pNA[38]    ,1      );
    pEA[12]  = new Element( 13, pNA[40] ,pNA[41]   ,pNA[42], pNA[43], pNA[44]   );
    pEA[13]  = new Element( 14, pNA[45] ,pNA[46]   ,pNA[47], pNA[48], pNA[49]   );
    


    // store the instances
    for (int i=0;i<14;i++)
    {
        AddElement(pEA[i]);
    }

    // calculate section values
    CalcSectValues();

    return 1;
}

void f_profile::List()
{
    sprintf(Msg,"\nProfile name................................: %s\n",m_pName);
    AppendLog(Msg);
    sprintf(Msg,"Length of I profile...........................: %10.2lf mm\n",m_dhi);
    AppendLog(Msg);
    sprintf(Msg,"Width of I profile............................: %10.2lf mm\n",m_dbi);
    AppendLog(Msg);
    sprintf(Msg,"Avg. Thickness of I profile...................: %10.2lf mm\n\n",m_dti);
    AppendLog(Msg);
    sprintf(Msg,"Length of U profile...........................: %10.2lf mm\n",m_dhu);
    AppendLog(Msg);
    sprintf(Msg,"Width of U profile............................: %10.2lf mm\n",m_dbu);
    AppendLog(Msg);
    sprintf(Msg,"Side wall Thickness of U profile..............: %10.2lf mm\n",m_dtu);
    AppendLog(Msg);
    sprintf(Msg,"Cross wall Thickness of U profile.............: %10.2lf mm\n\n",m_dsu);
    AppendLog(Msg);
    sprintf(Msg,"Inner diameter of tube profile................: %10.2lf mm\n",m_ddit);
    AppendLog(Msg);
    sprintf(Msg,"Thickness of tube profile.....................: %10.2lf mm\n",m_dtt);
    AppendLog(Msg);
    

    // print the data the Profile class only
    // if the geometric modell is created without errors
    if (m_nErr < 1) Profile::List();
}



// f_profile::f_profile(const char* pName):Profile(pName)
// {
//     m_nErr=Check();
// }

// int f_profile::Check()
// {
//     int nErr=0;
// }

// //Iprofile functions
// iprofile::iprofile(const char* pName,
//                  double hi, //length of the iprofile
//                  double bi, //width of the iprofile
//                  double ti //average thickeness of iprofile
//                 ):f_profile(pName)
//     {
//     m_dhi=hi;
//     m_dbi=bi;
//     m_dti=ti;

//     m_nErr=Check();
//     }

// int iprofile::Check()
// {   
//     int nErr=0;
//     if(m_dti>m_dhi)
//     {
//         nErr++;
//     }
//     if(m_dti>m_dbi)
//     {
//         nErr++;
//     }
// return nErr;

// }

// void iprofile::List()
// {
//     sprintf(Msg,"Profile name................................: %s\n",m_pName);
//     AppendLog(Msg);
//     sprintf(Msg,"Length of I profile.........................: %s\n",m_dhi);
//     AppendLog(Msg);
//     printf(Msg,"Width of I profile...........................: %s\n",m_dbi);
//     AppendLog(Msg);
//     printf(Msg,"Avg Thickness of I profile...................: %s\n",m_dti);
//     AppendLog(Msg);
    
//     // print the data the Profile class only
//     // if the geometric modell is created without errors
//     if (m_nErr < 1) Profile::List();

// }


// //Uprofile Functions
// uprofile::uprofile(const char* pName,double hu,double bu,double tu,double su):f_profile(pName)
// {
//     m_dhu=hu;
//     m_dbu=bu;
//     m_dtu=tu;
//     m_dsu=su;

//     m_nErr=Check();

// }

// int uprofile::Check()
// {   
//     int nErr=0;
//     if(m_dtu>m_dbu)
//     {
//         nErr++;
//     }
//     if(m_dsu>m_dhu)
//     {
//         nErr++;
//     }
// return nErr;

// }

// void uprofile::List()
// {
//     sprintf(Msg,"Profile name................................: %s\n",m_pName);
//     AppendLog(Msg);
//     sprintf(Msg,"Length of U profile.........................: %s\n",m_dhu);
//     AppendLog(Msg);
//     printf(Msg,"Width of U profile...........................: %s\n",m_dbu);
//     AppendLog(Msg);
//     sprintf(Msg,"Side wall Thickness of U profile.............: %s\n",m_dtu);
//     AppendLog(Msg);
//     sprintf(Msg,"Cross wall Thickness of U profile............: %s\n",m_dsu);
//     AppendLog(Msg);
    
//     // print the data the Profile class only
//     // if the geometric modell is created without errors
//     if (m_nErr < 1) Profile::List();

// }


// //Tube profile fucntions        
// tprofile::tprofile(const char* pName,double dit,double tt):f_profile(pName)
// {
//     m_ddit=dit;
//     m_dtt=tt;

//     m_nErr=Check();
// }

// int tprofile::Check()
// {   
//     int nErr=0;
//     if(m_dtt>m_ddit)
//     {
//         nErr++;
//     }
// return nErr;

// }


// void tprofile::List()
// {
//     sprintf(Msg,"Profile name................................: %s\n",m_pName);
//     AppendLog(Msg);
//     sprintf(Msg,"Inner diameter of tube profile..............: %s\n",m_ddit);
//     AppendLog(Msg);
//     printf(Msg,"Thickness of tube profile....................: %s\n",m_dtt);
//     AppendLog(Msg);
   
//     // print the data the Profile class only
//     // if the geometric modell is created without errors
//     if (m_nErr < 1) Profile::List();

// }


// //Create functions

// int iprofile::Create()
// {
//     if(m_nErr>0)
//     {
//         sprintf(Msg,"*** error: invalid input data, %d errors\n",m_nErr);
//         AppendLog(Msg);
//         return 0; 
//     }
//     AddNodeContainer(12);
//     AddElementContainer(6);

//     Node* pNA[12];

//     pNA[0] = new Node(1,(m_dhi),      ());


// }

// int uprofile::Create()
// {
//     if(m_nErr>0)
//     {
//         sprintf(Msg,"*** error: invalid input data, %d errors\n",m_nErr);
//         AppendLog(Msg);
//         return 0; 
//     }
//     AddNodeContainer(4);
//     AddElementContainer(6);

// }

// int tprofile::Create()
// {
//     if(m_nErr>0)
//     {
//         sprintf(Msg,"*** error: invalid input data, %d errors\n",m_nErr);
//         AppendLog(Msg);
//         return 0; 
//     }   

//     AddNodeContainer(8);
//     AddElementContainer(2);
// }



