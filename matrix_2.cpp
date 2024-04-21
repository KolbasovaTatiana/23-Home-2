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
            cerr << "File cannot be opened."
        }   
    }
    
    /*Matrix (ifstream& in)               
    {
        int count_numbers = 0; //количество чисел в матрице
        int curr;              //временная переменная

        while (!in.eof()) {
            in >> curr;        //пробегаемся по числам файла
            ++count_numbers;
        }

        in.seekg(0, ios::beg); //возврат каретки на 0 символ файла
        in.clear(); 

        int count_space = 0;
        char symbol;
        while (!in.eof()) {
            
            in.get(symbol);   //считываем посимвольно файл
            if (symbol == '\n') 
                break;
            if (symbol == ' ') 
                ++count_space;    
        }

        in.seekg(0, ios::beg);
        in.clear();

        col = count_space+1;
        str = count_numbers / col;

        matr = new t *[str];
        for (int i = 0; i < str; ++i) {
            matr[i] = new t[col];
            for (int j = 0; j < col; ++j)
                in >> matr[i][j];
        }
    }*/
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
    /*void printMatrix()                  //вывод на консоль
    {       
        for (int i = 0; i < str; ++i) {
            for (int j = 0; j < col; ++j) {
                printf("%2.2lf ", matr[i][j]);
            }
            puts ("");
        }
        
    }*/
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
    
    /*friend ofstream& operator << (ofstream& potok, const Matrix& a)
    {
        for (int i = 0; i < a.str; ++i)
        {
            for (int j = 0; j < a.col; ++j)
                potok << a.matr[i][j] << ' ';
            if (i+1 != a.str)
                potok << '\n';
        }
        return potok;
    }
    */
};

int main() {

    //Matrix b(3,3,1);
    Matrix<int> f(3,3);
    Matrix<int> a;
    cin >> a;
    cout << a;

    /*ifstream file1("input_matr.txt");
    Matrix z(file1);
    z.printMatrix();
    file1.close();
    
    ofstream file2("output_matr.txt");
    file2 << a << endl;
    file2.close();

    //cout << (b==f) << endl;
    //cout << (b!=f) << endl;

    try
    {
      //Matrix c = a*b;
      c.printMatrix();     
    }
    catch (const char* error_message)
    {
        cout << error_message << endl;
    }
    try
    {
      Matrix q = a+f;
      q.printMatrix();  
    }
    catch (const char* error_message)
    {
        cout << error_message << endl;
    }
    try
    {
      Matrix p = a-f;
      p.printMatrix();  
    }
    catch (const char* error_message)
    {
        cout << error_message << endl;
    }
    try
    {
        f.swapRows(2,3);     
    }
    catch (const char* error_message)
    {
        cout << error_message << endl;
    }
    try
    {
        f.skalRow(2,3);     
    }
    catch (const char* error_message)
    {
        cout << error_message << endl;
    }
    try
    {
        f.skaladdRows(1,2,3);     
    }
    catch (const char* error_message)
    {
        cout << error_message << endl;
    }*/
}
