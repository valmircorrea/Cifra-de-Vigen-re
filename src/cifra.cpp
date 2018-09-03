/**
* @file	    cifra.cpp
* @brief	programa de criptoanálise que encripta uma mensagem com a cifra de Vigerene.
* @author   Valmir Correa (valmircsjr@gmail.com)
* @date	    08/2018
*/

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

// string msg_cifrada = "";
//     int msg_tam = msg.size();

//     unsigned char alfabeto[96];
//     for (int ii = 32; ii <= 127; ii++) {
//         alfabeto[ii - 32] = ii;
//     }

//     int tam_chave = (int) strlen(chave);
//     int aux = 0;

//     for (int ii = 0; ii < msg_tam; ii++) {

//         if (msg[ii] > 31 && msg[ii] <= 127) {
//             for (unsigned char pp = 32; pp <= 127; pp++) {
//                 if (msg[ii] == alfabeto[pp-32]) {
//                     int indice = ((pp-32)+chave[aux]) % 96;
                    
//                     msg_cifrada += alfabeto[indice];
//                     aux++;
//                     if (aux >= tam_chave) {
//                         aux = 0;
//                     }
//                     break;
//                 }
//             }
//         } else {
//             msg_cifrada += msg[ii];
//         } 
//     }

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

#include <vector>
using std::vector;

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
string cifrar (string msg, char *chave) {

    string msg_cifrada;
    vector <char> alfabeto;
    for (int ii = 32; ii <= 127; ii++) {
        alfabeto.push_back(ii);
    }
    
    int aux = 0;
    int tam_chave = (int) strlen(chave);
    for (int ii = 0; ii < (int) msg.length(); ii++) {

        if (msg[ii] >= 32 && msg[ii] <= 127) {
            vector<char>::iterator it_msg = find(alfabeto.begin(), alfabeto.end(), msg[ii]);
            vector<char>::iterator it_key = find(alfabeto.begin(), alfabeto.end(), chave[aux]);

            aux++;
            if (aux >= tam_chave) {
                aux = 0;
            }

            int indice_msg = (it_msg - alfabeto.begin());
            int indice_key = (it_key - alfabeto.begin());

            int indice_char = (indice_msg + indice_key) % 95;

            char caracter = alfabeto[indice_char];
            
            msg_cifrada += caracter;
        } else {
            msg_cifrada += msg[ii];
        }
    }
    return msg_cifrada;
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
    string msg_cifrada = cifrar(msg, chave);
    
    string nome_arq = "data/mensagem_cifrada.txt";
    
    escrita(msg_cifrada, nome_arq);

    cout << "--> Mensagem cifrada em 'data/mensagem_cifrada'!" << endl;

    return 0;
}