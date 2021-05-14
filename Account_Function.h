#include <iostream>
#include <string>

using namespace std;

string convert_balance(int balance); // Ham tra ve string bieu dien so tien duoi dang VND

string Standardized(string &Name);  // Chuan hoa string Name

bool Check_Name(string &Name); // Kiem tra ten co hop le hay khong

bool Check_Password(string &Pass); // Kiem tra password co hop le hay khong

bool Check_ID(string &ID); // Kiem tra xem ID co hop le hay khong

bool get_ID(string &ID); // Nhan ID tu nguoi dung

bool get_Name(string &Name); //  Nhan vao ten cua nguoi dung

bool get_Password(string &Password, const bool &Need_Confirm); // Nhan vao password cua nguoi dung, neu la dang ki tai khoan thi se co them chuc nang confirm

int check_Acc(const string &ID, const string &Password); // Kiem tra xem Acc co dung hay khong hay da bị khoa chua

void Out_Stream(const string &Direct, string content); // in content vao file

bool Check_Money(const int &Money, const int &User_balance, const int &ATM_balance, int value[], int number[]);// kiem tra so tien can rut(Money) co hop le hay khong
