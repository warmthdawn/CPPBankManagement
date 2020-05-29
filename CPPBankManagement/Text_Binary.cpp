#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Text_Binary.h"
#define SIZE  8                            // 每次读取字符数目为8
using namespace std;
void TxtToBinary(const char* filename) {
    ifstream fin;
    ofstream fout;
    int i = 0;
    int ibina[SIZE];       // 存放二进制字节流
    char cRead;            // 存储读文件流的数据
    fin.open(filename, ios::in | ios::binary);
    fout.open("mybinary.dat");
    while (fin.peek() != EOF) {
        fin.read(&cRead, 1);
        for (i = 0; i < SIZE; i++) {
            if ((1 << SIZE - i - 1) & cRead) { ibina[i] = 1; }
            else { ibina[i] = 0; }                        //测试时去掉前面语句的双斜杠即可
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
    int ibina[SIZE];               //存放二进制字节流 
    char cRead[SIZE];              //存储读文件流的数据 
    char cChar;                    //存放由二进制还原的字符
    fin.open(filename, ios::in | ios::binary);
    fout.open("mytext.dat");
    while (fin.peek() != EOF) {
        fin.read(cRead, SIZE);
        //将字符转换为0101形式后存入整型数组  
        for (i = 0; i < SIZE; i++) {
            ibina[i] = (cRead[i] - '0');    //减'0'才能保存为0101形式，否则会保存为ASCII码形式 
        }
        //每8位为一个字节进行还原 
        iTemp = 1;
        cChar = 0;
        for (j = 7; j >= 0; j--) { cChar += ibina[j] * iTemp;   iTemp *= 2; }
        fout.write(&cChar, 1);
        //cout << cChar;                    //测试时去掉前面语句的双斜杠即可
    }
    fin.close();
    fout.close();
    remove(filename);
    rename("mytext.dat", filename);
}