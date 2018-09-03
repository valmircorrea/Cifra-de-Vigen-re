/**
* @file	    cifra_cesar.cpp
* @brief	programa de criptoanálise que utilize de força bruta para 
*           quebrar uma mensagem encriptada usando uma cifra de César tradicional.
* @author   Valmir Correa (valmircsjr@gmail.com)
* @date	    08/2018
*/

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include <string>
using std::string;
using std::stoi;

#include <cstring>

#include <algorithm>

#include <fstream>
using std::ifstream;
using std::ofstream;

#include <cstdlib>
using std::atoi;

/**
* @brief    Faz a leitura do conteudo do arquivo
* @param    arq Nome do arquivo a ser lido
* @return   Mensagem lida do arquivo
*/
string leitura (string arq) {
    
    ifstream arquivo (arq);
    
    if (!arquivo) {
        cerr << "Erro ao ler o arquivo " << arq << "!" << endl;
        exit (1);
    }

    string msg;
    while (!arquivo.eof()) {
        string str_temp;
        getline(arquivo, str_temp);
        msg += str_temp;
        msg += '\n';
    }

    if (msg == "") {
        cerr << "Não há mensagem para ser decifrada!" << endl;
        exit(1);
    }

    return msg;
}

/**
* @brief    Faz a escrita de uma mensagem em um arquivo
* @param    arq Nome do arquivo a ser aberto
*/
void escrita (string msg, string nome_arq) {
    
    ofstream arquivo (nome_arq, std::ofstream::ate);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo " << nome_arq << "!" << endl;
        exit (1);
    }

    arquivo << msg << endl;
    arquivo.close();
}

/**
* @brief    Cifra a mensagem recebida
* @param    msg Mensagem a ser cifrada
* @param    data Data
* @return   Mensagem cifrada
*/
string decifrar (string msg, char *chave) {

    string msg_decifrada = "";
    int msg_tam = msg.size();

    unsigned char alfabeto[96];
    for (int ii = 32; ii <= 127; ii++) {
        alfabeto[ii - 32] = ii;
    }

    int tam_chave = (int) strlen(chave);
    int aux = 0;

    for (int ii = 0; ii < msg_tam; ii++) {

        if (msg[ii] > 31 && msg[ii] <= 127) {
            for (unsigned char pp = 32; pp < 127; pp++) {
                if (msg[ii] == pp) {
                    int indice = (pp-chave[aux]) % 95;
                    if (indice < 0) {
                        indice += 95;
                    }
                    
                    msg_decifrada += alfabeto[indice];
                    aux++;
                    if (aux >= tam_chave) {
                        aux = 0;
                    }
                    break;
                }
            }
        } else {
            msg_decifrada += msg[ii];
        } 
    }
    return msg_decifrada;
}

/**
 * Função principal
*/
int main (int argc, char* argv[]) {

    // Verifica se os argumentos foram passados corretamente
    if (argc != 3) {
        cout << "--> Argumentos inválidos! Use o comando: ";
        cout << "'./cifra chave data/mensagem.txt'" << endl;
        exit(1);
    }

    bool chave_valida = false;
    // Garantindo que a chave é valida
    for (int ii = 0; ii < (int) strlen(argv[1]); ii++) {
        if ( (argv[1][ii] > 47 && argv[1][ii] < 57) ||
             (argv[1][ii] > 64 && argv[1][ii] < 91) ||
             (argv[1][ii] > 96 && argv[1][ii] < 123) ) {
            
            chave_valida = true;
        }
    }

    if (!chave_valida) {
        cout << "Chave inválida!" << endl;
        exit(1);
    }

    char *chave = new char [(int) strlen(argv[1])];
    for (int ii = 0; ii < (int) strlen(argv[1]); ii++) {
        chave[ii] = argv[1][ii];
    }

    // leitura da mensagem
    string arquivo_txt = argv[2];
    string msg = leitura(arquivo_txt);

    // cifrando
    string msg_decifrada = decifrar(msg, chave);
    
    string nome_arq = "data/mensagem_decifrada.txt";
    
    escrita(msg_decifrada, nome_arq);

    cout << "--> Mensagem cifrada em 'data/mensagem_decifrada'!" << endl;

    return 0;
}