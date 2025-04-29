#include <chrono>
#include <iostream>
#include "stimtoy.hxx"
#include <thread>

using namespace std::chrono_literals;

int main() {
    stimtoy st;
    do {
        st.sallys_first_stim();
        std::cout << st.u32[0] << '\n';
        std::this_thread::sleep_for(100ms);
    } while (st.u32[0] != 0);
}
