// walnambbong.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "pch.h"
#include <iostream>

int main()
{
    int nGamestart = 0;
    srand(time(NULL));
    rand();
    int nMoney = 1000;
    bool bRetry;
    char chRetry;

    ::cout << "[월남뽕 게임]\n" << endl;

    while (true) {
        ::cout << "게임을 시작하시겠습니까 (y, n) : ";
        cin >> chRetry;
        if (chRetry == 'y') {
            ::cout << endl;
            bRetry = true;
            break;
        }
        else if (chRetry == 'n') {
            ::cout << endl;
            bRetry = false;
            break;
        }
        else
            ::cout << "잘못된 입력입니다" << endl;
    }
    

    while (bRetry) // 게임이 끝난 후에 리트 할 건지 여부
    {
        int nCard[12]; // 카드에 1부터 12까지 순차적으로 초기화
        for (int i = 0; i < 12; i++)
            nCard[i] = i + 1;

        for (int i = 0; i < 120; i++) // 셔플
        {
            int nShuffle1 = rand() % 12;
            int nShuffle2 = rand() % 12;

            int nRam = nCard[nShuffle1];
            nCard[nShuffle1] = nCard[nShuffle2];
            nCard[nShuffle2] = nRam;
        }

        // 0, 1 공개; 2 승부; 3, 4, 5 추가배팅

        if (nCard[0] > nCard[1]) {
            int nRam = nCard[0];
            nCard[0] = nCard[1];
            nCard[1] = nRam;
        }

        int nBetting = 100;
        int nChoice;
        int nPluscard = 0;

        while (true) {
            ::cout << "[공개카드]\t[ " << nCard[0] << " ]\t[ " << nCard[1] << " ]" << endl;

            if (nPluscard >= 1)
                ::cout << "[제외카드]\t[ " << nCard[3] << " ] ";
            if (nPluscard >= 2)
                ::cout << " [ " << nCard[4] << " ] ";
            if (nPluscard >= 3)
                ::cout << " [ " << nCard[5] << " ] ";

            if (nGamestart == 0)
                nMoney -= nBetting;

            ::cout << "\n\n[배팅금액]: " << nBetting << "원\t[소지금]: " << nMoney << "원\n" << endl;
            
            ::cout << "3번째 카드를 공개하시려면 \t\t\t[1]\n추가배팅 후 제외카드를 보시려면 \t\t[2]\n포기하고 배팅금액의 절반을 회수하시려면 \t[0]\n을 입력해주세요 : ";
            cin >> nChoice;

            if (nPluscard == 3 && nChoice == 2) {
                ::cout << "추가배팅의 최대제한은 3회이므로 3번째 카드를 공개하겠습니다" << endl;
                nChoice = 1;
            }

            if (nChoice == 0) // 포기
            {
                nMoney += nBetting / 2;
                ::cout << "\n포기하고 절반금액을 회수했습니다.\n" << endl;
                ::cout << "[소지금액]: " << nMoney << "원\n" << endl;
                break;
            }
            else if (nChoice == 1) // 승부결정
            {
                ::cout << "[공개카드]\t[ " << nCard[0] << " ]\t[ " << nCard[1] << " ]\n" << endl;
                ::cout << "[배팅금액]: " << nBetting << "원\t[소지금]: " << nMoney << "원\n" << endl;

                ::cout << "[3번째 카드]\t[ " << nCard[2] << " ]" << endl;

                if (nCard[0] < nCard[2] && nCard[2] < nCard[1]) {
                    ::cout << "\n당신이 이겼습니다\n" << endl;
                    ::cout << "[획득금액]: " << nBetting;
                    if (nPluscard >= 0)
                        ::cout << " X 2";
                    if (nPluscard >= 1)
                        ::cout << " X 2";
                    if (nPluscard >= 2)
                        ::cout << " X 2";
                    if (nPluscard >= 3)
                        ::cout << " X 2";
                
                    while (nPluscard != -1) {
                        nBetting *= 2;
                        nPluscard--;
                    }
                    ::cout << " = " << nBetting << endl;
                    nMoney += nBetting;
                    ::cout << "[소지금액]: " << nMoney << "원\n" << endl;
                    break;
                }
                else {
                    ::cout << "\n당신이 졌습니다\n" << endl;
                    ::cout << "[소지금액]: " << nMoney << "원\n" << endl;
                    break;
                }
            }
            else if (nChoice == 2) // 추가배팅
            {
                int nPlusbetting;

                while (true) {
                    ::cout << "추가 배팅할 금액 (소지금 " << nMoney << "원 이내) :";
                    cin >> nPlusbetting;

                    if (nMoney < nPlusbetting)
                        ::cout << "돈이 부족합니다. 다시 입력해주세요" << endl;
                    else
                        break;
                }

                nMoney -= nPlusbetting;
                nBetting += nPlusbetting;
                nPluscard++;
                ::cout << "제외카드가 한 장 공개되었습니다\n" << endl;
            }
            else // 오류
            {
                ::cout << "잘못된 입력입니다,\n" << endl;
            }
            nGamestart = 100;
        }

        while (true) {
            ::cout << "게임을 다시하시겠습니까 (y, n) : ";
            cin >> chRetry;
            if (chRetry == 'y') {
                ::cout << endl;
                bRetry = true;
                nGamestart = 0;
                break;
            }
            else if (chRetry == 'n') {
                ::cout << endl;
                bRetry = false;
                break;
            }
            else
                ::cout << "잘못된 입력입니다" << endl;
        }
    }
    system("pause");
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
