#pragma once

#include <initializer_list>
#include <algorithm>
#include <tuple>
#include <memory>
#include <iostream>
#include <string>
#include <type_traits>

class identification
{
public:
    string login;
    // Получаемый логин
    string password;
    // Получаемый пароль

    bool registration()
    {
        bool flag;
        //запрос в базу данных, присутствует ли данный логин в базе
        //если нет
            // внести логин в базу данных (предположительно будет Ms SQL)
            // хешировать пароль
            // внести хеш пароля в базу данных
            // flag = True
        //если да
            // flag = False
        return flag;
    }
    bool autorization()
    {
        bool flag;
        //запрос в базу данных, присутствует ли данный логин в базе
        //если нет
            // flag = False
        //если да
            //запрос в базу данных на сравнение пароля (хешированного пароля) для данного пользователя
            //если верен
                //flag = True
            //иначе
                //flag = False
        return flag;
    }
}
