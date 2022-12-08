#include <iostream>
#include <fmt/format.h>

using namespace std;

int main(int argc, char** argv)
{
    cout << "hello world!" << endl;

fmt::print("Hello {}!", "world");

    return 0;
}
