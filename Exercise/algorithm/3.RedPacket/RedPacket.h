//
//  RedPacket.h
//  algorithm
//
//  Created by 宋春宇 on 2020/11/21.
//

#ifndef RedPacket_h
#define RedPacket_h

#include <stdio.h>
#include <time.h>

/*
    微信红包算法
 2倍均值算法，每个人期望一样，越后面的人方差越大
 min =
 max = (剩余钱数-(min*剩余人数))/剩余人数 * 2
*/

int getMoney(int remainPeople, int remainMoney)
{
    if (remainPeople <= 1)
    {
        return remainMoney;
    }
    int min = 1;
    int max = (remainMoney-(min*remainPeople))/remainPeople*2;
    int money = 0;
    if (max > min)
    {
        money = rand()%max + min;
    }
    else
    {
        money = min;
    }
    
    return money;
}

// money 单位（分）
void wechat(int people, int money)
{
    int money_check = 0;
    int remainPeople = people;
    int remainMoney = money;
    while (remainPeople > 0) {
        int randomMoney = getMoney(remainPeople, remainMoney);
        remainMoney -= randomMoney;
        --remainPeople;
        money_check += randomMoney;
        cout << randomMoney / 100.0f << " ";
    }
    cout << endl << "money_check:" << money_check << endl;
}

void RedPacket()
{
    cout << "3.RedPacket : " << endl;
    
    unsigned int seed = (unsigned int)(time(NULL));
    srand(seed);
    
    wechat(10, 1.0 * 100);
}

#endif /* RedPacket_h */
