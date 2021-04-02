#include "solve.h"
#include <cmath>
#include <cwctype>
#include <cwchar>

Roots solve(double a, double b, double c) {
	b /= a;
	c /= a;
	double d = b * b - 4 * c;
	if (d >= 0)
		return Roots{ false, (-b + sqrt(d)) / 2, (-b - sqrt(d)) / 2 };
	return Roots{ true, -b / 2, sqrt(-d)/2 };
}

void remove_whitespace(wchar_t* p) {
	const wchar_t* q = p;
	while (*p) {
		while (*q == L' ')
			++q;
		*(p++) = *(q++);
	}
}

struct EPart {
    enum Type {
        ZERO = 0,
        ONE = 1,
        TWO = 2,
        ERR = 3,
        EOL = 4
    } tp;
    double value;

    bool operator==(const EPart& y) const { return tp == y.tp; }
    bool operator!=(const EPart& y) const { return tp != y.tp; }
};

const EPart ERR = EPart{ EPart::ERR, 0. };
const EPart EOL = EPart{ EPart::EOL, 0. };

EPart x_part(const wchar_t*& txt, double k) {
    if (*txt != L'x')
        return ERR;
    if (txt[1] == L'*' && txt[2] == L'x' || txt[1] == L'^' && txt[2] == L'2') {
        txt += 3;
        return EPart{ EPart::TWO, k };
    }
    ++txt;
    return EPart{ EPart::ONE, k };
}

bool try_number(const wchar_t*& txt, double& k) {
    wchar_t* out;
    k = wcstod(txt, &out);
    bool b = txt != out;
    txt = out;
    return b && std::isfinite(k);
}

EPart next(const wchar_t*& txt, bool require_sign = true) {
    double k = 1.0;
    if (!*txt)
        return EOL;
    if (*txt == L'-') {
        k = -1.0;
        ++txt;
    } else if (*txt == L'+') {
        ++txt;
    } else if (require_sign)
        return ERR;
    if (*txt == L'x')
        return x_part(txt, k);
    if (try_number(txt, k)) {
        if (*txt == L'x')
            return x_part(txt, k);
        else if (*txt == L'*')
            return x_part(++txt, k);
        return EPart{ EPart::ZERO, k };
    }
    return ERR;
}

bool parse(const wchar_t* txt, double& a, double& b, double& c) {
    double ps[3]{};
    bool fs[3]{};
    int n;
    EPart t = next(txt, false);
    if (t == EOL || t == ERR)
        return false;
    ps[t.tp] = t.value;
    fs[t.tp] = true;
    for (n = 1; n < 4; ++n) {
        t = next(txt);
        if (t == ERR)
            return false;
        if (t == EOL)
            break;
        if (fs[t.tp])
            return false;
        ps[t.tp] = t.value;
        fs[t.tp] = true;
    }
    if (t != EOL)
        return false;
    c = ps[0]; b = ps[1]; a = ps[2];
    return true;
}

bool try_parse_and_solve(wchar_t* line, Roots& out) {
    remove_whitespace(line);
    double a, b, c;
    if (!parse(line, a, b, c) || !a)
        return false;
    out = solve(a, b, c);
    return true;
}
