#ifndef DES_H
#define DES_H

#endif // DES_H

/*

    Algoritmo di crittografia
    Claudio Malvica (26/10/2022)
    Sistemi e reti

*/

#include <string>
#include <bitset>
#include <cmath>

using namespace std;


// Variabili
int NUMBERS_P_BOX[8] =          {0,7,1,5,2,4,3,6};
int NUMBERS_S_BOX[4] =          {2,3,1,0};
string XOR_KEY       =          "01010011";

//Prototipi delle funzioni


int linearSearch(int _V[], int _size, int _number);
/*
    Ricerca Lineare - Dato un array e un numero, restituisce la prima posizione del vettore in cui compare quel numero
    Valori di ritorno:
        - prima posizione nel caso il numero venga trovato
        - -1 nel caso il numero non venga trovato
    Parametri:
        - array di interi in cui cercare il numero
        - dimensione dell'array
        - numero da cercare
*/

void invertBox(int _numberBox[], int _size, int _resultNumberBox[]);
/*
    Inversione Box - Dato un array contenente i valori di una P-BOX/S-BOX, calcola l'array necessario per invertire il processo
    Parametri:
        - Array BOX iniziale
        - Dimensione dell'array
        - Array in cui inserire il risultato
*/


string byteToString (string _binary);
/*
    Conversione da byte a stringa - Dato un byte rappresentato come stringa, ritorna il carattere ASCII rappresentato da quel byte
    Valori di ritorno:
        - Carattere nel caso la conversione vada a buon fine
        - Stringa vuota ("") nel caso il parametro non sia corretto
    Parametri:
        - Stringa contenente la rappresentazione binaria di un carattere ASCII
*/

int binaryToDecimal(string _binary);
/*
    Conversione da binario a decimale - Dato un byte rappresentato come stringa, ritorna come intero il valore decimale rappresentato
    Valori di ritorno:
        - Numero decimale nel caso la conversione vada a buon fine
    Parametri:
        - Stringa contenente la rappresentazione binaria di un numero decimale
*/

string P_BOX(int _NUMBERS_P_BOX_ARG[], string _message, bool _invert);
/*
    Metodo P-BOX - Data una stringa, esegue la crittografia mediante il metodo P-BOX
    Valori di ritorno:
        - Stringa contenente il messaggio criptato
    Parametri:
        - Array contenente i valori da usare per la crittografia (NULL per utilizzare quelli default)
        - Stringa contenente il messaggio da criptare
        - Bool per scegliere se decriptare un messaggio precedentemente criptato (true per invertire)
*/

string S_BOX(int _NUMBERS_S_BOX_ARG[], string _message, bool _invert);
/*
    Metodo S-BOX - Data una stringa, esegue la crittografia mediante il metodo S-BOX
    Valori di ritorno:
        - Stringa contenente il messaggio criptato
    Parametri:
        - Array contenente i valori da usare per la crittografia (NULL per utilizzare quelli default)
        - Stringa contenente il messaggio da criptare
        - Bool per scegliere se decriptare un messaggio precedentemente criptato (true per invertire)
*/

string DES(string _message);
/*
    Algoritmo di crittografia - Data una stringa, utilizza le funzioni XOR, P_BOX e S_BOX per crittografarla
    Valori di ritorno:
        - Stringa contenente il messaggio criptato
    Parametri:
        - Stringa contenente il messaggio da criptare

*/



int linearSearch(int _V[], int _size, int _number)
{
    for (int i = 0; i < _size; i++)
    {
        if(_V[i]==_number) return i;
    }
    return -1;
}

void invertBox(int _numberBox[], int _size, int _resultNumberBox[])
{
    for (int i = 0; i < _size; i++)
    {
        _resultNumberBox[i] = linearSearch(_numberBox, _size, i);
    }
}

//https://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting
string byteToString (string _binary)
{
    //Wrapper for the bitset to ulong conversion because that syntax is a bit too hard
    if(_binary.size() != 8) return "";

    string _temp = "";
    _temp = (char)bitset<8>(_binary).to_ulong();
    return _temp;
}

int binaryToDecimal(string _binary)
{
    //Converte un numero binario rappresentato con una stringa nel suo valore decimale corrispondente
    int _finalResult = 0;
    for (int i = _binary.size()-1; i >= 0; i--)
    {
        _finalResult += (_binary[i]-'0')*pow(2, labs(i-(_binary.size()-1)));
    }
    return _finalResult;
}

string P_BOX(int _NUMBERS_P_BOX_ARG[], string _message, bool _invert)
{
    int _NUMBERS_P_BOX[8];

    if (_NUMBERS_P_BOX_ARG != NULL)
    {
        copy(_NUMBERS_P_BOX_ARG, _NUMBERS_P_BOX_ARG+8, _NUMBERS_P_BOX);
    }
    else if (_NUMBERS_P_BOX_ARG == NULL)
    {
        if (_invert)
        {
            invertBox(NUMBERS_P_BOX, 8, _NUMBERS_P_BOX);
        }
        else
        {
            copy(NUMBERS_P_BOX, NUMBERS_P_BOX+8, _NUMBERS_P_BOX);
        }
    }

    string _temp;
    _temp.resize(8); //Alloco 8 byte per la stringa
    string _finalResult;



    for (int i = 0; i < _message.size(); i++)
    {
        string _binary = bitset<8>((int)_message[i]).to_string();
        for (int j = 0; j < 8; j++)
        {
            _temp[_NUMBERS_P_BOX[j]] = _binary[j];
        }
        _finalResult+=byteToString(_temp);
    }
    return _finalResult;
}


string S_BOX(int _NUMBERS_S_BOX_ARG[], string _message, bool _invert)
{
    int _NUMBERS_S_BOX[4];
    if (_NUMBERS_S_BOX_ARG != NULL)
    {
        copy(_NUMBERS_S_BOX_ARG, _NUMBERS_S_BOX_ARG+4, _NUMBERS_S_BOX);
    }
    else if (_NUMBERS_S_BOX_ARG == NULL)
    {
        if(_invert)
        {
            invertBox(NUMBERS_S_BOX, 4, _NUMBERS_S_BOX);
        }
        else
        {
            copy(NUMBERS_S_BOX, NUMBERS_S_BOX+4, _NUMBERS_S_BOX);
        }
    }

    string _finalResult;
    int _temp;

    for (int i = 0; i < _message.size(); i++)
    {
        string _binary = bitset<8>((int)_message[i]).to_string();
        string _tempResult;
        _tempResult.resize(8);

        for (int j = 0; j < _binary.size(); j+=2)
        {
            _temp = binaryToDecimal(_binary.substr(j,2)); //Converto in decimale le cifre del numero binario a 2 a 2
            _tempResult+=bitset<2>(_NUMBERS_S_BOX[_temp]).to_string();
        }
        _finalResult+=binaryToDecimal(_tempResult);
    }
    return _finalResult;
}


string XOR(string _value, string _key)
{
    string _finalResult = "";
    if (_key == "")
        _key = XOR_KEY;


    if (_value.size() != _key.size())
        return "";

    for (int i = 0; i < _value.size(); i++)
    {
        if (_value[i] == _key[i])
            _finalResult += "0";
        else
            _finalResult += "1";
    }
    return _finalResult;
}


string DES(string _message, bool _invert)
{
    if(_invert)
    {
        for (int i = 0; i < 16; i++)
        {
            string _tempResult = "";

            for (int j = 0; j < _message.size(); j++)
            {
                _tempResult += byteToString(XOR(bitset<8>((int)_message[j]).to_string(), ""));
            }
            string _PBOX_result = P_BOX(NULL, _tempResult, false);
            _message = S_BOX(NULL, _PBOX_result, false);
        }

    }
    else
    {
        for (int i = 0; i < 16; i++)
        {
            string _tempResult = "";
            string _SBOX_Result = S_BOX(NULL, _message, true);
            string _PBOX_Result = P_BOX(NULL, _SBOX_Result, true);
            for (int j = 0; j < _PBOX_Result.size(); j++)
            {
                _tempResult += byteToString(XOR(bitset<8>((int)_PBOX_Result[j]).to_string(), ""));
            }

            _message = _tempResult;
        }

    }


    return _message;
}

