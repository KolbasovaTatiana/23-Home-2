#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

template <typename t>
class Matrix 
{
private:
    t **matr;
    int str;
    int col;
    
public:
    
    Matrix ()                           //пустая матрица
    {
        matr = 0;
        str = 0;
        col = 0;
    }   
    static Matrix NullMatrix(int N, int M) {    //нулевая
        t **matrix = new t *[N];
        for (int i = 0; i < N; ++ i)
        {
            matrix[i] = new t [M];
            for (int j = 0; j < M; ++ j)
                matrix[i][j] = 0;
        }
        return matrix;
    }
        static Matrix EdMatrix(int N) {         //единичная
        t **matrix = new t *[N];
        for (int i = 0; i < N; ++ i)
        {
            matrix[i] = new t[N];
            for (int j = 0; j < N; ++ j)
                matrix[i][j] = (i == j);
        }
        return matrix;
    }
    Matrix (int N, int M)           //матрица заданного размера
    {
        str = N;
        col = M;
        matr = new t *[str];
        for (int i = 0; i < str; ++ i)
        {
            matr[i] = new t[col];
        }
    }        
    Matrix(const string& name)     //матрица из файла
    {
        ifstream file(name);
        if (file.is_open())
        {
            file >> str >> col;
            matr = new t*[str];
            for (int i = 0; i < str; ++i)
            {
                matr[i] = new t [col];
                for (int j = 0; j < col; ++j)
                    file >> matr[i][j];
            }
            file.close();
        }
        else 
        {
            cerr << "File cannot be opened.";
        }   
    }

    Matrix(const Matrix &other)         //конструктор копирования
    {
        this->str = other.str;
        this->col = other.col;
        this->matr = new t *[other.str];
        for (int i = 0; i < other.str; ++ i) 
        {
            this->matr[i] = new t[other.col];
            for (int j = 0; j < other.col; ++j)
                this->matr[i][j] = other.matr[i][j];
        }
    }    
    ~Matrix()                           //деструkтор
    {
        for (int i = 0; i < str; ++i)
            delete[] matr[i];
        delete[] matr;
    }
    void inputMatrix()                  //ввод с косоли
    {
        cout << "Input matrix: " << str << " rows, " << col << " columns." << endl;
        for (int i = 0; i < str; ++i)
        {
            for (int j = 0; j < col; ++j)
                scanf ("%lf", & matr[i][j]);
        }
        cout << "Matrix created." << endl;
    }
    friend ostream& operator <<(ostream& os, Matrix& obj)
    {
        for (int i = 0; i < obj.str; ++i)
        {
            for (int j = 0; j < obj.col; ++j)
                os << obj.matr[i][j] << "  ";
            os << endl;
        }
        return os;
    }
    friend istream& operator >>(istream& in, Matrix& obj)
    {
        cout << "Enter nuber of rows and columns:  ";
        in >> obj.str >> obj.col;
        obj.matr = new t *[obj.str];
        for (int i = 0; i < obj.str; ++i)
        {
            obj.matr[i] = new t[obj.col];
            for (int j = 0; j < obj.col; ++j)
                in >> obj.matr[i][j];
        }
        return in;
    }
    friend ofstream& operator <<(ofstream& ofs, Matrix& obj)
    {
        for (int i = 0; i < obj.str; ++i)
        {
            for (int j = 0; j < obj.col; ++j)
                ofs << obj.matr[i][j] << "  ";
            ofs << endl;
        }
        return ofs;
    }
    friend ifstream& operator >>(ifstream& ifs, Matrix& obj)
    {
        ifs >> obj.str >> obj.col;
        obj.matr = new t[obj.str];
        for (int i = 0; i < obj.str; ++i)
        {
            obj.matr[i] = new t[obj.col];
            for (int j = 0; j < obj.col; ++j)
                ifs >> obj.matr[i][j];
        }
        return ifs;
    }

    const Matrix operator *(const Matrix &other)
    {
        if (this->col != other.str)
            throw "The number of columns of the first matrix is not equal to the number of rows of the second. The operation cannot be completed.";
        Matrix z(this->str,other.col);
        int a;
        for (int i = 0; i < this->str; ++i)
        {
            for (int j = 0; j < other.col; ++j)
            {
                a = 0;
                for (int n = 0; n < this->col; ++n)
                {
                    a += this->matr[i][n]*other.matr[n][j];
                }
                z.matr[i][j] = a;
            }
        }
        return z;
    }
    const Matrix operator *(t skal)
    {
        Matrix z(*this);
        for (int i = 0; i < this->str; ++i)
        {
            for (int j = 0; j < this->col; ++j)
            {
                this->matr[i][j] = this->matr[i][j] * skal;
            }
        }
        return z;
    }
    const Matrix operator +(const Matrix &other)
    {
        Matrix z(*this);
        if (this->str != other.str || this->col != other.col)
            throw "Matrices have different dimensions!";
        for (int i = 0; i < this->str; ++i)
        {
            for (int j = 0; j < this->col; ++j)
            {
                z.matr[i][j] = this->matr[i][j] + other.matr[i][j];
            }
        }
        return z;
    }
    const Matrix operator -(const Matrix &other)
    {
        Matrix z(*this);
        if (this->str != other.str || this->col != other.col)
            throw "Matrices have different dimensions!";
        for (int i = 0; i < this->str; ++i)
        {
            for (int j = 0; j < this->col; ++j)
            {
                z.matr[i][j] = this->matr[i][j] - other.matr[i][j];
            }
        }
        return z;
    }
    Matrix operator !() {
        Matrix A(str, col);
        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < col; ++j) {
                A.matr[i][j] = matr[i][j];
            }
        }
        if (str != col) {
            throw "The matrix is not square";
        }
        else {
            double determinant = A.determinant();
            if (determinant == 0)
                throw "The matrix is ​​degenerate";
            else {
                Matrix B = A.MatrixDopolnenii();
                B.transposition();
                Matrix C = B * (1/determinant);
                cout << "The inverse matrix was successfully calculated" << endl;
                return C;
            }
        }
    }
    bool operator ==(const Matrix &other)
    {
        if (this->col != other.col || this->str != other.str)
            return false;
        for (int i = 0; i < this->str; ++i)
        {
            for (int j = 0; j < this->col; ++j)
            {
                if (this->matr[i][j] != other.matr[i][j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator ==(t skal)
    {
        Matrix a(this->str,this->col,skal);

        for (int i = 0; i < this->str; ++i)
        {
            for (int j = 0; j < this->col; ++j)
            {
                if (this->matr[i][j] != a[i][j])
                    return false;  
            }
        }
        return true;
    }
    bool operator !=(const Matrix &other)
    {
        if (this->str != other.str || this->col != other.col)
            return true;
        for (int i = 0; i < this->str; ++i)
        {
            for (int j = 0; j < this->col; ++j)
            {
                if (this->matr[i][j] != other.matr[i][j])
                    return true;
            }
        }
        return false;
    }
    bool operator !=(t skal)
    {
        Matrix a(this->str,this->col,skal);
        for (int i = 0; i < this->str; ++i)
        {
            for (int j = 0; j < this->col; ++j)
            {
                if (this->matr[i][j] != a[i][j])
                    return true;  
            }
        }
        return false;
    }
    Matrix& operator=(const Matrix& matrix) { //оператор присвоения
		if (matr != nullptr) {
			for (int i = 0; i < str; ++i) {
				delete[] matr[i];
			}
			delete[] matr;
		}
		str = matrix.str;
		col = matrix.col;
		matr = new t*[str];
		for (int i = 0; i < str; ++i) {
			matr[i] = new t[col];
			for (int j = 0; j < col; ++j) {
				matr[i][j] = matrix.matr[i][j];
			}
		}
		return *this;
    }
    
    int GetCol () {                     //метод возвращающий количество колонок
        return col;
    }    
    int GetStr () {                     //метод возвращающий количество строк
        return str;
    }        
    t* operator [] (int index)     //перегрузка оператора [] для возвращения строки
    {
        return getRow (index);
    }
    t* getRow (int index)
    {
        if (index >= 0 && index < str){
            return matr[index];
        }
        return 0;
    }
    t* getColumn (int index)
    {
        if (index < 0 || index >= col)
            return 0;
        double * c = new double [str];
        for (int i = 0; i < str; ++ i)
            c[i] = matr[i][index];
        return c;
    }  

    void swapRows (int index1, int index2)                     //First  elemental
    {
        if (index1-1 < 0 || index2-1 < 0 || index1 > str || index2 > str)
            throw "Invalid row number.";
        for (int i = 0; i < col; ++ i)
            swap (matr[index1-1][i], matr[index2-1][i]);
    }
    void skalRow (int index, double skal)                      //Second elemental
    {
        if (index <= 0 || index > str)
            throw "Invalid row number.";
        for (int i = 0; i < col; ++i)
        {
            matr[index-1][i] = matr[index-1][i]*skal;
        }
    }
    void skaladdRows (int index1, int index2, double skal = 1) //Third  elemental
    {
        if (index1 <= 0 || index2 <= 0 || index1 > str || index2 > str)
            throw "Invalid row number.";
        for (int i = 0; i < col; ++i)
        {
            matr[index2-1][i] = matr[index2-1][i] + (matr[index1-1][i]*skal);
        }    
    }
    void transposition() {
        t** result = new t * [col];
        for (int i = 0; i < col; ++i) {
            result[i] = new t[str];
            for (int j = 0; j < str; ++j) {
                result[i][j] = matr[j][i];
            }
        }
        for (int i = 0; i < str; ++i) 
            delete[] matr[i];
        delete[] matr;
        int curr = str;
        str = col;
        col = curr;
        matr = result;
    }
    
    double determinant() {
        if (str != col) {
            throw "Not possible to calculate the determinant";
        }
        else if (str == 1) {
            return matr[0][0];
        }
        else if (str == 2) {
            return matr[0][0] * matr[1][1] - matr[1][0] * matr[0][1];
        }
        else {
            double determinant = 0;
            Matrix minor(str - 1, col - 1);
            for (int i = 0; i < col; ++i) {
                for (int j = 1; j < str; ++j) {
                    int k = 0;
                    for (int l = 0; l < col; ++l) {
                        if (l != i) {
                            minor.matr[j - 1][k] = matr[j][l];
                            k++;
                        }
                    }
                }
                if (i%2 == 0)
                    determinant += matr[0][i] * minor.determinant();
                else
                    determinant += -1 * matr[0][i] * minor.determinant();
            }
            return determinant;
        }
    }
    double dopolnenie(int n, int m) {
        Matrix A(str - 1, col - 1);
        int x, y = 0;
        for (int i = 0; i < (str - 1); ++i) {
            if (i == n - 1)
                x = 1;
            for (int j = 0; j < (str - 1); ++j) {
                if (j == m - 1) {
                    y = 1;
                }
                A.matr[i][j] = matr[i + x][j + y];
            }
            y = 0;
        }
        int sign;
        if ((n + m) % 2 == 0) 
            sign = 1;
        else 
            sign = -1;
        return sign * A.determinant();
    }
    Matrix MatrixDopolnenii() {
        Matrix A(str, col);
        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < col; ++j) 
                A.matr[i][j] = matr[i][j];
        }
        Matrix result(str, col);
        if (str != col) {
            throw "The matrix is not square";
        }
        else {
            for (int i = 0; i < str; ++i) {
                for (int j = 0; j < col; ++j) 
                    result.matr[i][j] = A.dopolnenie(i + 1, j + 1);
            }
        }
        return result;
    }

};

int main() {

    Matrix<int> a;
    cin >> a;
    cout << a;
    a.transposition();
    cout << a;
    try 
    {
        double det_a;
        det_a = a.determinant();
        cout << det_a << endl;
    }
    catch (const char* error_message)
    {
        cout << error_message << endl;
    }
    try 
    {
        Matrix<int> not_a = !a;
        cout << not_a << endl;
    }
    catch (const char* error_message)
    {
        cout << error_message << endl;
    }

    Matrix<int> b("input.txt");
    cout << b;
    try
    {
        Matrix<int> c = a+b;
        cout << c;
    }
        catch (const char* error_message)
    {
        cout << error_message << endl;
    }
    try
    {
        Matrix<int> d = a-b;
        cout << d;
    }
        catch (const char* error_message)
    {
        cout << error_message << endl;
    }
    try
    {
        Matrix<int> e = a*b;
        cout << e;
    }
        catch (const char* error_message)
    {
        cout << error_message << endl;
    }
    try
    {
        Matrix<int> f = a+b;
        cout << f;
    }
        catch (const char* error_message)
    {
        cout << error_message << endl;
    }
    ofstream file("output.txt");
	file << a;
	cout << "Matrix is written to the file";
	cout << endl;
}
    

