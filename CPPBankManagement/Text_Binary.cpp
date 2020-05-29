#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Text_Binary.h"
#define SIZE  8                            // ÿ�ζ�ȡ�ַ���ĿΪ8
using namespace std;
void TxtToBinary(const char* filename) {
    ifstream fin;
    ofstream fout;
    int i = 0;
    int ibina[SIZE];       // ��Ŷ������ֽ���
    char cRead;            // �洢���ļ���������
    fin.open(filename, ios::in | ios::binary);
    fout.open("mybinary.dat");
    while (fin.peek() != EOF) {
        fin.read(&cRead, 1);
        for (i = 0; i < SIZE; i++) {
            if ((1 << SIZE - i - 1) & cRead) { ibina[i] = 1; }
            else { ibina[i] = 0; }                        //����ʱȥ��ǰ������˫б�ܼ���
            fout << ibina[i];
        }
    }
    fin.close();
    fout.close();
    remove(filename);
    rename("mybinary.dat", filename);
}
void BinaryToTxt(const char* filename) {
    ifstream fin;
    ofstream fout;
    int i = 0, j = 0, iTemp = 0;
    int ibina[SIZE];               //��Ŷ������ֽ��� 
    char cRead[SIZE];              //�洢���ļ��������� 
    char cChar;                    //����ɶ����ƻ�ԭ���ַ�
    fin.open(filename, ios::in | ios::binary);
    fout.open("mytext.dat");
    while (fin.peek() != EOF) {
        fin.read(cRead, SIZE);
        //���ַ�ת��Ϊ0101��ʽ�������������  
        for (i = 0; i < SIZE; i++) {
            ibina[i] = (cRead[i] - '0');    //��'0'���ܱ���Ϊ0101��ʽ������ᱣ��ΪASCII����ʽ 
        }
        //ÿ8λΪһ���ֽڽ��л�ԭ 
        iTemp = 1;
        cChar = 0;
        for (j = 7; j >= 0; j--) { cChar += ibina[j] * iTemp;   iTemp *= 2; }
        fout.write(&cChar, 1);
        //cout << cChar;                    //����ʱȥ��ǰ������˫б�ܼ���
    }
    fin.close();
    fout.close();
    remove(filename);
    rename("mytext.dat", filename);
}