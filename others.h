#include <vector>
#include <string>

namespace String {
    class StringProcessor
    {
        private:
        std::vector<int> _getNext(std::string p)
        {
            int n = p.size(), tmp;
            std::vector<int> next(n);
            next[0] = -1;
            for (int i = 1; i < n; ++i)
            {
                tmp = next[i-1];
                while (tmp >= 0 && p[tmp] != p[i-1])
                    tmp = next[tmp];
                next[i] = tmp + 1;
            }
            return next;
        }

        public:
        int KMP(std::string s, std::string p) // p is pattern, s is main string
        {
            int p1 = 0, p2 = 0;
            int ans = -1;
            std::vector<int> next = _getNext(p);
            while (s[p1])
            {
                if (!p[p2])
                {
                    ans = p1 - p2;
                    break;
                }
                if (s[p1] == p[p2])
                {
                    p1++; p2++;
                }
                else if (p2 == 0)
                    p1++;
                else
                    p2 = next[p2];
            }
            return ans; 
            // index of return value starts from 0. -1 for not found.
        }
    };
}
