#include "bitset.h"

BitSet::BitSet(int tamanho){
    tam = tamanho;
    int numero_minimo_de_inteiros = (numero_de_bits_inteiro + tam - 1)/numero_de_bits_inteiro;
    vetor = new int[numero_minimo_de_inteiros];
    memset(vetor, 0, numero_minimo_de_inteiros);
}

void BitSet::print(){
    cout << toString() << endl;

}

void BitSet::set(){
    //todos os bits ficam ligados
    memset(vetor, INT_MAX, sizeof(vetor));
}

void BitSet::set(int k, bool val){
    if(k<0 || k>=tam)
          throw std::out_of_range("index is out of range");
    if(val==true)
        ligarBit(k);
    else
        desligarBit(k);

}

void BitSet::set(int k, int val){
    if(k<0 || k>=tam)
        throw std::out_of_range("index is out of range");
    if(val%2==0)
        ligarBit(k);
    else
        desligarBit(k);

}

void BitSet::reset(){
    memset(vetor, 0, sizeof(vetor));

}

void BitSet::reset(int k){
    if(k<0 || k>=tam)
          throw std::out_of_range("index is out of range");
    desligarBit(k);

}

void BitSet::flip(){
    for(int i=0; i<tam;i++){
        inverterBit(i);
    }

}

void BitSet::flip(int k){
    if(k<0 || k>=tam)
          throw std::out_of_range("index is out of range");
    inverterBit(k);

}

string BitSet::toString(){

    char *saida = new char[tam];
    for(int i=0;i<tam;i++){
        if (bitKligado(i))
            saida[i] = '1';
        else
            saida[i] = '0';
    }
    return saida;

}

void BitSet::ligarBit(int k){
    int i = k/numero_de_bits_inteiro;
    int pos = k%numero_de_bits_inteiro;
    unsigned long aux = (1uL << pos);
    vetor[i] = vetor[i] | aux;
}

void BitSet::desligarBit(int k){
    int i = k/numero_de_bits_inteiro;
    int pos = k%numero_de_bits_inteiro;
    unsigned long aux = ~(1uL << pos);
    vetor[i] = vetor[i] & aux;

}

void BitSet::inverterBit(int k){
    int i = k/numero_de_bits_inteiro;
    int pos = k%numero_de_bits_inteiro;
    unsigned long aux = 1uL << pos;
    vetor[i] = vetor[i] ^ aux;

}

bool BitSet::bitKligado(const int k){
    int i = k/numero_de_bits_inteiro;
    int pos = k%numero_de_bits_inteiro;
    unsigned long aux = (1uL << pos);
    int r = vetor[i] & aux;
    if(r==0)
        return false;
    else
        return true;

}
