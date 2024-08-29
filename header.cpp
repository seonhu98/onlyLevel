#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <unistd.h>
#define MAX 30000.0;
using namespace std;
struct only
{
    int turn;
    double exp;
    double max_exp;
    int level;
};
only user;
void play(only *user);           // 경험치 획득 함수
void initialization(only *user); // 구조체 초기화 함수
void level_updown(only *user);   // 레벨 변동 함수
void option(only *user);        //옵션추가
void play(only *user)
{
    int count;
    char name[40];
    cout << "참가자 이름을 입력하시오: ";
    cin >> name;
    cout << name << "님 반갑습니다.\n";
    initialization(user);
    double randnum;
    srand(time(NULL));
    while (user->level <= 99)
    {
        if (user->level < 99)
        {
            if (user->turn % 6 != 0)
            {
                randnum = rand() % 7000 - 3500;
                cout << user->turn << "번째 턴입니다.\n";
                cout << "현재 Level" << user->level << endl;
                cout << "경험치" << randnum << "를 획득하였습니다.\n";
                user->exp += randnum;
                cout << "현재 경험치" << user->exp << '\t' << "최대 경험치" << user->max_exp << '\t'
                     << "필요경험치" << user->max_exp - user->exp << endl;
                level_updown(user);
                option(user);
                sleep(1);
                system("clear");
                user->turn++;
            }
            else
            {
                double event = rand() % 5 + 1; // 이벤트 경험치 1~5배 발생
                if (randnum > 0)               /*양수일 경우에만 적용*/
                {
                    user->exp += event * randnum;
                    cout << user->turn << "번째 턴입니다.\n";
                    cout << "현재 Level" << user->level << endl;
                    cout << "이벤트 경험치" << randnum * event << "획득하였습니다\n";
                    cout << "현재 경험치" << user->exp << '\t' << "최대 경험치" << user->max_exp << '\t'
                         << "필요경험치" << user->max_exp - user->exp << endl;
                    level_updown(user);
                    option(user);
                    sleep(1);
                    system("clear");
                    user->turn++;
                }
                else
                {
                    cout << user->turn << "번째 턴입니다.\n";
                    cout << "현재 Level" << user->level << endl;
                    cout << "이벤트 경험치를 획득하지 못하였습니다.\n";
                    cout << "현재 경험치" << user->exp << '\t' << "최대 경험치" << user->max_exp << '\t'
                         << "필요경험치" << user->max_exp - user->exp << endl;
                    sleep(1);
                    system("clear");
                    user->turn++;
                }
            }
        }
        else
        {
            cout << "축하합니다. Level 99를 달성하였습니다. win\n";
            break;
        }
    }
}
void initialization(only *user)
{
    user->exp = 0.0;
    user->max_exp = MAX;
    user->level = 1;
    user->turn = 1;
}
void level_updown(only *user)
{

    double randnum;
    srand(time(NULL));
    randnum = (rand() % (26 - 18) + 18) * 0.1;
    if (user->exp < user->max_exp)
    {
        if (user->exp <= 0 && user->level <= 1)
        {
            user->level = 1;
            user->exp = 0.0;
            cout << "사망하셨습니다.다시 시작합니다.\n";
        }
        else if (user->exp <= 0 && user->level > 1)
        {
            user->level--;
            user->exp = user->max_exp / 2;
            cout << "Level이 감소하였습니다.경험치가 반으로 줄어듭니다.\n";
        }
    }
    if (user->exp >= user->max_exp && user->level > 0)
    {
        user->level++;
        user->exp -= user->max_exp;
        user->max_exp = randnum * MAX;
        cout << "축하합니다 Level up!! 현재 레벨은 " << user->level << "입니다.\n";
        cout << "현재 경험치" << user->exp << '\t' << "최대 경험치" << user->max_exp << '\t'
                << "필요경험치" << user->max_exp - user->exp << endl;
    }
}
void option(only *user)
{
    double randnum;
    srand(time(NULL));
    randnum = rand() % 6+1;

    if(user->turn%10==0)
    {
        cout<<"주사위게임을 시작합니다. 1이 나오면 10000 경험치 획득!\n";
        cout<<"주사위 나온 숫자"<<randnum<<'\n';

        if(randnum==1)
        {
            cout<<"주사위 경험치 획득\n";
            user->exp+=10000;
        }
        else
            cout<<"주사위 경험치를 획득하지 못했습니다.\n";
    }
}
