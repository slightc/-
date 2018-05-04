#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


using namespace std;

struct Wage{
    int number;
    string name;
    int base;
    int add;
    int sub;
    int fact;
};

void AddStaff(vector<struct Wage> &wage,int number,string name,int base,int add,int sub,int fact);
void ShowStaff(vector<struct Wage> wage,int number);
void Compute(vector<struct Wage> &wage);
void Sort(vector<struct Wage> &wage);
int Search(vector<struct Wage> wage,int number);
void Output(vector<struct Wage> wage,string name);
void AddMode(vector<struct Wage> &wage);

int main()
{
    vector<struct Wage> wage;
    int mode=1,num;
    char name[20];

    AddStaff(wage,50001,"zhanghua",6000,1200,500,0);
    AddStaff(wage,50003,"lifang",5000,1000,200,0);
    AddStaff(wage,50002,"sunlei",7000,800,100,0);
    AddStaff(wage,50005,"chenxin",4000,1100,300,0);
    AddStaff(wage,50004,"guyan",9000,1200,0,0);

    

    cout<<"输入你的名字"<<endl;
    cin>>name;

    while(mode!=0)
    {
        system("cls");
        cout<<"输入要执行的命令0~6"<<endl;
        cout<<"1:Compute()计算实发工资"<<endl;
        cout<<"2:Sort()按职工号排序"<<endl;
        cout<<"3:Search()按职工号搜索"<<endl;
        cout<<"4:Output()输出所有职工信息"<<endl;
        cout<<"5:计算,排序,输出"<<endl;
        cout<<"6:添加职工信息"<<endl;
        cout<<"0:退出程序"<<endl;
        cin>>mode;

        switch(mode)
        {
            case 0: 
            cout<<"退出程序"<<endl;
            system("pause"); break;

            case 1:
            cout<<"计算实发工资"<<endl;
            Compute(wage);
            cout<<"计算完成"<<endl;
            system("pause"); break;

            case 2:
            cout<<"按职工号排序"<<endl;
            Sort(wage);
            cout<<"排序完成"<<endl;
            system("pause"); break;

            case 3:
            cout<<"按职工号搜索"<<endl;
            cout<<"输入要搜索的职工号:";
            cin>>num;
            if(num>=0 && num<999999)
                {
                    Search(wage,num);
                    cout<<"搜索完成"<<endl;
                }
            else
                 cout<<"超出搜索范围"<<endl;
            system("pause"); break;

            case 4:
            cout<<"输出所有职工信息"<<endl;
            Output(wage,name);
            cout<<"输出完成"<<endl;
            system("pause"); break;
            break;

            case 5:
            cout<<"计算,排序,输出"<<endl;
            Compute(wage);
            Sort(wage);
            Output(wage,name);
            cout<<"执行完成"<<endl;
            system("pause"); break;
            break;

            case 6:
            AddMode(wage);
            break;

            default:
            cout<<"输入错误，请正确输入"<<endl;
            system("pause"); break;
        }
    }

    return 0;
}

void AddStaff(vector<struct Wage> &wage,int number,string name,int base,int add,int sub,int fact)
{
    struct Wage staff={number,name,base,add,sub,fact};
    wage.insert(wage.end(),staff);
}

void AddMode(vector<struct Wage> &wage)
{
    struct Wage staff={0};
    int mode;
    int repeat=0;

    while(mode!=0)
    {
        repeat=0;
        system("cls");
        cout<<"添加模式"<<endl;
        cout<<"输入要执行的命令0~3"<<endl;
        cout<<"1:添加职工信息"<<endl;
        cout<<"2:删除所有职工信息"<<endl;
        cout<<"3:显示所有职工信息"<<endl;
        cout<<"0:退出添加模式"<<endl;
        cin>>mode;

        switch(mode)
        {
            case 0: 
            cout<<"退出添加模式"<<endl;
            system("pause"); break;

            case 1:
            cout<<"输入 编号 姓名 基本工资 附加工资 扣除工资："<<endl;
            cin>>staff.number>>staff.name>>staff.base>>staff.add>>staff.sub;
            if(staff.number>=0 && staff.number<1000000)
            {
                for(int i=0;i<wage.size();i++)
                    if(staff.number==wage[i].number)
                        repeat=1;
                if(!repeat)
                {
                    wage.insert(wage.end(),staff);
                    cout<<"添加完成"<<endl;
                }
                else
                    cout<<"编号错误，编号不可重复"<<endl;
            }
            else
                cout<<"编号错误，编号超出指定范围"<<endl;
            system("pause"); break;

            case 2: 
            wage.clear();
            cout<<"删除完成"<<endl;
            system("pause"); break;

            case 3: 
            for(int i=0;i<wage.size();i++)
                ShowStaff(wage,i);
            cout<<"删除完成"<<endl;
            system("pause"); break;

            default:
            cout<<"输入错误，请正确输入"<<endl;
            system("pause"); break;
        } 
    }
}

void ShowStaff(vector<struct Wage> wage,int number)
{
    
    if(number>=0 && number<wage.size())
    {
        cout.setf(ios::left);
        cout
        <<"职工号:"   <<setw(8)<<wage[number].number
        <<" 姓名:"    <<setw(14)<<wage[number].name
        <<" 基本工资:"<<setw(8)<<wage[number].base
        <<" 附加工资:"<<setw(8)<<wage[number].add
        <<" 扣除工资:"<<setw(8)<<wage[number].sub
        <<" 实发工资:"<<setw(8)<<wage[number].fact
        <<endl;
    }
    else
        cout<<"超出职工范围"<<endl;
    //cout.setf(ios::right);
}

void Compute(vector<struct Wage> &wage)
{
    for(int i=0;i<wage.size();i++)
    {
        wage[i].fact=wage[i].base+wage[i].add-wage[i].sub;
    }
}

void Sort(vector<struct Wage> &wage)
{
    struct Wage change;

    for(int j=0;j<wage.size()-1;j++)
    {
        for(int i=j;i<wage.size()-1;i++)
        {
            if(wage[i].number>wage[i+1].number)
            {
                change=wage[i];
                wage[i]=wage[i+1];
                wage[i+1]=change;
            }
        }
    }
}

int Search(vector<struct Wage> wage,int number)
{
    int left=0,right=wage.size()-1,seek=(wage.size()-1)/2;
    for(;left!=right;)
    {
        if(number>wage[seek].number)
            left=seek;
        else if(number<wage[seek].number)
            right=seek;
        else if(number==wage[seek].number)
            {
                //cout<<"num:%d name:%s base:%d add:%d sub:%d fact:%d\n",
                //wage[seek].number,wage[seek].name,wage[seek].base,wage[seek].add,wage[seek].sub,wage[seek].fact
                //);
                ShowStaff(wage,seek);
                return seek;
            }
        seek=(left+right)/2;
    }
    cout<<"没有此职工号"<<endl;
    return -1;
}

void Output(vector<struct Wage> wage,string name)
{
    char date[20];
    struct tm *timep;
    time_t timel;
    int i;

    time(&timel);
    timep=localtime(&timel);
    sprintf(date,"%d/%d/%d",timep->tm_year+1900,timep->tm_mon+1,timep->tm_mday);

    ofstream outfile;
    outfile.open("gzbb.dat",ios::out|ios::trunc);
    outfile<<"\t\t\t\t\tGong zi Bao Biao\n";
    outfile<<"************************************************************\n";
    outfile<<"\tnum\t\tname\t\tbase\tadd\t\tsub\t\tfact\n";
    
    for(int i=0;i<wage.size();i++)
    {
        outfile.setf(ios::left);
        outfile
        <<"\t"<<setw(7)<<wage[i].number
        <<"\t"<<setw(10)<<wage[i].name
        <<"\t"<<setw(7)<<wage[i].base
        <<"\t"<<setw(7)<<wage[i].add
        <<"\t"<<setw(7)<<wage[i].sub
        <<"\t"<<setw(7)<<wage[i].fact
        <<endl;
    }
    outfile.setf(ios::right);
    outfile<<"************************************************************\n";
    outfile<<"\t\t\t\t\t\t\t\t\t\t\tname:"<<name<<endl;
    outfile<<"\t\t\t\t\t\t\t\t\t\t\tdate:"<<date<<endl;

    outfile.close();
}