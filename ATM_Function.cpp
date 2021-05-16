#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <conio.h>
#include <unistd.h>
#include <windows.h>
#include "Account_Function.h"
#include "ATM_Function.h"

using namespace std;

ATM::ATM()
{
    ifstream in_file("ATM_State.txt");
    in_file >> Count;
    for(int i = 0; i < 9; i++) in_file >> number[i];
    in_file >> ATM_balance;
    in_file.close();
}

void ATM::Home_Screen()
{
    cout << "\t\t\t Chao Mung Den Voi BIDV Smart ATM \n";
    cout << "[ 1 ]. Dang ki tai khoan. \n";
    cout << "[ 2 ]. Dang nhap vao he thong. \n";
    cout << "[ 3 ]. Thoat. \n";
    cout << "____________________________________________ \n";
}

void ATM::Quit()
{
    cout << "Hen Gap Lai Lan Sau!!!";
    sleep(2);
    cout << "\n\n\n\n\n";
}

void ATM::Option()
{
    cout << "\t\t\t Bang Chuc Nang \n";
    cout << "[ 1 ]. Gui tien vao tai khoan \n";
    cout << "[ 2 ]. Rut tien tu tai khoan \n";
    cout << "[ 3 ]. Kiem tra so du tai khoan \n";
    cout << "[ 4 ]. Chuyen tien den so tai khoan \n";
    cout << "[ 5 ]. Kiem tra lich su giao dich \n";
    cout << "[ 6 ]. Dang xuat \n";
    cout << "[ 7 ]. Thoat. \n";
    cout << "____________________________________________ \n";
}

void ATM::Update_State()
{
    ofstream out_file("ATM_State.txt");
    out_file << Count <<'\n';
    for(int i = 0; i < 9; i++) {
        out_file << number[i];
        if(i == 8) out_file << '\n';
        else out_file << " ";
    }
    out_file << ATM_balance;
    out_file.close();
}

void ATM::Update_History(const string &ID, const string &content, const char* Time, const ll &balance)
{
    string direct = "History/" + ID + ".txt";
    ofstream File(direct , ios :: app);
    File.seekp(ios_base :: end);
    File << Time;
    File << "Noi Dung: " << content << '\n';
    if(balance){
        File << "So du: ";
        if(balance < 0) File << "-";
        else File << "+";
        File << convert_balance(abs(balance)) << " VND";
    }
    File << '\n' << '\n';
    File.close();
}

bool ATM::Sign_Up()
{
    string Name, Password;
    if(!get_Name(Name)) return 0;
    if(!get_Password(Password, 1)) return 0;
    Count++;
    ID = to_string(Count);
    while(ID.size() < 5) ID = '0' + ID;

    cout << "Chuc Mung Ban Da Tao Tai Khoan Thanh Cong!!!" << '\n';
    cout << "ID cua ban la:              " << ID << '\n';
    cout << "So du tai khoan cua ban la: " << "0 VND" << '\n';
    cout << "*Luu y: Tuyet Doi Khong De Nguoi Khac Biet Mat Khau Cua Ban" << '\n';

    time_t now = time(0);
    Update_History(ID, "Tao Tai Khoan Thanh Cong", ctime(&now), 0);

    Out_Stream("Check_Banned/" + ID + ".txt", "0");
    Out_Stream("Name/" + ID +".txt", Name);
    Out_Stream("Balance/" + ID +".txt", "0");


    ofstream out_file("Account.txt", ios :: app);
    out_file.seekp(ios_base :: end);
    out_file << ID << " " << Password << '\n';
    out_file.close();

    return 1;
}

bool ATM::Sign_In()
{
    bool success = 1;
    string Password;
    do{
        if(!get_ID(ID)) {success = 0; break;}
        if(!get_Password(Password, 0)) {success = 0; break;}
        int t = check_Acc(ID, Password);
        if(t == 0) continue;
        if(t == 3) {
            success = 0;
            cout << "Tai Khoan Bi Khoa Do Dang Nhap That Bai Qua 5 Lan" << '\n';
            time_t now = time(0);
            Update_History(ID, "Tai Khoan Bi Khoa Do Dang Nhap That Bai Qua 5 Lan", ctime(&now), 0);
            cout << "Nhan 1 phim bat ki de tiep tuc" << '\n';
            getch();
        }
        if(t == 2){
            success = 0;
            cout << "Tai Khoan Da Bi Khoa" << '\n';
            cout << "Nhan 1 phim bat ki de tiep tuc" << '\n';
            getch();
        }
        break;
    }
    while(1);

    if(success)
    {
        ifstream File("Balance/" + ID + ".txt");
        File >> User_balance;
        File.close();
    }

    return success;
}

void ATM::Send_money()
{
    cout << "-----------------------Gui Tien-----------------------" << '\n';
    cout << "Nhap vao so to tien ban gui tuong ung voi moi menh gia" << '\n';
    cout << "       Menh gia                    So luong           " << '\n';

    ll tmp = 0;
    for(int i = 0; i < 9; i++)
    {
        cout << setw(9) << setfill(' ') << value[i] << ".000vnd" ;
        cout << setw(22) << setfill(' ') << ' ';

        ll cnt;                                                        //
        cin >> cnt;                                                     // nhap vao so luong to tien menh gia value[i]
        number[i] += cnt;                                               // Tang so luong to tien trong ATM
        ATM_balance += cnt * value[i];                                  // Tang so du trong may ATM
        User_balance += cnt * value[i];                                 // Tang so du cua nguoi dung
        tmp += cnt * value[i];
    }
    time_t now = time(NULL);
    Update_History(ID, "Gui Tien", ctime(&now), tmp * 1000);
    Out_Stream("Balance/" + ID +".txt", to_string(User_balance));

    cout << "----------------Giao dich thanh cong!!!----------------" << '\n';
}

void ATM::Check_balance()
{
    cout << "So du TK: " << convert_balance(User_balance * 1000) << " VND \n";
}

void ATM::Withdrawal()
{
    ll Money;
    do{
        system("cls");
        cout << "So tien can rut la boi cua 1000 va toi thieu la 50.000 VND" << '\n';
        cout << "Nhap 0 de thoat.\n" ;
        cout << "Moi nhap so tien can rut: " ;
        cin >> Money;
        if(!Money) return;
    }
    while(!Check_Money(Money, User_balance, ATM_balance, value, number));
    ATM_balance -= Money / 1000;
    User_balance -= Money / 1000;
    time_t now = time(NULL);
    Update_History(ID, "Rut tien", ctime(&now), -Money);
    Out_Stream("Balance/" + ID +".txt", to_string(User_balance));

    cout << "\t\t    TIEN TRA VE" << '\n';
    cout << "       Menh gia                    So luong           " << '\n';
    for(int i = 0; i < 9; i++)
    {
        ll v = value[i] * 1000;
        ll cnt = min(number[i], Money / v);
        Money -= cnt * v;
        number[i] -= cnt;
        cout << setw(9) << setfill(' ') << value[i] << ".000vnd" ;
        cout << setw(22) << setfill(' ') << ' ' << cnt << '\n';
    }

    cout << "----------------Giao dich thanh cong!!!----------------" << '\n';
}

void ATM::Transfer()
{
    string Receiver_ID;
    cout << "1. Nhap vao ID cua nguoi nhan!\n";
    get_ID(Receiver_ID);
    int check = stoi(Receiver_ID);
    if(check > Count){
        cout << "ID khong ton tai!!!\n";
        return;
    }

    string Direct = "Name/" + Receiver_ID + ".txt";
    fstream File(Direct, ios::in);
    string Receiver_Name;
    getline(File, Receiver_Name);
    File.close();

    cout << "2. Kiem tra\n";
    cout << "Ten nguoi nhan: " << Receiver_Name << '\n';

    cout << "Nhan [ Esc ] neu khong phai nguoi nhan!\n";
    cout << "Neu dung nhan 1 phim bat ki!\n";

    getch();
    system("cls");
    if(GetKeyState(0x1B) & 0x8000) return ;

    cout << "3. Nhap vao so tien can chuyen (So tien can chuyen phai la boi cua 1000).\n";
    ll Money;
    bool success = 1;
    cin >> Money;
    if(Money % 1000) {
        success = 0;
        cout << "So tien can chuyen khong phai boi cua 1000!\n";
    }
    else if(Money > User_balance * 1000)
    {
        success = 0;
        cout << "So tien can chuyen lon hon so du tai khoan!\n";
    }

    if(!success){
        return ;
    }

    time_t now = time(NULL);
    Money /= 1000;
    User_balance -= Money;
    Direct = "Balance/" + ID + ".txt";
    Out_Stream(Direct, to_string(User_balance));
    Update_History(ID, "Chuyen tien den so tai khoan: " + Receiver_ID, ctime(&now), -Money * 1000);

    Direct = "Balance/" + Receiver_ID + ".txt";
    ll Receiver_balance;
    File.open(Direct, ios::in);
    File >> Receiver_balance;
    Receiver_balance += Money;
    File.close();
    Out_Stream(Direct, to_string(Receiver_balance));
    Update_History(Receiver_ID, "Nhan tien tu so tai khoan: " + ID, ctime(&now), Money * 1000);


    cout << "----------------Giao dich thanh cong!!!----------------" << '\n';
}

void ATM::Check_History()
{
    string Direct = "History/" + ID + ".txt";
    ifstream File(Direct);
    string s;
    while(getline(File, s))
        cout << s << '\n';
}
