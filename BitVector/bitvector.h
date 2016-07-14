#ifndef BITVECTOR_H
#define BITVECTOR_H

#include <limits.h>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>


using namespace std;


#define NULL 0



class BitVector{
private:
    //  CHAR_BIT = número de bits da arquitetura geralmente 8 | sizeof(int) = número de bits da inteiro
    int numero_de_bits_inteiro = CHAR_BIT * sizeof(int);
    int numero_minimo_de_inteiros;
    int tam;
    int *vetor = NULL;
    void ligarBit(int k);
    void desligarBit(int k);
    void inverterBit(int k);
    bool bitKligado(int k);


public:
    class bit_ref{
        friend class BitVector;
        int * refInteiro;
        int tamanho_palavra;
        int bit_pos;
    public:
        bit_ref(){};
        bit_ref(BitVector &bv, int k) {
            tamanho_palavra = bv.numero_de_bits_inteiro;
            refInteiro = &bv.vetor[k/tamanho_palavra];
            bit_pos = k%tamanho_palavra;
        }

        bit_ref &operator=(bool t) {
            if(t)
                *refInteiro = *refInteiro | (1uL << bit_pos);
            else
                *refInteiro = *refInteiro & (~(1uL << bit_pos));
            return *this;

        }

        bit_ref &operator=(bit_ref br) {
            *this = bool(br);
            return *this;
        }

        operator bool() const {
            return ((*refInteiro) & (1uL << bit_pos)) ? true : false;
        }

        bool operator== (bool b){
             int r = (*refInteiro) & (1uL << bit_pos) ;
             bool a = r==0? false : true;
             return a == b;
        }

        bool operator== (bit_ref br){
             return bool(*this) == bool(br);
        }

        bool operator!= (bool b){
             return ! (*this==b);
        }

        bool operator!= (bit_ref br){
             return ! (*this==br);
        }

        bool operator! (){
            return !bool(*this);
        }

        bool operator&(bool b){
            return (*this) & b;
        }

        bool operator&&(bool b) const{
            return bool(*this) && b;
        }

        bool operator||(bool b) const{
            return bool(*this) || b;
        }


    };

    BitVector(int tamanho);
    void print();
    void set();
    void set(int k, bool val=true);
    void set(int k, int val);
    void reset();
    void reset(int k);
    void flip();
    void flip(int k);
    void resize(int newSize);
    string toString();

    bool operator[](int k)const {
        if(k<0 || k>=tam)
              throw std::out_of_range("index is out of range");
        //ligar bit
        int i = k/numero_de_bits_inteiro;
        int pos = k%numero_de_bits_inteiro;
        unsigned long aux = (1uL << pos);
        int r = vetor[i] & aux;
        if(r==0)
            return false;
        else
            return true;
    }

    bit_ref operator [] (int k){
        if(k<0 || k>=tam)
              throw std::out_of_range("index is out of range");
        return bit_ref(*this,k);
    }

    bool operator== ( BitVector rhs){
        if(tam!=rhs.tam)
            return false;

        for(int i=0;i <tam;i++){
           if  (bitKligado(i) != rhs.bitKligado(i))
                    return false;
        }
        return true;
    }
    bool operator!= (BitVector rhs){
        return ! ((*this) == rhs);
    }

};











#endif // BITVECTOR_H
