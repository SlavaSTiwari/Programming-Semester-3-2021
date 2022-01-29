#pragma once

#include<string>

class Complex {
private:
    double real, imag;
public:
    // CONSTRUCTORS:
    Complex() {
        real = 0;
        imag = 0;
    }
    Complex(double r) {
        real = r;
        imag = 0;
    }
    Complex(double r, double i) {
        real = r;
        imag = i;
    }
    // GETTERS:
    double GetReal() {
        return this->real;
    }
    double GetImag() {
        return this->imag;
    }
    //SETTERS:
    void SetReal(double r) {
        this->real = r;
    }
    void SetImag(double i) {
        this->imag = i;
    }

    // METHODS:
    void Print() const {
        if (imag > 0) {
            std::cout << this->real << "+" << this->imag << "i" << std::endl;
        }
        else {
            std::cout << this->real << this->imag << "i" << std::endl;
        }
    }

    std::string toString() const {
        if (imag > 0) {
            return std::to_string(this->real) + "+" + std::to_string(this->imag) + "i";
        }
        else {
            return std::to_string(this->real) + std::to_string(this->imag) + "i";
        }
    }

    //OPERATOR OVERLOADING:
    Complex operator + (const Complex& obj) {
        Complex temp;
        temp.real = this->real + obj.real;
        temp.imag = this->imag + obj.imag;
        return temp;
    }

    Complex operator - (const Complex& obj) {
        Complex temp;
        temp.real = this->real - obj.real;
        temp.imag = this->imag - obj.imag;
        return temp;
    }

    Complex operator * (const Complex& obj) {
        Complex temp;
        temp.real = (this->real * obj.real) - (this->imag * obj.imag);
        temp.imag = (this->real * obj.imag) + (this->imag * obj.real);
        return temp;
    }
    bool operator == (const Complex& obj) const {
        if (this->real == obj.real && this->imag * obj.imag) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator > (const Complex& obj) const {
        if ((this->real * this->real) + (this->imag * this->imag) > (obj.real * obj.real) + (obj.imag * obj.imag)) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator < (const Complex& obj) const {
        if ((this->real * this->real) + (this->imag * this->imag) < (obj.real * obj.real) + (obj.imag * obj.imag)) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator ! () {
        if (this == nullptr) {
            return true;
        }
        return false;
    }
};

std::ostream& operator <<(std::ostream& os, const Complex& Obj) {
    os << Obj.toString();
    return os;
}

std::string random_name() {

    int c;
    std::string name("");
    char cons[] = "bcdfghjklmnpqrstwvxyz";
    char vow[] = "aeiou";

    for (c = 0; c < 3; c++) {
        name += cons[rand() % 21];
        name += vow[rand() % 5];
    }

    return name;
}

class Student {
private:
    std::string First_name;
    std::string Last_name;
    std::string Student_ID;
    std::string B_date;

public:
    // Constructors:
    Student() {
        First_name = "";
        Last_name = "";
        Student_ID = "0000000000"; // Always 10 characters long.
        B_date = "0000";
    }
    Student(std::string F_name, std::string L_name, std::string b_date, std::string Stud_ID) {
        First_name = F_name;
        Last_name = L_name;
        Student_ID = Stud_ID; // Always 10 characters long.
        B_date = b_date;
    }
    Student(std::string F_name, std::string type)
    {
        First_name = F_name;
        if (type == "Random")
        {
            Last_name = random_name();
            B_date = std::to_string(rand() % 30 + 1985);
            Student_ID = std::to_string(rand() % 8999999 + 1000000);
        }
        else
        {
            Last_name = "";
            Student_ID = "0000000000"; // Always 10 characters long.
            B_date = "0000";
        }
        
    }
    // GETTERS:
    std::string Get_First_name() const {
        return First_name;
    }
    std::string Get_Last_name() const {
        return Last_name;
    }
    std::string Get_Student_ID() const {
        return Student_ID;
    }
    std::string Get_B_date() const {
        return B_date;
    }
    // SETTERS:
    void Set_First_name(std::string f) {
        First_name = f;
    }
    void Set_Last_name(std::string l) {
        Last_name = l;
    }
    void Set_Student_ID(std::string id) {
        Student_ID = id;
    }
    void Set_B_date(std::string b_date) {
        B_date = b_date;
    }
    //Misc~
    void Print() const {
        std::cout << Student_ID << ": " << First_name << " " << Last_name << ", " << B_date << std::endl;
    }

    std::string toString() const {
        return Student_ID + ": " + First_name + " " + Last_name + ", " + B_date;
    }

    void Randomize() {
        First_name = random_name();
        Last_name = random_name();
        B_date = std::to_string(rand() % 30 + 1985);
        Student_ID = std::to_string(rand() % 8999999 + 1000000);
    }

    bool operator == (Student obj) const {
        if (this->Get_First_name() == obj.Get_First_name() && this->Get_Last_name() == obj.Get_Last_name() && this->Get_B_date() == obj.Get_B_date() && this->Get_Student_ID() == obj.Get_Student_ID()) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator > (Student obj) const {
        if (this->Get_Student_ID() > obj.Get_Student_ID()) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator < (Student obj) const {
        if (this->Get_Student_ID() < obj.Get_Student_ID()) {
            return true;
        }
        else {
            return false;
        }
    }

    void operator = (const Student& obj) {
        this->First_name = obj.Get_First_name();
        this->Last_name = obj.Get_Last_name();
        this->B_date = obj.Get_B_date();
        this->Student_ID = obj.Get_Student_ID();
    }

    bool operator ! () {
        if (this == nullptr) {
            return true;
        }
        return false;
    }

};

std::ostream& operator << (std::ostream& os, const Student& Obj) {
    os << Obj.toString();
    return os;
}

class Teacher {
private:
    std::string First_name;
    std::string Last_name;
    std::string Teacher_ID;
    std::string B_date;

public:
    // Constructors:
    Teacher() {
        First_name = "";
        Last_name = "";
        Teacher_ID = "0000 000000"; // Always 10 characters long.
        B_date = "0000";
    }
    Teacher(std::string F_name, std::string L_name, std::string b_date, std::string Teach_ID) {
        First_name = F_name;
        Last_name = L_name;
        Teacher_ID = Teach_ID; // Always 10 characters long.
        B_date = b_date;
    }

    std::string Get_First_name() const {
        return First_name;
    }
    std::string Get_Last_name() const {
        return Last_name;
    }
    std::string Get_Teacher_ID() const {
        return Teacher_ID;
    }
    std::string Get_B_date() const {
        return B_date;
    }
    // SETTERS:
    void Set_First_name(std::string f) {
        First_name = f;
    }
    void Set_Last_name(std::string l) {
        Last_name = l;
    }
    void Set_Teacher_ID(std::string id) {
        Teacher_ID = id;
    }
    void Set_B_date(std::string b_date) {
        B_date = b_date;
    }
    //Misc~
    void Print() const {
        std::cout << Teacher_ID << ": " << First_name << " " << Last_name << ", " << B_date << std::endl;
    }

    std::string toString() const {
        return Teacher_ID + ": " + First_name + " " + Last_name + ", " + B_date;
    }

    void Randomize() {
        First_name = random_name();
        Last_name = random_name();
        B_date = std::to_string(rand() % 30 + 1985);
        Teacher_ID = std::to_string(rand() % 8999999 + 1000000);
    }

    bool operator == (Teacher obj) const {
        if (this->Get_First_name() == obj.Get_First_name() && this->Get_Last_name() == obj.Get_Last_name() && this->Get_B_date() == obj.Get_B_date() && this->Get_Teacher_ID() == obj.Get_Teacher_ID()) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator > (Teacher obj) const {
        if (this->Get_Teacher_ID() > obj.Get_Teacher_ID()) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator < (Teacher obj) const {
        if (this->Get_Teacher_ID() < obj.Get_Teacher_ID()) {
            return true;
        }
        else {
            return false;
        }
    }

    void operator = (Teacher obj) {
        this->First_name = obj.Get_First_name();
        this->Last_name = obj.Get_Last_name();
        this->B_date = obj.Get_B_date();
        this->Teacher_ID = obj.Get_Teacher_ID();
    }

    bool operator ! () {
        if (this == nullptr) {
            return true;
        }
        return false;
    }

};

std::ostream& operator << (std::ostream& os, const Teacher& Obj) {
    os << Obj.toString();
    return os;
}

// Misc.

bool check_number(std::string str) {
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}

int choose(int f, int l) {
    std::string msg = "";
    std::string choice;
    do {
        std::cout << msg;
        msg = "Please enter a valid option!: ";
        std::cin >> choice;
        scanf_s("%*[^\n]", &choice); // * is used to tell that we dont want to store the input
    } while (std::stoi(choice) < f || std::stoi(choice) > l || !check_number(choice));
    fgetc(stdin); // consume the newline
    //std::cout << choice;
    return std::stoi(choice);
}