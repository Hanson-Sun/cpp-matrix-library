#include <iostream>
#include <chrono>
#include "matrix.h"

#define TRACY_ENABLE ;

int main()
{
    Math::Matrix m1(3, 4, 1);
    Math::Matrix m2(2, 3, {1, 2, 3, 4, 5, 6});
    Math::Matrix m3(std::vector<double>({1.0, 2.0, 3.0}));
    Math::Matrix m4({1, 3, 4}, false);
    Math::Matrix m5({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    Math::Matrix m6(m1);
    Math::Matrix m7({{1, 2}, {4, 5}, {7, 8}});
    Math::Matrix m8({{1, 2, 3}, {4, 5, 6}});
// constructor test
#if false
    m1.print();
    m2.print();
    m3.print();
    m4.print();
    m5.print();
    m6.print();
#endif

#if true
    m7.transpose().print();
    m7.transposed();
    m7.print();
    m7.transposed();
    m7.print();
#endif

#if true
    (Math::Matrix({{1, 2}, {4, 5}}) * Math::Matrix({{1, 3}, {4, 6}})).print();
    (Math::Matrix({{1, 2}, {4, 5}, {7, 8}}) * Math::Matrix({{1, 2, 3}, {4, 5, 6}})).print();
    (Math::Matrix(std::vector<std::vector<double>>{{1}, {4}, {7}}) * Math::Matrix(std::vector<std::vector<double>>{{1, 2, 3}})).print();
    (Math::Matrix(std::vector<std::vector<double>>{{1, 2, 3}}) * Math::Matrix(std::vector<std::vector<double>>{{1}, {4}, {7}})).print();
#endif

#if true
    Math::Matrix::iProd(Math::Matrix({{1, 3}, {4, 6}}), Math::Matrix({{1, 2}, {4, 5}})).print();
    Math::Matrix::iProd(Math::Matrix({{1, 2}, {4, 5}, {7, 8}}), Math::Matrix({{1, 2}, {4, 5}, {7, 8}})).print();
    Math::Matrix::iProd(Math::Matrix({{1, 2, 3}, {4, 5, 6}}), Math::Matrix({{1, 2, 3 , 4}, {4, 5, 6, 7}})).print();
    Math::Matrix::iProd(Math::Matrix(std::vector<std::vector<double>>{{1, 2, 3}}),Math::Matrix(std::vector<std::vector<double>>{{1, 2, 3}})).print();
    Math::Matrix::iProd(Math::Matrix(std::vector<std::vector<double>>{{1}, {4}, {7}}),Math::Matrix(std::vector<std::vector<double>>{{1}, {4}, {7}})).print();
#endif

#if true
    Math::Matrix::oProd( Math::Matrix({{1, 2}, {4, 5}}), Math::Matrix({{1, 3}, {4, 6}})).print();
    Math::Matrix::oProd(Math::Matrix({{1, 2}, {4, 5}, {7, 8}}), Math::Matrix({{1, 4}, {4, 4}, {1, 8}})).print();
    Math::Matrix::oProd(Math::Matrix({{1, 2, 3}, {4, 5, 6}}), Math::Matrix({{1, 2, 3}, {4, 5, 6}, {4, 5, 6}})).print();
    Math::Matrix::oProd(Math::Matrix(std::vector<std::vector<double>>{{1, 2, 3}}), Math::Matrix(std::vector<std::vector<double>>{{1, 2, 3}})).print();
    Math::Matrix::oProd(Math::Matrix(std::vector<std::vector<double>>{{1}, {4}, {7}}),Math::Matrix(std::vector<std::vector<double>>{{1}, {4}, {7}})).print();
#endif

#if true
    Math::Matrix M1({{1, 2, 3}, {4, 5, 6}});
    Math::Matrix M2({{1, 2, 3}, {3, 4, 5}});

    Math::Matrix::hProd(M2, M1).print();

    Math::Matrix::hProd(M1, M2).print();
#endif

#if true
    for (int i = 0; i < 1; i++)
    {
        Math::Matrix M1({{1, 2}, {4, 5}, {7, 8}});
        Math::Matrix M2({{1, 2, 3}, {4, 5, 6}});

        Math::Matrix M3(512, 512, 2);
        Math::Matrix M4(512, 1, 2);

        int n = 10;

        std::cout << "begin multiplication" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < n; i++)
        {
            M1 *M2;
            M3 *M3;
            M3 *M4;
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << (duration.count() / n) << std::endl;
        std::cout << "end" << std::endl;
    }
#endif

#if false
    Math::Matrix M1t({{1, 2}, {4, 5}, {7, 8}});
    Math::Matrix M2t({{1, 2, 3}, {4, 5, 6}});

    Math::Matrix M3t(512, 512, 2);
    Math::Matrix M4t(512, 1, 2);

    int nt = 10;

    std::cout << "begin multiplication" << std::endl;
    auto startt = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < nt; i++)
    {
        Math::Matrix::simpleThreaded(M1t, M2t);
        Math::Matrix::simpleThreaded(M3t, M3t);
        Math::Matrix::simpleThreaded(M3t, M4t);
    }
    auto stopt = std::chrono::high_resolution_clock::now();
    auto durationt = std::chrono::duration_cast<std::chrono::microseconds>(stopt - startt);
    std::cout << (durationt.count() / nt) << std::endl;
    std::cout << "end" << std::endl;
#endif

#if false
for (int i = 0; i < 1; i++){
    Math::Matrix M1tt({{1, 2}, {4, 5}, {7, 8}});
    Math::Matrix M2tt({{1, 2, 3}, {4, 5, 6}});

    Math::Matrix M3tt(512, 512, 2);
    Math::Matrix M4tt(512, 1, 2);

    int ntt = 10;

    std::cout << "begin multiplication" << std::endl;
    auto starttt = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ntt; i++)
    {
        Math::Matrix::poolThreaded(M1tt, M2tt);
        Math::Matrix::poolThreaded(M3tt, M3tt);
        Math::Matrix::poolThreaded(M3tt, M4tt);
    }
    auto stoptt = std::chrono::high_resolution_clock::now();
    auto durationtt = std::chrono::duration_cast<std::chrono::microseconds>(stoptt - starttt);
    std::cout << (durationtt.count() / ntt) << std::endl;
    std::cout << "end" << std::endl;
}
#endif

#if false
    std::condition_variable event;
    std::mutex eventMutex;
    std::atomic<int> completedTasksCount(0);

    std::string s = "abc";
    Math::Matrix::threadPool.enqueue([&s, &completedTasksCount, &event]
                                     {
                    s[0] = 'A';
                    completedTasksCount.fetch_add(1);
                    event.notify_all(); });

    Math::Matrix::threadPool.enqueue([&s, &completedTasksCount, &event]
                                     {
                    s[1] = 'B';
                    completedTasksCount.fetch_add(1);
                    event.notify_all(); });

    Math::Matrix::threadPool.enqueue([&s, &completedTasksCount, &event]
                                     {
                    s[2] = 'C';
                    completedTasksCount.fetch_add(1); 
                    event.notify_all(); });

    {
        std::unique_lock<std::mutex> lock(eventMutex);
        event.wait(lock, [&completedTasksCount]
                   { 
                    std::cout << "completed " <<  completedTasksCount<< std::endl;
                    return completedTasksCount == 3; });

        event.notify_all();
    }

    std::cout << s << std::endl;
#endif



    return 0;
}