#include <iostream>
#define ll long long

class ATM
{
    private:
        string ID;                                                  // ID cua nguoi dung
        ll Count = 0;                                              // Bien tao ID
        ll value[9] = {500, 200, 100, 50, 20, 10, 5, 2, 1};        // Gia tri tien Viet Nam
        ll number[9];                                              // So luong cac to tien
        ll ATM_balance = 0, User_balance = 0;                      // So du cua cay ATM va nguoi dung
    public:
        ATM();                                                                                             // constructor

        void Home_Screen();                                                                                // Trang chu cua ATM

        void Option();                                                                                     // Cac Chuc Nang

        void Quit();                                                                                       // ...

        void Update_State();                                                                               // Update cac bien private vao file

        void Update_History(const string &ID, const string &content, const char* Time, const ll &balance);  // Cap nhat lich su vao file

        bool Sign_Up();                                                                                    // Dang ki

        bool Sign_In();                                                                                    // Dang nhap

        void Send_money();                                                                                 // Gui tien

        void Check_balance();                                                                              // Kiem tra so du tai khoan

        void Withdrawal();                                                                                 // Rut tien

        void Transfer();                                                                                   // Chuyen tien

        void Check_History();                                                                         // In ra lich su giao dich
};
