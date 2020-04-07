
//{============================================================================
//|                   REMOVE PUNCTUATION TO COUNT ONLY WORDS                  ;
//}============================================================================

#include <stdio.h>

//=============================================================================

int main ()
{
    FILE *fin  = fopen ("text.txt",     "r");
    FILE *fout = fopen ("res_text.txt", "w");

    char bad_chars[12] = {',', '!', '.', '\\', '/', '<', '>', '"', '\'', '-', ':', '?'};

    char elem = '\0';
    while ((elem = fgetc (fin)) != EOF)
    {
        bool ok = true;
        for (int i = 0; i < 12; i++)
        {
            if (elem == bad_chars[i])
            {
                ok = false;
            }
        }

        if (ok) fputc (elem, fout);
        else fputc (' ', fout);
    }

    return 0;
}
