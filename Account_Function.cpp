#include <unistd.h>
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include "Account_Function.h"

using namespace std;


void Notice_Sign_In_Success(const string &name)
{
    system("cls");
    cout << "\t \t Dang Nhap Thanh Cong!!!" << '\n';
    cout << "\t \t Xin Chao " << name <<"!!!" << '\n';
}

void Notice_Sign_In_Fail()
{
    system("cls");
    cout << "ID hoac mat khau khong dung!!!" << '\n';
    cout << "Moi ban dang nhap lai!" << '\n';
    cout << "Nhan 1 phim bat ki de tiep tuc\n";
    getch();
    system("cls");
}

string convert_balance(ll balance)
{
    string res = to_string(balance);
    int Count = 0;
    for(int i = res.size() - 1; i >= 0; i--)
    {
        Count ++;
        if(Count == 3 && i != 0){
            res.insert(res.begin() + i, '.');
            Count = 0;
        }
    }
    return res;
}

bool get_ID(string &ID)
{
    do{
        ID = "";
        system("cls");
        cout << "Nhan esc de thoat\n";
        cout << "Moi nhap vao ID: ";
        char c = getch();
        while(c != 13)
        {
            if(GetKeyState(0x1B) & 0x8000) return 0;
            if(c == 8)
            {
                if(ID.size()){
                    ID.erase(ID.size() - 1, 1);
                }
                system("cls");
                cout << "Nhan esc de thoat\n";
                cout << "Moi nhap vao ID: " << ID;
            }
            if(32 <= c && c <= 126){
                ID = ID + c;
                cout << c;
            }
            c = getch();
        }
    }
    while(!Check_ID(ID));

    system("cls");

    return 1;
}

bool get_Name(string &Name)
{
    string Title1 =  "** Ho va ten duoc viet khong dau, khong chua cac ki tu dac biet va so **\n";
    string Title2 =  "Nhan esc de thoat\n";
    string Title3 =  "Moi nhap ho va ten cua ban: ";

    do{
        Name = "";
        system("cls");
        cout << Title1 << Title2 << Title3;
        char c = getch();
        while(c != 13)
        {
            if(GetKeyState(0x1B) & 0x8000) return 0;
            if(c == 8)
            {
                if(Name.size()){
                    Name.erase(Name.size() - 1, 1);
                }
                system("cls");
                cout << Title1 << Title2 << Title3 << Name;
            }
            if(32 <= c && c <= 126){
                Name = Name + c;
                cout << c;
            }
            c = getch();
        }
    }
    while(!Check_Name(Name));

    system("cls");

    Name = Standardized(Name);   // Chuẩn hóa string Name

    return 1;
}

int confirm_Password(const string &Password)
{
    string tmp="";
    string cf_Password = "";
    system("cls");
    cout << "Nhan esc de thoat ve man hinh chinh\n";
    cout << "Moi nhap lai mat khau cua ban: ";
    char c = getch();
    while(c != 13)
    {
        if(GetKeyState(0x1B) & 0x8000) return -1;
        if(c == 8)
        {
            if(cf_Password.size()){
                cf_Password.erase(cf_Password.size() - 1, 1);
                tmp.erase(tmp.size() - 1, 1);
            }
            system("cls");
            cout << "Nhan esc de thoat ve man hinh chinh\n";
            cout << "Moi nhap lai mat khau cua ban: " << tmp;
        }
        if(32 <= c && c <= 126){
            cf_Password = cf_Password + c;
            tmp += '*';
            cout << "*";
        }
        c = getch();
    }

    if(Check_Password(cf_Password) && cf_Password == Password) return 1;
    else{
        system("cls");
        cout << "Mat khau xac nhan khong khop :((" << '\n';
        cout << "Moi thu lai!!!" << '\n';
        cout << "Vui Long Cho!!!";
        for(int i = 1; i < 4; i++, sleep(1)) cout << '.';
        cout << '\n';
        return 0;
    }

    system("cls");

    return 1;
}

bool get_Password(string &Password, const bool &Need_Confirm)
{
    string Title1 =  "** Mat khau duoc viet khong dau va khong chua dau cach**\n";
    string Title2 =  "Nhan esc de thoat\n";
    string Title3 =  "Moi nhap mat khau cua ban: ";

    do{
        string tmp="";
        Password = "";
        system("cls");
        cout << Title1 << Title2 << Title3;
        char c = getch();
        while(c != 13)
        {
            if(GetKeyState(0x1B) & 0x8000) return 0;
            if(c == 8)
            {
                if(Password.size()){
                    Password.erase(Password.size() - 1, 1);
                    tmp.erase(tmp.size() - 1, 1);
                }
                system("cls");
                cout << Title1 << Title2 << Title3 << tmp;
            }
            if(32 <= c && c <= 126){
                Password = Password + c;
                tmp += '*';
                cout << "*";
            }
            c = getch();
        }
        if(!Check_Password(Password))continue;
        int v;
        if(!Need_Confirm) v = 1;
        else v = confirm_Password(Password);
        if(v == -1) return 0;
        if(v == 0) continue;
        break;
    }
    while(1);

    system("cls");

    return 1;
}

string Standardized(string &Name)
{
    string res = "";
    int L = Name.size();
    for(int i = 0; i < L; i++)
    {
        if(Name[i] == ' ' && ( i + 1 == L || Name[i + 1] == ' ')) continue;

        if(i == 0 || (i > 0 && Name[i - 1] == ' '))
        {
            if('a' <= Name[i] && Name[i] <= 'z') Name[i] -= 32;
        }

        if(i > 0 && Name[i - 1] != ' ')
        {
            if('A' <= Name[i] && Name[i] <= 'Z') Name[i] += 32;
        }

        res += Name[i];
    }

    return res;
}

bool Check_Name(string &Name)
{
    bool success = 1;
    while(Name.size() && Name[0] == ' ') Name.erase(0,1);
    if(Name.size() == 0) success = 0;
    for(int i = 0; i < int(Name.size()); i++)
    {
        if(!success) break;
        if(Name[i] != ' ' && ('a' > Name[i] || 'z' < Name[i]) && ('A' > Name[i] || 'Z' < Name[i]) )
            success = 0;
    }

    if(!success)
    {
        cout << '\n' << "Ho va ten khong hop le!!!" << '\n';
        cout << "Moi nhap lai!!!" << '\n';
        cout << "Vui Long Cho!!!";
        for(int i = 1; i < 4; i++, sleep(1)) cout << '.';
        cout << '\n';
    }
    return success;
}

bool Check_Password(string &Pass)
{
    bool success = 1;

    if(Pass.size() == 0) success=  0;
    for(int i = 0; i < int(Pass.size()); i++)
    {
        if(Pass[i] == ' ' || 32 > Pass[i] || 126 < Pass[i])
            success = 0;
    }

    if(!success){
        cout << '\n' << "Mat khau khong hop le!!!" << '\n';
        cout << "Moi nhap lai!!!" << '\n';
        cout << "Vui Long Cho!!!";
        for(int i = 1; i < 4; i++, sleep(1)) cout << '.';
        cout << '\n';
    }

    return success;
}

bool Check_ID(string &ID)
{
    bool success = 1;
    while(!ID.empty() && ID[0] == ' ') ID.erase(0,1);
    while(!ID.empty() && ID[ID.size() - 1] == ' ') ID.erase(ID.size() - 1,1);

    if(ID.size() != 5) success = 0;
    for(int i = 0; i < int(ID.size()); i++)
        if('0' > ID[i] || '9' < ID[i])
            success = 0;

    if(!success)
    {
        cout << "\nID khong hop le!! \n";
        cout << "Nhan 1 phim bat ki de tiep tuc!\n";
        getch();
    }
    return success;
}

void Out_Stream(const string &Direct, string content)
{
    ofstream File(Direct);
    File << content;
    File.close();
}

bool Check_Money(const ll &Money, const ll &User_balance, const ll &ATM_balance, ll value[], ll number[])
{
    bool success = 1;
    if(Money % 1000) {
        cout << "So tien khong hop le (Khong phai boi cua 1000) " << '\n';
        success = 0;
    }
    else if(Money < 50000) {
        cout << "So tien khong hop le (So tien nho hon 50.000 VND)" << '\n';
        success = 0;
    }
    else if(Money > User_balance * 1000)
    {
        cout << "So tien can rut lon hon so du tai khoan" << '\n';
        success = 0;
    }
    else
    {
        ll money = Money;
        for(int i = 0; i < 9; i++)
        {
            ll v = value[i] * 1000;
            money -= min(number[i], money / v) * v;
        }
        if(money || Money > ATM_balance * 1000)
        {
            cout << "Smart ATM khong du tien de tra cho ban :(" << '\n';
            success = 0;
        }
    }

    if(!success){
        cout << "Moi nhap lai so tien can rut!!!" << "\n\n";
        cout << "Nhan 1 phim bat ki de tiep tuc" << '\n';
        getch();
    }
    return success;
}

int check_Acc(const string &ID, const string &Password)
{
    ifstream in_file("Account.txt");
    string id, pass, name;
    int cnt = 0;
    while(in_file >> id)
    {

        if(id != ID)getline(in_file, pass);
        else{
            string direct = "Check_Banned/" + ID + ".txt";
            ifstream Check(direct);
            Check >> cnt;
            if(cnt >= 5) return 2;
            in_file >> pass;
            if(Password == pass)
            {
                Check.close();
                Check.open("Name/" + ID + ".txt");
                getline(Check, name);

                Notice_Sign_In_Success(name);
                in_file.close();
                Check.close();

                ofstream File(direct);
                File << 0;
                File.close();
                return 1;
            }
            else{
                cnt = min(cnt + 1, 5);
                ofstream File(direct);
                File << cnt;
                File.close();
                if(cnt == 5) return 3;
                break;
            }
        }
    }
    Notice_Sign_In_Fail();
    in_file.close();
    return 0;
}

