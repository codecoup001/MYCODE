//CURRENCY CONVERTER USING C++

#include <iostream>
using namespace std;
int main() {

     float ind_rs;
float cad=(1/60.78);
float aud=(1/55.51);
float bef=(1/2.23);
float doll=(1/83.54);
float nzd=(1/51.55);
int choice;

cout<<"Enter amount in rupees:";
cin>>ind_rs;
cout<<"Choose the currency to convert to"<<endl;
cout<<"1.  Indian Rupees\n";
cout<<"2.  Canadian Dollar\n";
cout<<"3.  Australian Dollar\n";
cout<<"4.  Belgian Frank\n";
cout<<"5.  New Zealand Dollar\n";
cout<<"6.  Dollar\n";
cout<<"Enter your choice:";
cin>>choice;

switch (choice) {

    case 1:
    cout<<"Indian Rupees:"<<ind_rs*1<<endl;
    break;

    case 2:
    cout<<"Canadian Dollar:"<<ind_rs*cad<<endl;
    break;

    case 3:
    cout<<"Australian Dollar:"<<ind_rs*aud<<endl;
    break;

    case 4:
    cout<<"Belgian Frank:"<<ind_rs*bef<<endl;
    break;

    case 5:
    cout<<"New Zealand Dollar:"<<ind_rs*nzd<<endl;
    break;

    case 6:
    cout<<"Dollar:"<<ind_rs*doll<<endl;
    break;
}
return 0;

}

