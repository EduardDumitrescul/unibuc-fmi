#include <bits/stdc++.h>

#define maxn 1005
#define maxp 600000

// #define maxn 10
// #define maxp 50

std::ifstream fin("take5.in");
std::ofstream fout("take5.out");

int v[maxn], temp[maxn];
int left[maxp], right[maxp];
int cnt_left, cnt_right;

int main() {
    int n;
    long long sum;
    fin >> n >> sum;
    if(sum > 2000000000) {
        fout << 0;
        return 0;
    }

    for(int i = 0; i < n; i ++) {
        fin >> v[i];
    }
    std::sort(v, v+n);

    for(int i = 3; i < n; i ++) {
        for(int j = i + 1; j < n; j ++) {
            right[cnt_right++] = v[i] + v[j];
        }
    }
    std::sort(right, right+cnt_right);
    left[cnt_left++] = v[0] + v[1];

    long long ans = 0;

    for(int mid = 2; mid < n - 2; mid ++) {
        // for(int i = 0; i < cnt_left; i ++)
        //     fout << left[i] <<  ' ';
        // fout << '\n';
        // for(int j = 0; j < cnt_right;j  ++) 
        //     fout << right[j] << ' ';
        // fout << '\n';


        for(int i = 0, j = cnt_right - 1; i < cnt_left and j >= 0;) {
            while(j > 0 and right[j] + left[i] > sum - v[mid])
                j --;

            if(left[i] + right[j] + v[mid] != sum) {
                i ++;
                continue;
            }

            int l = 0, r = 1;
            while(j > 0 and left[i] + right[j-1] == sum - v[mid]) {
                j --;
                r ++;
            }
            while(i < cnt_left and left[i] + right[j] == sum - v[mid]) {
                i ++;
                l ++;
            }
            // std::cout << mid << ' ' << l * r << '\n';
            ans = ans + l * r;
        }

        if(mid == n-3)
            break;

        int p = 0;
        for(int i = 0; i < mid; i ++) {
            temp[p++] = v[i] + v[mid];
        }

        int i = cnt_left, j = p;
        cnt_left = cnt_left + p;
        p = cnt_left;
        
        while(i and j and --p) {
            if(temp[j-1] >= left[i-1]) {
                left[p] = temp[--j];
            }
            else
                left[p] = left[--i];
        }
        while(i > 0)
            left[--p] = left[--i];
        while(j > 0)
            left[--p] = temp[--j];


        p = 0;
        for(int i = mid + 2; i < n; i ++) {
            temp[p++] = v[i] + v[mid + 1];
        }

        i = j = 0;
        int k = 0;
        while(i < cnt_right and j < p) {
            while(i < cnt_right and right[i] < temp[j]) {
                right[k++] = right[i];
                i ++;
            }
            if(i == cnt_right)
                break;
            if(right[i] == temp[j]) {
                i ++;
                j ++;
            }
            else {
                j ++;
            }
        }
        while(i  < cnt_right) {
            right[k++] = right[i++];
        }
        cnt_right = k;

    }
    fout << ans << '\n';
    return 0;
}
