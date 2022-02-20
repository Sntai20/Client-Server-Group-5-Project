#include <iostream>
#include <future>

using namespace std;

// Part of Example 1
void threadFunction1(); 

// Part of Example 2
class thread_object 
{
public:
    void operator()()
    {
        int count = 2;
        for (size_t i = 0; i < count; i++)
        {
            cout << "Thread using function"
                  " object as  callable\n";
        }
    }
}; // End of class thread_object

// Part of Example 3
int asyncFunction ();

// Part of Example 4
void asyncProducer(std::promise<int> &prom); 
// Part of Example 4
void asyncConsumer(std::future<int> &fut); 

/**
 * @brief This program uses the std::thread class provided by C++ for portability.
 * To run this program on Windows, Linux, and Mac the POSIX threads library or 
 * C pthreads library are not used. 
 * https://www.geeksforgeeks.org/multithreading-in-cpp/
 * 
 * @return int 
 */
int main()
{
    cout << "Thread Project starting.\n" << endl;
    
    cout << "To run this program on Windows, Linux, and Mac (portability) this program uses the std::thread class provided by C++. The POSIX threads library or C pthreads library are not used.\n" << endl;
    
    /** Example 1
     * @brief Create a threat object and pass the executing code from the callable object into the constructor of the object.
     * Start the thread using the function pointer.
     * 
     * @return thread 
     */
    thread t1 (threadFunction1);

    // Wait for t1 to finish.
    t1.join();

    // t1 has finished do other stuff.

    /** Example 2
     * @brief This thread is launched by using a function object as a callable.
     * Not sure why we need double parentheses, but it works. 
     * 
     * @return thread 
     */
    thread t2 (( thread_object() ));

    // Wait for t2 to finish.
    t2.join();

    // Example 3
    std::future<int> fut = std::async(asyncFunction);
    std::cout << "max = " << fut.get() << std::endl;

    // Example 4
    std::promise<int> prom;
    std::future<int> futureExample4 = prom.get_future();
    std::async(asyncProducer, std::ref(prom));
    std::async(asyncConsumer, std::ref(futureExample4));
    std::cout << "Async Producer-Consumer ended!" << std::endl;

    return 0;
}

/** Part of Example 1
 * @brief This is the function passed to the thread object.
 * 
 */
void threadFunction1()
{
    int count = 2;
    cout << "starting thread 1 ... " << endl;
    for (int i = 0; i < count; i++) {
        cout << "Thread using function"
               " pointer as callable\n";
    }
    cout << "end thread 1 ... " << endl;
} // End of void threadFunction1

/** Part of Example 3
 * @brief 
 * 
 * @return int 
 */
int asyncFunction()
{
    std::cout << "starting asyncFunction ... " << std::endl;
    int max = 0;
    for (int i = 0; i < 100000; ++i)
    {
        max += i;
    }
    std::cout << " Finished asyncFunction ..." << std::endl;
    return max;
}

/** Part of Example 4
 * @brief 
 * 
 * @param fut 
 */
void asyncConsumer(std::future<int> &fut)
{
    std::cout << "Got " << fut.get() << " from the producer ... "
        << std::endl;
}

/** Part of Example 4
 * @brief 
 * 
 * @param prom 
 */
void asyncProducer(std::promise<int> &prom)
{
    std::cout << " sending 5 to the consumer ... " << std::endl;
    prom.set_value (5);
}