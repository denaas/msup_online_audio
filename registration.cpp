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
    // ���������� �����
    string password;
    // ���������� ������

    bool registration()
    {
        bool flag;
        //������ � ���� ������, ������������ �� ������ ����� � ����
        //���� ���
            // ������ ����� � ���� ������ (���������������� ����� Ms SQL)
            // ���������� ������
            // ������ ��� ������ � ���� ������
            // flag = True
        //���� ��
            // flag = False
        return flag;
    }
    bool autorization()
    {
        bool flag;
        //������ � ���� ������, ������������ �� ������ ����� � ����
        //���� ���
            // flag = False
        //���� ��
            //������ � ���� ������ �� ��������� ������ (������������� ������) ��� ������� ������������
            //���� �����
                //flag = True
            //�����
                //flag = False
        return flag;
    }
}
