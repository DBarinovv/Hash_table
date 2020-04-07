
//{============================================================================
//|                                                                           ;
//|                COMPARING HASH FUNCTIONS USING HASH TABLES                 ;
//|                                                                           ;
//|                                                     (c) Barinov Denis     ;
//}============================================================================



//=============================================================================
//                                INCLUDES                                    ;
//=============================================================================

#include <stdio.h>
#include <fstream>
#include <iostream>

#include <vector>
#include <string>
#include <list>

//=============================================================================
//                              USED FROM STD                                 ;
//=============================================================================

using ::std::vector;
using ::std::string;
using ::std::list;

using ::std::hash;

using ::std::ifstream;
using ::std::cout;

//=============================================================================
//                                  CONSTANS                                  ;
//=============================================================================

const int C_sz_table = 1000;

enum types_of_hash {
                    E_std_hash     = 0,
                    E_ret_1        = 1,
                    E_ret_len      = 2,
                    E_sum_asci     = 3,
                    E_asci_div_len = 4,
                    E_xor_prev     = 5, // TBA
                    E_sz_enum      = 6, // size of enum
                    };

//=============================================================================
//                                 PROTOTYPE                                  ;
//=============================================================================


size_t My_Hash (string elem, const char type = '\0');

void Dump (vector <list <string>> hash_table);

void Make_File (vector <vector <list <string>>> hash_tables);

//=============================================================================
//=============================================================================


int main ()
{
    vector <vector <list <string>>> hash_tables;

    vector <list <string>> helper (C_sz_table);

    for (int i = 0; i < E_sz_enum; i++)
    {
        hash_tables.push_back (helper);
    }


    ifstream fin;
    fin.open ("res_text.txt");

    string word = "";
    while (fin >> word)
    {
        for (int i = 0; i < E_sz_enum; i++)
        {
            int pos = My_Hash (word, i);
            hash_tables[i][pos].push_back (word);
        }
    }

    Make_File (hash_tables);

    return 0;
}

//=============================================================================

size_t My_Hash (string elem, const char type)  // default type = 0
{
    switch (type)
    {
        case (E_std_hash):  // 0
        {
            hash <string> hash_str;
            return hash_str (elem) % C_sz_table;
        }

        case (E_ret_1):  // 1
        {
            return 1;
        }

        case (E_ret_len):
        {
            return elem.size() % C_sz_table;
        }

        case (E_sum_asci):  // 2
        {
            int res = 0;

            for (int i = 0; i < elem.size(); i++)
            {
                res += (char) elem[i];
            }

            return res % C_sz_table;
        }

        case (E_asci_div_len):  // 3
        {
            int res = 0;

            for (int i = 0; i < elem.size(); i++)
            {
                res += (char) elem[i];
            }

            return (res / elem.size()) % C_sz_table;
        }
    }
}

//=============================================================================

void Dump (vector <list <string>> hash_table)
{
    for (int i = 0; i < C_sz_table; i++)
    {
        printf ("[%0.4d]: ", i);

//        list <string> :: iterator iter;                                            //}
//        for (iter = hash_table[i].begin(); iter != hash_table[i].end(); iter++)    //|
//        {                                                                          //| to see elements in each list
//            cout << (*iter) << " || ";                                             //|
//        }                                                                          //}

        cout <<  hash_table[i].size();                                               //} to see count of elems in each list

        printf ("\n");
    }
}

//=============================================================================

void Make_File (vector <vector <list <string>>> hash_tables)
{
    FILE *fout = fopen ("output_exel.txt", "w");

    fprintf (fout, "NUMBER, STD, 1, LEN, SUM, SUM/LEN, XOR\n");

    for (int i = 0; i < C_sz_table; i++)
    {
        fprintf (fout, "%d, ", i);

        for (int k = 0; k < E_sz_enum; k++)
        {
            fprintf (fout, "%d, ", hash_tables[k][i].size());
        }

        fprintf (fout, "%d");
    }
}


//{============================================================================
//|                                 TESTS                                     ;
//}============================================================================
/*

int main ()
{
    vector <list <string>> hash_table (C_sz_table);

    ifstream fin;
    fin.open ("res_text.txt");

    string word = "";
    while (fin >> word)
    {
        int pos = My_Hash (word, *_TYPE TO TEST_*);
        hash_table[pos].push_back (word);
    }

    Dump (hash_table);

    return 0;
}

*/

