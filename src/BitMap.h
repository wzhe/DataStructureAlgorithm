/***************************************************
 * Data Structure & Algorithm
 * wzhe ahuwang@163.com
 ***************************************************/

#pragma once

#pragma GCC diagnostic ignored "-Wconversion"
#include <stdio.h>
#include <string.h>

class Bitmap {
private:
    unsigned char *M; //比特图所存放的空间M[]
    int N;            //比特图的容量为N*sizeof(char)*8 比特

protected:
    void init(int n) {
        M = new unsigned char[N = n / 8 + 1];
        memset(M, 0, N);
    }

public:
    Bitmap(int n = 8) { init(n); }
    Bitmap(char *file, int n = 8) //按指定规模从文件中读取比特图
    {
        init(n);
        FILE *fp = fopen(file, "r");
        fread(M, sizeof(char), N, fp);
        fclose(fp);
    }
    ~Bitmap() {
        delete[] M;
        M = NULL;
    }

    void set(int k) {
        expand(k);
        M[k >> 3] |= (0x80 >> (k & 0x07));
    }
    void clear(int k) {
        expand(k);
        M[k >> 3] &= ~(0x80 >> (k & 0x07));
    }
    bool test(int k) {
        expand(k);
        return M[k >> 3] & (0x80 >> (k & 0x07));
    }

    void dump(char *file) {
        FILE *fp = fopen(file, "w");
        fwrite(M, sizeof(char), N, fp);
        fclose(fp);
    }

    char *bits2string(int n) {
        expand(n - 1);             //此时可能被访问的最高位为bitmap[n-1]
        char *s = new char[n + 1]; //所占用内存由上层释放
        s[n] = '\0';
        for (int i = 0; i < n; i++) {
            s[i] = test(i) ? '1' : '0';
        }
        return s;
    }

    void expand(int k) {
        if (k < 8 * N)
            return;
        int oldN = N;
        unsigned char *oldM = M;
        init(2 * k);
        memcpy(M, oldM, oldN);
        delete[] oldM;
    }
};
#pragma GCC diagnostic warning "-Wconversion"
