#pragma once
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

//实现文本与二进制的相互转换
void TxtToBinary(const char* filename); //文本转二进制
void BinaryToTxt(const char* filename); //二进制转文本