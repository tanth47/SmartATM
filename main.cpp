#include <iostream>
#include <unistd.h>
#include <conio.h>
#include "Account_Function.h"
#include "ATM_Function.h"

using namespace std;

int main()
{
    ATM BIDV;
    while(1)
    {
        system("cls");
        string Type;
        BIDV.Home_Screen();
        cin >> Type;
        system("cls");
        if(Type == "1")
        {
            if(!BIDV.Sign_Up())continue;
            BIDV.Update_State();
            cout << "Nhan 1 phim bat ki de tiep tuc!" << '\n';
            getch();
        }
        else if(Type == "2")
        {
            if(!BIDV.Sign_In()){
                system("cls");
                cout << "Dang nhap that bai :((" << '\n';
                cout << "Vui long cho" << '\n';
                for(int i = 1; i < 4; i++, sleep(1)) cout << '.';
                continue;
            }
            while(1)
            {
                BIDV.Option();
                int Op;
                cin >> Op;
                system("cls");
                if(Op == 1) BIDV.Send_money();
                if(Op == 2) BIDV.Withdrawal();
                BIDV.Update_State();
                if(Op == 3) BIDV.Check_balance();
                if(Op == 4) BIDV.Transfer();
                if(Op == 5) BIDV.Check_History();
                if(Op == 6) break;
                if(Op == 7){
                    BIDV.Quit();
                    exit(0);
                }
                cout << "Nhan 1 phim bat ki de tiep tuc" << '\n';
                getch();
                system("cls");
            }
        }
        else if(Type == "3") break;
        else {
            cout << "Lua chon khong hop le!!!" << '\n';
            cout << "Nhan 1 phim bat ki de tiep tuc" << '\n';
            getch();
        }
    }

    BIDV.Quit();
}
