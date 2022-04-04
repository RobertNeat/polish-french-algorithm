#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct students{
    string name;
    string surname;
    int points;
};

void line(){cout<<endl<<"---------------------------------------------------------------------"<<endl;}
void dLine(){cout<<endl<<"====================================================================="<<endl;}

void readStudents(students*& arr, int studentCount, ifstream& file){
    string line, help;
    char semicolon;
    for (int i = 0;i < 2;i++){
        file >> semicolon;
    }
    for (int i = 0;i < studentCount;i++){
        file >> line;
        istringstream ss(line);
        getline(ss, arr[i].name, ';');
        getline(ss, arr[i].surname, ';');
        getline(ss, help);
        arr[i].points = atoi(help.c_str());
    }
}
void displayStudents(students* arr,int start, int stop)
{
    for (int i = start;i <= stop;i++)
    {
        cout <<"name: " <<arr[i].name;
        cout<<" surname: "<<arr[i].surname;
        cout<<" points: "<<arr[i].points<< endl;
    }
}
void menu(){
cout<<endl<<"Choose task:"<<endl;
cout<<"0. Quit"<<endl;
cout<<"1. Program reads file"<<endl;
cout<<"2. Division into specific intervals (polish flag)"<<endl;
cout<<"3. Division into specific intervals (french flag)"<<endl;
cout<<"Choose:";
}

int polishFlag(students* arr, int n){
    int a=0;
    int b=n-1;
    while(a<b){
        while(a<b && arr[a].points<=10){  a=a+1;  }
        while(a<b && arr[b].points>10){  b=b-1;  }
        if( a<b){
            swap(arr[a],arr[b]);
            a=a+1;
            b=b-1;
    }}

    int lastIndex=0;
    if(arr[a].points<=10){lastIndex=a+1;}
    else{lastIndex=a;}

    lastIndex=lastIndex-1;

    return lastIndex;
}

void frenchFlag(students* arr, int n, int* ptr1, int *ptr2){
    int a=-1;
    int b=0;
    int c=n;
    while(b<c){
        if(arr[b].points%3==0){
            a+=1;
            swap(arr[a],arr[b]);
            b+=1;
        }
        else{
            if(arr[b].points%3==2){
                c-=1;
                swap(arr[b],arr[c]);
            }
            else{
                b+=1;
            }
        }
}
*ptr1=a;
*ptr2=b;
}

int main()
{
        int studentCount;
        students* arr;
        ifstream file;
        file.open("students.csv");
        file >> studentCount;

    menu();
    int a;
    cin>>a;

    while(a!=0){
        switch (a){
    case 1: //read file from students.csv
        arr=new students[studentCount];
        readStudents(arr, studentCount, file);
        menu();
        cin>>a;
        break;
    case 2: //division for students between <=10 and >10 points
        //displaying - array before division
        line();
        cout<<"Array before splitting:"<<endl<<endl;
        displayStudents(arr, 0,studentCount-1);

        int split;
        split=polishFlag(arr,studentCount);

        line();
        cout<<"Array after split:"<<endl;
        cout<<endl<<"students which got <=10pkt. :"<<endl<<endl;
        displayStudents(arr,0,split);
        cout<<endl<<"students which got >10 pkt. :"<<endl<<endl;
        displayStudents(arr,split+1,studentCount-1);
        line();

        menu();
        cin>>a;
        break;
    case 3:
        //disply - array before split
        line();
        cout<<endl<<"Array before split:"<<endl;
        displayStudents(arr, 0,studentCount-1);

        int pointer1,pointer2;
        frenchFlag(arr,studentCount,&pointer1,&pointer2);

        line();

        cout<<endl<<"Array after split:"<<endl;
        cout<<endl<<"Range 1 (rest 0 after dividing by 3):"<<endl;
        displayStudents(arr,0,pointer1);
        cout<<endl<<"Range 2 (rest 1 after dividing by 3):"<<endl;
        displayStudents(arr,pointer1+1,pointer2-1);
        cout<<endl<<"Range 3 (rest 2 after dividing by 3):"<<endl;
        displayStudents(arr,pointer2,studentCount-1);
        line();

        menu();
        cin>>a;
        break;
    default:
        cout<<endl<<"Wrong number choosen!!";
        menu();
        cin>>a;
        }
    }

    //displayStudents(arr, studentCount);
    delete[] arr;
    file.close();
}
