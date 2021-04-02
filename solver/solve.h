struct Roots {
	bool complex;
	double r1, r2;
};

Roots solve(double a, double b, double c);
bool try_parse_and_solve(wchar_t* text, Roots &out);

