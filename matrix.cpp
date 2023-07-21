#if false

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <algorithm>
#include "matrix.h"

namespace Math
{
    Matrix::Matrix(int rows, int cols, double val) : cols(cols), rows(rows)
    {
        vals = std::vector<double>(rows * cols, val);
        size = rows * cols;
    }

    Matrix::Matrix(int rows, int cols, const std::vector<double> &v)
    {
        if (rows * cols != v.size())
            throw std::invalid_argument("Row and column dimensions do not match input vector.");
        Matrix::cols = cols;
        Matrix::rows = rows;
        vals = v;
        size = rows * cols;
    }

    Matrix::Matrix(const std::vector<double> &v, bool isCol)
    {
        if (isCol)
        {
            cols = 1;
            rows = v.size();
        }
        else
        {
            cols = v.size();
            rows = 1;
        }

        vals = v;
        size = rows * cols;
    }

    Matrix::Matrix(const std::vector<std::vector<double>> &vv)
    {
        if (vv.size() == 0)
            throw std::invalid_argument("Nested vector must have values.");

        cols = vv[0].size();
        rows = vv.size();
        vals.reserve(cols * rows);

        for (int i = 0; i < rows; i++)
        {
            std::vector<double> v = vv[i];
            if (v.size() != cols)
                throw std::invalid_argument("Rows must be same length.");

            vals.insert(vals.end(), v.begin(), v.end());
        }
        size = rows * cols;
    }

    Matrix::Matrix(const Matrix &other)
    {
        cols = other.cols;
        rows = other.rows;
        vals = other.vals;
        size = other.size;
    }

    int Matrix::getCols() const
    {
        return cols;
    }

    int Matrix::getRows() const
    {
        return rows;
    }

    int Matrix::getSize() const
    {
        return size;
    }

    std::vector<double> Matrix::getVals() const
    {
        return vals;
    }

    double Matrix::get(int row, int col)
    {
        return vals[row * cols + col];
    }

    void Matrix::set(int row, int col, double val)
    {
        vals[row * cols + col] = val;
    }

    Matrix Matrix::generateRandom(int rows, int cols)
    {
        int size = rows * cols;
        std::vector<double> v(size, 0.0);
        for (int i = 0; i < size; i++)
            v[i] = static_cast<double>(rand()) / RAND_MAX;
        return Matrix(rows, cols, v);
    }

    Matrix Matrix::transpose() const
    {
        std::vector<double> v(size);
        for (int i = 0; i < cols; i++)
            for (int j = 0; j < rows; j++)
                v[i * cols + j] = vals[j * cols + i];

        return Matrix(cols, rows, v);
    }
    void Matrix::transposed()
    {
        std::vector<double> v(size);
        for (int i = 0; i < cols; i++)
            for (int j = 0; j < rows; j++)
                v[i * rows + j] = vals[j * cols + i];

        int temp = cols;
        cols = rows;
        rows = temp;
        vals = v;
    }

    void Matrix::print() const
    {
        for (int i = 0; i < size; i++)
        {
            std::string v = std::to_string(vals[i]);
            std::cout << v << " ";
            if ((i + 1) % cols == 0)
                std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    Matrix Matrix::applyFn(double (*fn)(double)) const
    {
        std::vector<double> v(size);
        for (int i = 0; i < size; i++)
            v[i] = fn(vals[i]);

        return Matrix(rows, cols, v);
    }

    void Matrix::applyFnHere(double (*fn)(double))
    {
        for (int i = 0; i < size; i++)
            vals[i] = fn(vals[i]);
    }

    double Matrix::operator[](int i) const
    {
        return vals[i];
    }

    double &Matrix::operator[](int i)
    {
        return vals[i];
    }

    Matrix &Matrix::operator+=(const Matrix &m)
    {
        if (rows != m.rows)
            throw std::invalid_argument("Height mismatch.");
        else if (cols != m.cols)
            throw std::invalid_argument("Width mismatch.");

        for (int i = 0; i < size; i++)
            vals[i] += m[i];

        return *this;
    }
    Matrix &Matrix::operator-=(const Matrix &m)
    {
        if (rows != m.rows)
            throw std::invalid_argument("Height mismatch.");
        else if (cols != m.cols)
            throw std::invalid_argument("Width mismatch.");

        for (int i = 0; i < size; i++)
            vals[i] -= m[i];

        return *this;
    }

    Matrix &Matrix::operator+=(const double &d)
    {
        for (int i = 0; i < size; i++)
            vals[i] += d;

        return *this;
    }
    Matrix &Matrix::operator-=(const double &d)
    {
        for (int i = 0; i < size; i++)
            vals[i] -= d;

        return *this;
    }
    Matrix &Matrix::operator*=(const double &d)
    {
        for (int i = 0; i < size; i++)
            vals[i] *= d;

        return *this;
    }
    Matrix &Matrix::operator/=(const double &d)
    {
        for (int i = 0; i < size; i++)
            vals[i] /= d;

        return *this;
    }

    Matrix operator+(Matrix mat1, const Matrix &mat2)
    {
        mat1 += mat2;
        return mat1;
    }
    Matrix operator-(Matrix mat1, const Matrix &mat2)
    {
        mat1 -= mat2;
        return mat1;
    }

    Matrix operator+(Matrix mat1, const double &d)
    {
        mat1 += d;
        return mat1;
    }

    Matrix operator-(Matrix mat1, const double &d)
    {
        mat1 -= d;
        return mat1;
    }

    Matrix operator*(Matrix mat1, const double &d)
    {
        mat1 *= d;
        return mat1;
    }

    Matrix operator/(Matrix mat1, const double &d)
    {
        mat1 /= d;
        return mat1;
    }

    std::string Matrix::toString() const
    {
        std::string s = "";
        for (int i = 0; i < size; i++)
        {
            std::string v = std::to_string(vals[i]);
            s += v + " ";
            if ((i + 1) % cols == 0)
                s += "\n";
        }

        return s;
    }

    std::ostream &operator<<(std::ostream &out, const Matrix &m)
    {
        out << m.toString();
        return out;
    }

    double dot(const Matrix &m1, const Matrix &m2)
    {
        std::vector<double> m1Vals = m1.getVals();
        std::vector<double> m2Vals = m2.getVals();

        if ((m1Vals.size() != m2Vals.size()) && (m1.getCols() != 1 || m2.getCols() != 1) && (m1.getRows() != 1 || m2.getRows() != 1))
            throw std::invalid_argument("Dot product must be performed between two column matrices or two row matrices of the same size");

        double sum = 0;
        for (int i = 0; i < m1Vals.size(); i++)
            sum += m1Vals[i] * m2Vals[i];

        return sum;
    }

    Matrix Matrix::iProd(Matrix m1, const Matrix &m2)
    {
        int m1Cols = m1.getCols();
        int m1Rows = m1.getRows();
        int m2Cols = m2.getCols();
        int m2Rows = m2.getRows();

        if (m1.getRows() != m2.getRows())
            throw std::invalid_argument("Dimension mismatch.");

        std::vector<double> v(m1Cols * m2Cols);

        // for (int i = 0; i < m1.getCols(); i++)
        //     for (int j = 0; j < m2.getCols(); j++)
        //         for (int k = 0; k < m1.getRows(); k++)
        //             v[i * m2.getCols() + j] += m1[k * m1.getCols() + i] * m2[k * m2.getCols() + j];

        threadPoolProcess([&](int start, int end)
                          {
                              for (int i = start; i < end; i++)
                                  for (int j = 0; j < m2Cols; j++)
                                      for (int k = 0; k < m1Rows; k++)
                                          v[i * m2Cols + j] += m1[i * m1Cols + k] * m2[k * m2Cols + j]; },
                          m1Cols);

        return Matrix(m1Cols, m2Cols, v);
    }

    Matrix Matrix::oProd(const Matrix &m1, const Matrix &m2)
    {
        int m1Cols = m1.getCols();
        int m1Rows = m1.getRows();
        int m2Cols = m2.getCols();
        int m2Rows = m2.getRows();

        if (m1.getCols() != m2.getCols())
            throw std::invalid_argument("Dimension mismatch.");

        std::vector<double> v(m1Rows * m2Rows);

        // std::vector<double> v(m1.getRows() * m2.getRows());
        // for (int i = 0; i < m1.getRows(); i++)
        //     for (int j = 0; j < m2.getRows(); j++)
        //         for (int k = 0; k < m1.getCols(); k++)
        //             v[i * m2.getRows() + j] += m1[i * m1.getCols() + k] * m2[j * m2.getCols() + k];

        threadPoolProcess([&](int start, int end)
                          {
                              for (int i = start; i < end; i++)
                                  for (int j = 0; j < m2Rows; j++)
                                      for (int k = 0; k < m1Cols; k++)
                                          v[i * m2Rows + j] += m1[i * m1Cols + k] * m2[j * m2Cols + k]; },
                          m1Rows);

        // debug comments incase i need them again
        // std::cout << m1[i * m1.getCols() + k] << "||" << m2[j * m2.getCols() + k] << " ";
        // std::cout << i << " " << j << " " << k << std::endl;

        return Matrix(m1Rows, m2Rows, v);
    }

    Matrix Matrix::hProd(Matrix m1, const Matrix &m2)
    {
        std::vector<double> m1Vals = m1.getVals();
        std::vector<double> m2Vals = m2.getVals();

        if (m1.getCols() != m2.getCols() || m1.getRows() != m2.getRows())
            throw std::invalid_argument("Hadamard product must be performed between two matrices of the same dimensions.");

        for (int i = 0; i < m1Vals.size(); i++)
            m1[i] *= m2Vals[i];

        return m1;
    }

    Matrix &Matrix::operator*=(const Matrix &m)
    {
        // if (cols != m.rows)
        //     throw std::invalid_argument("Dimension mismatch.");

        // std::vector<double> v(rows * m.cols);
        // for (int i = 0; i < rows; i++)
        //     for (int j = 0; j < m.cols; j++)
        //         for (int k = 0; k < m.rows; k++)
        //             v[i * m.cols + j] += vals[i * cols + k] * m[k * m.cols + j];

        // vals = v;
        // cols = m.cols;

        int mCols = m.cols;
        int mRows = m.rows;

        if (cols != mRows)
            throw std::invalid_argument("Dimension mismatch.");

        std::vector<double> v(rows * mCols);
        threadPoolProcess([&](int start, int end)
                          {
                              for (int i = start; i < end; i++)
                                  for (int j = 0; j < mCols; j++)
                                      for (int k = 0; k < mRows; k++)
                                          v[i * mCols + j] += vals[i * cols + k] * m[k * mCols + j]; },
                          rows);

        vals = v;
        cols = mCols;
        size = rows * cols;

        return *this;
    }

    void Matrix::simpleThreadProcess(std::function<void(int start, int end)> fn, int rows)
    {
        const int MAX_THREADS = Matrix::threadPool.getPoolSize();
        const int threadNum = std::min({rows, MAX_THREADS});
        const int block = std::max(rows / threadNum, 1);
        std::vector<std::thread> threads(threadNum);
        std::reference_wrapper funcRef = std::ref(fn);

        int start = 0;
        int end = block;

        for (int i = 0; i < threadNum - 1; i++)
        {
            threads[i] = std::thread(funcRef, start, end);
            start = end;
            end += block;
        }
        threads[threadNum - 1] = std::thread(funcRef, start, rows);

        for (int i = 0; i < threadNum; i++)
            threads[i].join();
    }

    Matrix Matrix::simpleThreaded(const Matrix &ogm, const Matrix &m)
    {
        int rows = ogm.getRows();
        int cols = ogm.getCols();
        int mCols = m.getCols();
        int mRows = m.getRows();

        if (ogm.getCols() != m.getRows())
            throw std::invalid_argument("Dimension mismatch.");

        std::vector<double> v(rows * m.getCols());

        simpleThreadProcess([&](const int &start, const int &end)
                            {
                                for (int i = start; i < end; i++)
                                    for (int j = 0; j < mCols; j++)
                                        for (int k = 0; k < mRows; k++)
                                            v[i * mCols + j] += ogm[i * cols + k] * m[k * mCols + j]; },
                            rows);

        return Matrix(rows, m.getCols(), v);
    }

    // make sure that fn is does not access same elements of a matrix for different blocks
    void Matrix::threadPoolProcess(std::function<void(int start, int end)> fn, int rows)
    {
        std::condition_variable event;
        std::mutex eventMutex;
        std::atomic<int> completedTasksCount(0);

        const int MAX_THREADS = Matrix::threadPool.getPoolSize();
        const int threadNum = std::min({rows, MAX_THREADS});

        int block = std::max(rows / threadNum, 1);

        int start = 0;
        int end = block;

        for (int i = 0; i < threadNum - 1; i++)
        {
            // std::cout << start << "-" << end << std::endl;
            Matrix::threadPool.enqueue([start, end, &fn, &eventMutex, &completedTasksCount, &event]
                                       {fn(start, end);
                                        {
                                            std::unique_lock<std::mutex> lock(eventMutex);
                                            completedTasksCount.fetch_add(1);
                                            event.notify_one();
                                        } });
            start = end;
            end += block;
        }
        // std::cout << start << "-" << end << std::endl;
        Matrix::threadPool.enqueue([start, rows, &fn, &eventMutex, &completedTasksCount, &event]
                                   {fn(start, rows);
                                        {
                                            std::unique_lock<std::mutex> lock(eventMutex);
                                            completedTasksCount.fetch_add(1);
                                            event.notify_one();
                                    } });

        {
            std::unique_lock<std::mutex> lock(eventMutex);
            event.wait(lock, [&completedTasksCount, threadNum]
                       { 
                            //std::cout << "completed " << completedTasksCount << " | goal " << threadNum << std::endl;
                            return completedTasksCount == threadNum; });
            event.notify_all();
        }
    }

    void multiply(std::vector<double> &v, const int &start, const int &end, const Matrix &ogm, const Matrix &m)
    {
        int cols = ogm.getCols();
        int mCols = m.getCols();
        int mRows = m.getRows();
        for (int i = start; i < end; i++)
            for (int j = 0; j < mCols; j++)
                for (int k = 0; k < mRows; k++)
                    v[i * mCols + j] += ogm[i * cols + k] * m[k * mCols + j];
    }

    Matrix Matrix::poolThreaded(const Matrix &ogm, const Matrix &m)
    {
        int rows = ogm.getRows();
        int cols = ogm.getCols();
        int mCols = m.getCols();
        int mRows = m.getRows();

        if (ogm.getCols() != m.getRows())
            throw std::invalid_argument("Dimension mismatch.");

        std::vector<double> v(rows * m.getCols());

        threadPoolProcess([&](int start, int end)
                          {
                              for (int i = start; i < end; i++)
                                  for (int j = 0; j < mCols; j++)
                                      for (int k = 0; k < mRows; k++)
                                          v[i * mCols + j] += ogm[i * cols + k] * m[k * mCols + j]; },
                          rows);

        return Matrix(rows, m.getCols(), v);
    }

    Matrix operator*(Matrix mat1, const Matrix &mat2)
    {
        mat1 *= mat2;
        return mat1;
    }

} // namespace Math

#endif