#include "../rust/target/cxxbridge/synth/src/lib.rs.h"
#include <iostream>
#include <vector>

using namespace std;
int main(){

    auto synth = new_synth();
    std::cout << synth->next_sample() <<endl;
    synth->set_frequency(440.0);
    std::cout << synth->next_sample() <<endl;


    return 0;
}