#include "bitvector.h"

BitVector::BitVector(int tamanho){
    tam = tamanho;
    numero_minimo_de_inteiros = (numero_de_bits_inteiro + tam - 1)/numero_de_bits_inteiro;
    vetor = new int[numero_minimo_de_inteiros];
    memset(vetor, 0, numero_minimo_de_inteiros);
}

void BitVector::print(){
    cout << toString() << endl;

}

void BitVector::set(){
    //todos os bits ficam ligados
    memset(vetor, INT_MAX, sizeof(vetor));
}

void BitVector::set(int k, bool val){
    if(k<0 || k>=tam)
          throw std::out_of_range("index is out of range");
    if(val==true)
        ligarBit(k);
    else
        desligarBit(k);

}

void BitVector::set(int k, int val){
    if(k<0 || k>=tam)
        throw std::out_of_range("index is out of range");
    if(val%2==0)
        ligarBit(k);
    else
        desligarBit(k);

}

void BitVector::reset(){
    memset(vetor, 0, sizeof(vetor));

}

void BitVector::reset(int k){
    if(k<0 || k>=tam)
          throw std::out_of_range("index is out of range");
    desligarBit(k);

}

void BitVector::flip(){
    for(int i=0; i<tam;i++){
        inverterBit(i);
    }

}

void BitVector::flip(int k){
    if(k<0 || k>=tam)
          throw std::out_of_range("index is out of range");
    inverterBit(k);

}

void BitVector::resize(int newSize){
    int new_numero_minimo_de_inteiros = (numero_de_bits_inteiro + newSize - 1)/numero_de_bits_inteiro;
    int *new_vetor = new int[new_numero_minimo_de_inteiros];
    memset(new_vetor, 0, numero_minimo_de_inteiros);

    int total = numero_minimo_de_inteiros < new_numero_minimo_de_inteiros ? numero_minimo_de_inteiros : new_numero_minimo_de_inteiros;
    for(int i=0;i<total;i++){
        new_vetor[i] = vetor[i];
    }

    free(vetor);
    vetor = new_vetor;
    tam = newSize;


}

string BitVector::toString(){

    char *saida = new char[tam];
    for(int i=0;i<tam;i++){
        if (bitKligado(i))
            saida[i] = '1';
        else
            saida[i] = '0';
    }
    return saida;

}

void BitVector::ligarBit(int k){
    int i = k/numero_de_bits_inteiro;
    int pos = k%numero_de_bits_inteiro;
    unsigned long aux = (1uL << pos);
    vetor[i] = vetor[i] | aux;
}

void BitVector::desligarBit(int k){
    int i = k/numero_de_bits_inteiro;
    int pos = k%numero_de_bits_inteiro;
    unsigned long aux = ~(1uL << pos);
    vetor[i] = vetor[i] & aux;

}

void BitVector::inverterBit(int k){
    int i = k/numero_de_bits_inteiro;
    int pos = k%numero_de_bits_inteiro;
    unsigned long aux = 1uL << pos;
    vetor[i] = vetor[i] ^ aux;

}

bool BitVector::bitKligado(const int k){
    int i = k/numero_de_bits_inteiro;
    int pos = k%numero_de_bits_inteiro;
    unsigned long aux = (1uL << pos);
    int r = vetor[i] & aux;
    if(r==0)
        return false;
    else
        return true;

}

