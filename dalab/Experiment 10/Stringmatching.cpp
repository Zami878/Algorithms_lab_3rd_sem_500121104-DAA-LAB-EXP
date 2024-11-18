#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

vector<int> naiveSearch(const string& text, const string& pattern) {
    vector<int> result;
    int n = text.length();
    int m = pattern.length();

    for (int i = 0; i <= n - m; ++i) {
        int j = 0;
        while (j < m && text[i + j] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            result.push_back(i);
        }
    }

    return result;
}
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define d 256 

vector<int> rabinKarpSearch(const string& text, const string& pattern) {
    vector<int> result;
    int n = text.length();
    int m = pattern.length();
    int i, j;
    int p = 0;
    int t = 0; 
    int h = 1;

    
    for (i = 0; i < m - 1; i++) {
        h = (h * d);
    }

    for (i = 0; i < m; i++) {
        p = (p * d + pattern[i]);
        t = (t * d + text[i]);
    }

    
    for (i = 0; i <= n - m; i++) {
        
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }
            if (j == m) {
                result.push_back(i);
            }
        }

        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]);
        }
    }

    return result;
}



vector<int> computeLPSArray(const string& pattern) {
    int m = pattern.length();
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}


vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> result;
    int n = text.length();
    int m = pattern.length();
    vector<int> lps = computeLPSArray(pattern);
    int i = 0; 
    int j = 0; 

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            result.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return result;
}




int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABAB";

    
    auto start = chrono::high_resolution_clock::now();
    vector<int> naiveResult = naiveSearch(text, pattern);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> naiveDuration = end - start;

    
    start = chrono::high_resolution_clock::now();
    vector<int> rabinKarpResult = rabinKarpSearch(text, pattern);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> rabinKarpDuration = end - start;


    start = chrono::high_resolution_clock::now();
    vector<int> kmpResult = kmpSearch(text, pattern);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double> kmpDuration = end - start;

    cout << "Naive Result: ";
    for (int index : naiveResult) cout << index << " ";
    cout << "\nNaive Time: " << naiveDuration.count() << " seconds\n";

    cout << "Rabin-Karp Result: ";
    for (int index : rabinKarpResult) cout << index << " ";
    cout << "\nRabin-Karp Time: " << rabinKarpDuration.count() << " seconds\n";

    cout << "KMP Result: ";
    for (int index : kmpResult) cout << index << " ";
    cout << "\nKMP Time: " << kmpDuration.count() << " seconds\n";

    return 0;
}

