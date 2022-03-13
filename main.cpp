#include "node.h"
#include "element.h"
#include "f_profile.h"
#include "profile.h"
#include "base.h"

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<iostream>

using namespace std;

int main()
{
    cout<<"Choose from the given sections(all units in mm)"<<endl;
    cout<<"1.  U100 IPE100 Tube 88.9 x 2.9"<<endl;
    cout<<"2.  U120 IPE100 Tube 88.9 x 2.9"<<endl;
    cout<<"3.  U140 IPE100 Tube 88.9 x 2.9"<<endl;
    cout<<"4.  Enter custom dimensions(all in mm)"<<endl;
    
    int select;
    cout<<"Enter your selection(1-4) :";
    cin>>select;

    char pName[256];
    double hu=0.,bu=0.,tu=0.,su=0.; // for U section
    double hi=0.,bi=0.,ti=0.;       // for I section
    double dit=0.,tt=0.;            // for tube section

    switch(select)
    {
        case 1:
            strcpy(pName,"Profile1");
            hu=100;
            bu=50;
            tu=8.5;
            su=6;

            hi=100;
            bi=55;
            ti=5.7;
            
            dit=83.1;
            tt=2.9;
        break;

        case 2:
            strcpy(pName,"Profile2");
            hu=120;
            bu=55;
            tu=9;
            su=7;

            hi=100;
            bi=55;
            ti=5.7;
            
            dit=83.1;
            tt=2.9;
        break;
        
        case 3:
            strcpy(pName,"Profile3");
            hu=140;
            bu=60;
            tu=10;
            su=7;

            hi=100;
            bi=55;
            ti=5.7;
            
            dit=83.1;
            tt=2.9;
        break;

        case 4:
            strcpy(pName,"CustomProfile");
            cout<<"Enter custom dimensions(all in mm) :"<<endl;
            cout<<"U beam :"<<endl;
            cout<<"height : ";cin>>hu;
            cout<<"breadth : ";cin>>bu;
            cout<<"side wall thickness : ";cin>>tu;
            cout<<"cross wall thickness : "; cin>>su;
            cout<<"I beam :"<<endl;
            cout<<"height : ";cin>>hi;
            cout<<"breadth : ";cin>>bi;
            cout<<"average thickness : ";cin>>ti;
            cout<<"Tube :"<<endl;
            cout<<"inner diameter : ";cin>>dit;
            cout<<"section thickness : ";cin>>tt;
            
            
        break;

        default:
        cout<<"Check your selection"<<endl;
        return 0;
    }

    // creating the full profile

    f_profile pro = f_profile(pName,hi,bi,ti,hu,bu,tu,su,dit,tt);
    pro.Create();
    pro.List();

    return 0;
}