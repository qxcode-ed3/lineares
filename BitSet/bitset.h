#ifndef BITSET_H
#define BITSET_H

#include <limits.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>


using namespace std;


#define NULL 0

class BitSet{
private:
    //  CHAR_BIT = número de bits da arquitetura geralmente 8 | sizeof(int) = número de bits da inteiro
    int numero_de_bits_inteiro = CHAR_BIT * sizeof(int);
    int tam;
    int *vetor = NULL;  
    void ligarBit(int k);
    void desligarBit(int k);
    void inverterBit(int k);
    bool bitKligado(int k);


public:
    BitSet(int tamanho);
    void print();
    void set();
    void set(int k, bool val=true);
    void set(int k, int val);
    void reset();
    void reset(int k);
    void flip();
    void flip(int k);
    string toString();


    bool operator[](int i){
        if(i<0 || i>=tam)
              throw std::out_of_range("index is out of range");
        return bitKligado(i);
    }



    bool operator== ( BitSet rhs){
        return toString()==rhs.toString();
    }
    bool operator!= (BitSet rhs){
        return ! ((*this) == rhs);
    }




};

#endif // BITSET_H
