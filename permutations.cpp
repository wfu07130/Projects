#include <string>
#include <iostream>

void helper(std::string in, int currLen)
{
    if (currLen == (int)(in.length()))
    {
        std::cout << in << std::endl;
        return;
    }
    else
    {
        for (int i = currLen; i < (int)(in.length()); i++)
        {
            std::swap(in[currLen],in[i]);
            helper(in, currLen+1);
            std::swap(in[currLen],in[i]);
        }
    }
}

void permutations(std::string in)
{
    helper(in, 0);
}