#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <ctime>

using namespace std;

// Hàm sinh một ký tự thường ngẫu nhiên 'a'-'z'
char getRandomChar(mt19937& gen) {
    uniform_int_distribution<> dis(0, 25) ;
    return 'a' + dis(gen);
}

// Hàm sinh test case
void generateTestCase(int R, int C, int K, string filename) {
    mt19937 gen(time(0)); // Seed dựa trên thời gian thực
    
    // 1. Tạo lưới ký tự ngẫu nhiên
    vector<vector<char>> grid(R, vector<char>(C));
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            grid[i][j] = getRandomChar(gen);
        }
    }

    // 2. Tạo danh sách từ khóa
    vector<string> keywords;
    
    // Để test khách quan, ta sẽ "cấy" (plant) một nửa số từ khóa vào lưới 
    // để đảm bảo chắc chắn có kết quả "found"
    int planted = K / 2;
    for (int k = 0; k < planted; ++k) {
        int wordLen = 3 + (gen() % 6); // Độ dài từ 3 đến 8
        string word = "";
        
        if (gen() % 2 == 0) { // Cấy theo chiều ngang (Horizontal)
            int r = gen() % R;
            int c = gen() % max(1, C - wordLen);
            for (int i = 0; i < wordLen; ++i) {
                word += grid[r][c + i];
            }
        } else { // Cấy theo chiều dọc (Vertical)
            int r = gen() % max(1, R - wordLen);
            int c = gen() % C;
            for (int i = 0; i < wordLen; ++i) {
                word += grid[r + i][c];
            }
        }
        keywords.push_back(word);
    }

    // Một nửa còn lại là các từ hoàn toàn ngẫu nhiên (có thể không có trong lưới)
    while (keywords.size() < (size_t)K) {
        int wordLen = 3 + (gen() % 6);
        string word = "";
        for (int i = 0; i < wordLen; ++i) word += getRandomChar(gen);
        keywords.push_back(word);
    }

    // 3. Ghi vào file theo định dạng đề bài
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Khong the mo file de ghi!" << endl;
        return;
    }

    outfile << R << " " << C << "\n";
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            outfile << grid[i][j] << (j == C - 1 ? "" : " ");
        }
        outfile << "\n";
    }
    
    outfile << K << "\n";
    for (const string& s : keywords) {
        outfile << s << "\n";
    }

    outfile.close();
    cout << "Da tao file: " << filename << " (" << R << "x" << C << ", K=" << K << ")" << endl;
}

int main() {
    // Scenario 1: Thay đổi kích thước lưới (Grid Size), giữ K nhỏ (K=5)
    generateTestCase(10, 10, 5, "test_s1_10.txt");
    generateTestCase(100, 100, 5, "test_s1_100.txt");
    generateTestCase(500, 500, 5, "test_s1_500.txt");
    generateTestCase(1000, 1000, 5, "test_s1_1000.txt"); // Max size

    // Scenario 2: Thay đổi số lượng từ khóa (Dictionary Size), giữ lưới cố định (100x100)
    generateTestCase(100, 100, 10, "test_s2_k10.txt");
    generateTestCase(100, 100, 50, "test_s2_k50.txt");
    generateTestCase(100, 100, 100, "test_s2_k100.txt");

    return 0;
}
