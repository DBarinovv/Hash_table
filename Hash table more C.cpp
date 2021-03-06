
//{============================================================================
//|                                                                           ;
//|                COMPARING HASH FUNCTIONS USING HASH TABLES                 ;
//|                                                                           ;
//|                                                     (c) Barinov Denis     ;
//}============================================================================

#include "TxLib.h"

//=============================================================================
//                                INCLUDES                                    ;
//=============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <sys\stat.h>
#include <ctime>

#include <list>
#include <array>

#include <iostream>
#include <algorithm>

#include "List.h"

//=============================================================================
//                                  CONSTANS                                  ;
//=============================================================================

const int C_sz_table = 700;

//-----------------------------------------------------------------------------

struct string_t
{
    char *str;
    int len;
};

//=============================================================================
//                                 PROTOTYPE                                  ;
//=============================================================================

int Find_Sz_File (char *fin);

int Number_Of_Lines (const int sz_file, const char *buf);

string_t *Make_Arr_Of_Words (char *file, int *cnt_of_lines);

//-----------------------------------------------------------------------------

uint32_t Hash_Xor (string_t elem);

//=============================================================================
//=============================================================================


int main ()
{
    int start = clock();
    int cnt_of_lines = 0;
    string_t *strings_arr = Make_Arr_Of_Words ("words.txt", &cnt_of_lines);

    list_t hash_table[C_sz_table + 1];
    for (int i = 0; i < C_sz_table; i++)
    {
        hash_table[i] = Constructor (C_size_of_array);
    }

    for (int i = 0; i < cnt_of_lines; i++)
    {
        int pos = Hash_Xor (strings_arr[i]);
        Insert_End (&hash_table[pos], strings_arr[i].str);
    }

    char word[15] = "aaaaaaaaaaaaaa";  // 15 letters

    for (int i = 0; i < 100000000; i++)
    {
        word[i % 15] = (word[i % 15] + i) % 26 + 97;  // make random letter
        int pos = Hash_Xor ({word, 15});

        Find (hash_table[pos], word);
    }

    printf ("TIME = [%d]\n", clock() - start);

    return 0;
}

//=============================================================================

int Find_Sz_File (char *fin)

{
    struct stat text = {};

    stat (fin, &text);

    return text.st_size;
}

//-----------------------------------------------------------------------------

int Number_Of_Lines (const int sz_file, const char *buf)
{
    int cnt = 0;

    for (int i = 0; i < sz_file - 1; i++)
    {
        if (*(buf + i) == '\n')  cnt++;
    }

    return cnt;
}

//-----------------------------------------------------------------------------

string_t *Make_Arr_Of_Words (char *file, int *cnt_of_lines)
{
    int sz_file = Find_Sz_File (file);
    char *buf = (char *) calloc (sz_file + 2, sizeof (char));
    FILE *fin = fopen (file, "r");
    fread (buf, sizeof (char), sz_file, fin);
    *cnt_of_lines = Number_Of_Lines (sz_file, buf) + 1;
    string_t *strings_arr = (string_t *) calloc (*cnt_of_lines, sizeof (string_t));

    int pos  = -1;
    int line = -1;

    while (pos < sz_file - 1 && line < *cnt_of_lines - 1)
    {
        if (buf[pos] == '\0' || buf[pos] == '\n')
        {
            buf[pos] = '\0';

            line++;

            strings_arr[line].str = (buf + pos + 1);

            if (strings_arr[line].str - strings_arr[line - 1].str == 1 ||
                strings_arr[line].str - strings_arr[line - 1].str == 0)
            {
                strings_arr[line - 1].len = 0;
            }
            else
                strings_arr[line - 1].len = strings_arr[line].str - strings_arr[line - 1].str - 2;
        }

        pos++;
    }

    if (buf + pos - strings_arr[line].str == 1 ||
        buf + pos - strings_arr[line].str == 0)
    {
        strings_arr[line].len = 0;
    }
    else
    {
       strings_arr[line].len = buf + pos - strings_arr[line].str - 1;
    }

    return strings_arr;
}

//=============================================================================

uint32_t Hash_Xor (string_t elem)
{
    uint32_t res = 0;
    int bit = 0;

    for (int i = 0; i < elem.len; i++)
    {
        res ^= elem.str[i];
        bit = (res >> 31) & 1;
        res <<= 1;
        res |= bit;
    }

    return res % C_sz_table;
}
