
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
#include <string_view>
#include <list>
#include <array>

#include "sha256.h"

//=============================================================================
//                              USED FROM STD                                 ;
//=============================================================================

using ::std::vector;
using ::std::string;
using ::std::string_view;
using ::std::list;
using ::std::array;

using ::std::hash;

using ::std::ifstream;
using ::std::cout;

//=============================================================================
//                                  CONSTANS                                  ;
//=============================================================================

const int C_sz_table = 8000;

enum types_of_hash {
                    E_std_hash     = 0,
                    E_ret_1        = 1,
                    E_ret_len      = 2,
                    E_sum_asci     = 3,
                    E_asci_div_len = 4,
                    E_sha_256      = 5,
                    E_sz_enum      = 6, // size of enum
                    };

//=============================================================================
//                                 PROTOTYPE                                  ;
//=============================================================================

size_t Hash_Std_Hash     (string_view elem);

size_t Hash_Ret_1        (string_view elem);

size_t Hash_Ret_Len      (string_view elem);

size_t Hash_Sum_Asci     (string_view elem);

size_t Hash_Asci_Div_Len (string_view elem);

size_t Hash_Sha_256      (string_view elem);

//-----------------------------------------------------------------------------

void Dump (vector <list <string_view>> hash_table);

void Make_File (array <array <list <string_view>, C_sz_table>, E_sz_enum> hash_tables);

//=============================================================================
//=============================================================================


int main ()
{
    array <array <list <string_view>, C_sz_table>, E_sz_enum> hash_tables;

    size_t (*arr_of_hash_func_ptr[E_sz_enum]) (string_view) = {
                                                            &Hash_Std_Hash,
                                                            &Hash_Ret_1,
                                                            &Hash_Ret_Len,
                                                            &Hash_Sum_Asci,
                                                            &Hash_Asci_Div_Len,
                                                            &Hash_Sha_256,
                                                            };

    ifstream fin;
    fin.open ("res_text.txt");

    string word = "";
    while (fin >> word)
    {
        string_view view_word = word;

        for (int i = 0; i < E_sz_enum; i++)
        {
            int pos = arr_of_hash_func_ptr[i] (view_word);
            hash_tables[i][pos].push_back (view_word);
        }
    }

    Make_File (hash_tables);

    return 0;
}

//=============================================================================

size_t Hash_Std_Hash (string_view elem)
{
    hash <string_view> hash_str;
    return (hash_str (elem)) % C_sz_table;
}

//-----------------------------------------------------------------------------

size_t Hash_Ret_1 (string_view elem)
{
    return 1;
}

//-----------------------------------------------------------------------------

size_t Hash_Ret_Len (string_view elem)
{
    return elem.size() % C_sz_table;
}

//-----------------------------------------------------------------------------

size_t Hash_Sum_Asci (string_view elem)
{
    int res = 0;

    for (int i = 0; i < elem.size(); i++)
    {
        res += (char) elem[i];
    }

    return res % C_sz_table;
}

//-----------------------------------------------------------------------------

size_t Hash_Asci_Div_Len (string_view elem)
{
    int res = 0;

    for (int i = 0; i < elem.size(); i++)
    {
        res += (char) elem[i];
    }

    return (res / elem.size()) % C_sz_table;
}

//-----------------------------------------------------------------------------

size_t Hash_Sha_256 (string_view elem)
{
    vector <unsigned long> block;

    block = convert_to_binary (elem);

    block = pad_to_512bits (block);

    block = resize_block (block);

    string_view res_hash = compute_hash (block);

    unsigned long long res = 0;
    for (int i = 0; i < res_hash.size(); i++)
    {
        res += ((unsigned long long) ((char) res_hash[i])) * (pow (2, i % 8));
        res %= C_sz_table;
    }

    return res;
}

//=============================================================================

void Dump (vector <list <string_view>> hash_table)
{
    for (int i = 0; i < C_sz_table; i++)
    {
        printf ("[%0.4d]: ", i);

//        list <string_view> :: iterator iter;                                            //}
//        for (iter = hash_table[i].begin(); iter != hash_table[i].end(); iter++)    //|
//        {                                                                          //| to see elements in each list
//            cout << (*iter) << " || ";                                             //|
//        }                                                                          //}

        cout <<  hash_table[i].size();                                               //} to see count of elems in each list

        printf ("\n");
    }
}

//=============================================================================

void Make_File (array <array <list <string_view>, C_sz_table>, E_sz_enum> hash_tables)
{
    FILE *fout = fopen ("output_exel.txt", "w");

    fprintf (fout, "NUMBER, STD, 1, LEN, SUM, SUM/LEN, SHA256\n");

    for (int i = 0; i < C_sz_table; i++)
    {
        fprintf (fout, "%d, ", i + 1);

        for (int k = 0; k < E_sz_enum; k++)
        {
            fprintf (fout, "%d, ", hash_tables[k][i].size());
        }

        fprintf (fout, "\n");
    }
}


//{============================================================================
//|                                 TESTS                                     ;
//}============================================================================
/*

int main ()
{
    vector <list <string_view>> hash_table (C_sz_table);

    ifstream fin;
    fin.open ("res_text.txt");

    string_view word = "";
    while (fin >> word)
    {
        int pos = My_Hash (word, *_TYPE TO TEST_*);
        hash_table[pos].push_back (word);
    }

    Dump (hash_table);

    return 0;
}

*/

