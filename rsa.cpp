#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <sstream>

using namespace std;

long gcd (long x, long y)
{
    long a;
    while (true)
    {
        a = x % y;
        if (a == 0)
        {
            return y;
        }
        x = y;
        y = a;
    }
}

long int modularexp(long int m, long int n, int e)
{
    int x = 1;     
    m = m % n;
    if (m == 0)
    {
        return 0;
    } 
    while (e > 0)
    {
        if (e & 1)
        {
            x = (x * m) % n;
        }
        e = e >> 1; 
        m = (m * m) % n;
    }
    return x;
}

long decryptKey(int p, int q)
{
    long e = 65537;
    long l;
    l = ((p-1) * (q-1)) / (gcd(p-1, q-1));
    // 
    if (l <=65537)
    {
        cout << "Bad l value" << endl;
        exit(0);
    }
    // extended Euclidean
    long s = 0;
    long old_s = 1;
    long t = 1;
    long old_t = 0;
    long r = e;
    long old_r = l;
    while (r != 0)
    {
        long quotient = floor(old_r/r);
        long temp = r;
        r = old_r - quotient * r;
        old_r = temp;
        temp = s;
        s = old_s - quotient * s;
        old_s = temp;
        temp = t;
        t = old_t - quotient * t;
        old_t = temp;
    }
    long d = old_t;
    if (d < 0)
    {
        d += (p-1) * (q-1);
    }
    // bad p and q
    if (gcd(e,l) != 1)
    {
        cout << "Bad p and q" << endl;
        exit(0);
    }
    return d;
}
void decrypt(string inFile, string outFile, int p, int q)
{
    long key = decryptKey(p,q);
    long chunk;
    long m;
    ifstream ifile(inFile);
    ofstream ofile(outFile);
    // decrypt each encrypted chunk
    while (ifile >> chunk){
        m = modularexp(chunk, key, p * q);        
        int remainder = m % 100;
        int divisor = m / 100;
        string result = "";
        while (divisor>0)
        {
            if (remainder == 0){
                result += " ";
                remainder = divisor % 100;
                divisor /= 100;
            }
            else{
                remainder += 96;
                result +=remainder;
                
                remainder = divisor % 100;
                divisor = divisor / 100;
            }
        }
        remainder += 96;
        result += remainder;
        //reverse result string to be legible
        for (long unsigned int i = 0; i < result.length()/2;i++)
        {
            swap(result[i], result[result.length() - i - 1]);
        }
        ofile << result;
    }

}


int encrypt(ofstream &ifile, long int n, string message)
{
    int e = 65537;
    int x;
    long int m;
    // determine the value for x
    if (n >= 27)
    {
        x = (log(n/6))/(log(100));
    }
    else
    {
        return 0; 
    }
    // if the message is larger than x
    if (message.length() >= (long unsigned int)x)
    {
        for (long unsigned int j = 0; j < (message.length()/x);j++)
        {
            string result = ""; 
            m = 0;
            string chunk = message.substr(j*x,x); 
            // if there are less than x characters remaining
            if (chunk.length() < (long unsigned int)x)
            {
                for (long unsigned int i = 0; i < chunk.length();i++)
                {
                    char number[3];
                    int messNum;
                    if (chunk[i] >= 'a' && chunk[i] <= 'z')
                    {
                        messNum = (int)chunk[i] - 96;
                    }
                    else
                    {
                        messNum = 0;
                    }
                    snprintf(number,3,"%02d",messNum);
                    string add(number);
                    result += add;
                }
                for (long unsigned int i = 0; i < x - chunk.length(); i++)
                {
                    string zeros = "00";
                    result += zeros;
                }
            }
            //create an int by changing each character in message to digits
            else if (chunk.length() == (long unsigned int) x)
            {
                for (int i = 0; i < x;i++)
                {
                    char number[3];
                    int messNum;
                    if (chunk[i] >= 'a' && chunk[i] <= 'z')
                    {
                        messNum = (int)chunk[i] - 96;
                    }
                    else
                    {
                        messNum = 0;
                    }
                    snprintf(number,3,"%02d",messNum);
                    string add(number);
                    result += add;
                }
            }
            stringstream ss;
            ss << result;
            ss >> m;
            // create encrypted message through modular exponentiation
            long int c = modularexp(m,n,e);
            ifile << c << " ";
        }
    }
    else
    {
        string result = "";
        m = 0;
        for (long unsigned int i = 0; i < message.length();i++)
        {
            char number[3];
            int messNum = (int)message[i] - 96;
            snprintf(number,3,"%02d",messNum);
            string add(number);
            result += add;
        }
        for (long unsigned int i = 0; i < x - message.length(); i++)
        {
            string zeros = "00";
            result += zeros;
        }
        stringstream ss;
        ss << result;
        ss >> m;
        // create encrypted message through modular exponentiation
        int c = modularexp(m,n,e);
        ifile << c << " ";
    }
    return 1;
}


int main (int argc, char *argv[])
{
    string inCommand, inputFile, outputFile, message;
    // multiply p and q to get n 
    int p = atoi(argv[1]);
    int q = atoi(argv[2]);
    long int n = p*q;
    bool working = true;
    while (working)
    {
        cout << "What is your command:" << endl;
        cin >> inCommand;
        // stop program
        if (inCommand == "EXIT")
        {
            return 1;
        }
        // decrypt message with p and q from inputfile to output file
        else if (inCommand == "DECRYPT")
        {
            cin >> inputFile >> outputFile;
            decrypt(inputFile,outputFile, p , q);
        }
        // encrypt a message onto textfile using given n
        else if (inCommand == "ENCRYPT")
        {
            cin >> inputFile >> n;
            string sentenceMess;
            getline(cin, sentenceMess);
            stringstream ss(sentenceMess);
            int i = 0;
            ofstream ifile;
            ifile.open(inputFile, ofstream::trunc);
            while (ss >> message)
            {
                if (i > 0)
                {
                    message = " " + message;
                    int result = encrypt(ifile,n,message);
                    if (result == 0)
                    {
                        working = false;
                        break;
                    }
                    i++;
                }
                else
                {
                    int result = encrypt(ifile,n,message);
                    if (result == 0)
                    {
                        working = false;
                        break;
                    }
                }
                i++;
            }
        }
        else 
        {
            return -1;
        }
    }
    return 0;
}

