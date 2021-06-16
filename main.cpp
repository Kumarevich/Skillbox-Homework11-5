#include <iostream>

std::string get_column(std::string line, int x) {
    std::string col = "";
    for (int i = x - 1; i < x + 6; i += 3) {
        col += line[i];
    }
    return col;
}

int chek_line (std::string line, char ch) {
    int res = 0;
    for (int i = 0; i < line.length(); ++i) {
        if (line[i] == ch) {
            ++res;
        }
    }
    return res/3;
}

char get_char (std::string line, int x, int y) {
    //std::string line = one + two + three;
    int pos;
    if (y == 1) {
        pos = x - y;
    } else if (y == 2) {
        pos = x + y;
    } else if (y == 3) {
        pos = x + y + 2;
    } else {
        return 'f';
    }
    return line[pos];
}

int sum_char (std::string line, char ch) {
    int sum = 0;
    for (int y = 1; y <= 3; ++y) {
        for (int x = 1; x <= 3; ++x) {
            if (get_char(line, x, y) == ch) {
                ++sum;
            } else if (get_char(line, x, y) != 46 && get_char(line, x, y) != 79 && get_char(line, x, y) != 88) {
                return 666;
            }
        }
    }
    return sum;
}

std::string check_winer (std::string line1, std::string line2, std::string line3) {
    std::string result;
    std::string line = line1 + line2 + line3;
    std::string tempLine, dLine1, dLine2;
    int petya, vanya, petyaW = 0, vanyaW = 0;
    for (int i = 0; i < line.length(); i += 3) {
        tempLine = "";
        for (int j = i; j < i + 3; ++j) {
            tempLine += line[j];
        }
        petyaW += chek_line(tempLine, 'X');
        vanyaW += chek_line(tempLine, 'O');
    }
    for (int i = 1; i <= 3; ++i) {
        petyaW += chek_line(get_column(line, i), 'X');
        vanyaW += chek_line(get_column(line, i), 'O');
    }
    for (int i = 1; i < 4; ++i) {
        dLine1 += get_char(line, i, i);
        dLine2 += get_char(line, i, (4 - i));
    }
    petyaW += chek_line(dLine1, 'X');
    petyaW += chek_line(dLine2, 'X');
    vanyaW += chek_line(dLine1, 'O');
    vanyaW += chek_line(dLine2, 'O');
    if (petyaW == 1 && vanyaW == 0) {
        result = "Petya won.";
    } else if (vanyaW == 1 && petyaW == 0) {
        result = "Vanya won.";
    } else if (vanyaW == 0 && petyaW == 0) {
        result = "Nobody.";
    } else {
        result = "Fail!";
    }
    return result;
}

bool chek_input (std::string one, std::string two, std::string three) {
    std::string full = one + two + three;
    int l = full.length() - 1;
    int charX = 0, charO = 0, point = 0;
    if (one.length() != 3 || two.length() != 3 || three.length() != 3
        || sum_char(full, 'X') == 666
        || sum_char(full, 'O') > sum_char(full, 'X')) {
        return false;
    }
    return true;
}


int main() {
    std::cout << "Input result in 3x3 format (X, O or '.' for empty slot): ";
    std::string line1, line2, line3;
    std::cin >> line1 >> line2 >> line3;
    while (!chek_input(line1, line2, line3)) {
        std::cout << "Wrong input. Try again in 3x3 format (X, O or '.' for empty slot): ";
        std::cin >> line1 >> line2 >> line3;
    }
    std::cout << check_winer(line1, line2, line3);
    return 0;
}
