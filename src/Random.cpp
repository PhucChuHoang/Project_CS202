#include "Random.h"

namespace Random {
    const unsigned ALL_BITS = ~((unsigned)0);
    std::mt19937 rnd;

    void setSeed(unsigned seed) {
        rnd.seed(seed);
    }

    unsigned next() {
        return rnd();
    }

    void setLevelSeed(int level) {
        assert(0 <= level);
        setSeed(RANDOM_SEED);
        for (int i = 0; i < level; ++i) {
            next();
        }
        setSeed(next());
    }

    unsigned getBits(int n) {
        assert(0 <= n && n <= 32);
        if (n == 0) {
            return 0;
        }
        return next() & (ALL_BITS >> (32 - n));
    }

    float nextFloat01() {
        union {
            unsigned u;
            float f;
        } uf;
        uf.u = ALL_BITS >> 2;
        uf.u &= ~getBits(23);
        return uf.f - (float)1;
    }

    float wnextFloat01(int type) {
        if (type == 0) {
            return nextFloat01();
        }
        if (type > 0) {
            ++type;
            float res = wnextFloat01((type >> 1) - 1);
            res = std::max(res, wnextFloat01((type >> 1) - 1));
            if (type & 1) {
                res = std::max(res, nextFloat01());
            }
            return res;
        } else {
            type = -type + 1;
            float res = wnextFloat01(-(type >> 1) + 1);
            res = std::min(res, wnextFloat01(-(type >> 1) + 1));
            if (type & 1) {
                res = std::min(res, nextFloat01());
            }
            return res;
        }
    }

    unsigned next(unsigned l, unsigned r) {
        assert(l <= r);
        return l + next() % (r - l + 1);
    }

    int next(int l, int r) {
        assert(l <= r);
        return l + next() % (r - l + 1);
    }

    int wnext(int type, int l, int r) {
        assert(l <= r);
        int res = next(l, r);
        if (type < 0) {
            res = std::min(res, wnext(type + 1, l, r));
        }
        if (type > 0) {
            res = std::max(res, wnext(type - 1, l, r));
        }
        return res;
    }

    float next(float l, float r) {
        assert(l <= r);
        float diff = r - l;
        return l + diff * nextFloat01();
    }

    float wnext(int type, float l, float r) {
        assert(l <= r);
        float diff = r - l;
        return l + diff * wnextFloat01(type);
    }
}