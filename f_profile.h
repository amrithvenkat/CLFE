#ifndef F_PROFILE_H_INCLUDED
#define F_PROFILE_H_INCLUDED

#include "profile.h"

class f_profile : public Profile
{

    public:
        f_profile(const char* pName,
                double hi, //length of the iprofile
                double bi, //width of the iprofile
                double ti, //average thickeness of iprofile
                double hu, //length of the uprofile
                double bu, //width of the uprofile
                double tu, //thickeness of uprofile side wall
                double su,  //thickness of uprofile cross wall
                double dit, // diameter of tube
                double tt   // thickness of tube
                );//iprofile

        // f_profile(const char* pName,
        //         double hu, //length of the uprofile
        //         double bu, //width of the uprofile
        //         double tu, //thickeness of uprofile side wall
        //         double su  //thickness of uprofile cross wall
        //         );//uprofile
        
        // f_profile(const char* pName,
        //         double dit, // diameter of tube
        //         double tt   // thickness of tube
        //         );//tubeprofile
        
        // ~f_profile();

        int Check();
        int Create();
        void List();

    double m_dhi;
    double m_dbi;
    double m_dti;

    double m_dhu;
    double m_dbu;
    double m_dtu;
    double m_dsu;

    double m_ddit;
    double m_dtt;
    

    int m_nErr;
};

// class f_profile : public Profile
// {
//         public:
//                 f_profile(const char* pName);

//                 virtual int Check();
//                 virtual int Create();
//                 virtual void List();

//                 int m_nErr=0;

// };

// class iprofile : public f_profile
// {
//         public:
//                 iprofile(const char* pName,
//                  double hi, //length of the iprofile
//                  double bi, //width of the iprofile
//                  double ti //average thickeness of iprofile
//                );//iprofile

//                 int Check();
//                 int Create();
//                 void List();

//                 double m_dhi;
//                 double m_dbi;
//                 double m_dti;


//                 // int m_nErr;

// };

// class uprofile : public f_profile
// {
//         public:
//                 uprofile(const char* pName,
//                 double hu, //length of the uprofile
//                 double bu, //width of the uprofile
//                 double tu, //thickeness of uprofile side wall
//                 double su  //thickness of uprofile cross wall
//                 );//uprofile
                
                
//                 int Check();
//                 int Create();
//                 void List();
                
//                 double m_dhu;
//                 double m_dbu;
//                 double m_dtu;
//                 double m_dsu;

                
// };

// class tprofile : public f_profile
// {
//         public:
//                 tprofile(const char* pName,
//                 double dit, // diameter of tube
//                 double tt   // thickness of tube
//                 );//tubeprofile

//                 int Check();
//                 int Create();
//                 void List();
                
//                 double m_ddit;
//                 double m_dtt;

                

// };



#endif // F_PROFILE_H_INCLUDED