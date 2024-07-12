#include <vector>
#include "CCircularBuffer.h"
#include "CCircularBufferExt.h"

using namespace std;

int main() {
    CCircularBufferExt<int> buf1;
    buf1.insert(buf1.begin(), {1, 2, 3, 4, 5});
    cout << buf1 << endl;
}
