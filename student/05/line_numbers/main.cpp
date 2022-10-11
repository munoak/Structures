#include <iostream>
#include<fstream>
#include<string>
#include <vector>

using namespace std;

int main()
{

            string f1;
            cout << "Input file: ";
            getline(cin, f1);
            string f2 ="";
            cout << "Output file: ";
            getline(cin, f2);

            // opening first file to read the content
            ifstream f1_object(f1);
            ofstream f2_object(f2);
            if (!f1_object)
            {
                cout << "Error! The file " << f1 << " cannot be opened." << endl;
                return EXIT_FAILURE;
            }
         else {
                int line_num = 0;
                string ch;
                while (getline(f1_object, ch)) {
                    ++line_num;
                    //getline(f1_object, ch);
                    f2_object  << line_num << " "<< ch << endl;

                }
            }
            // closing the files
            f1_object.close();
            f2_object.close();
            return 0;
        }
