#include <iostream>
#include <cstdarg>

int total_calc = 0;
template<typename T>
void do_something_with_arg(T var)
{
	auto count = sizeof(T);
	char *p = (char*)&var;
	for (int i = 0; i < count; i++)
	{
		total_calc += p[i];
	}
}

template<typename ...Args> int CollectVars( Args ...args)
{
	total_calc = 0;
	(do_something_with_arg(args), ...);
	return total_calc;
}


static int CollectVars2(const char* fmt...)
{
	total_calc = 0;
	va_list args;
	va_start(args, fmt);

	while (*fmt != '\0') 
	{
		switch (*fmt)
		{
			case 'd':
			{
				const int i = va_arg(args, int);
				do_something_with_arg(i);
				break;
			}
			case 'c':
			{
				const int c = va_arg(args, int);
				do_something_with_arg(static_cast<char>(c));
				break;
			}
			case 'f':
			{
				const double d = va_arg(args, double);
				do_something_with_arg(static_cast<float>(d));
				break;
			}
			case 'x':
			{
				const double d = va_arg(args, double);
				do_something_with_arg(d);
				break;
			}
			case 'b':
			{
				const int b = va_arg(args, int);
				do_something_with_arg(static_cast<bool>(b));
				break;
			}

		}
		++fmt;
	}
	va_end(args);
	return total_calc;
}

int main()
{
	int total_calc0{}, total_calc1{};
	volatile auto x = 10;
	volatile auto y = 5.0;
	volatile auto z = 6.f;
	volatile auto w = true;
	volatile auto q = 'c';
	total_calc0 = CollectVars(x,y,z,w,q);
	//total_calc1 = CollectVars2("dxfbc", x, y, z, w, q);
	std::cout << total_calc0 << " " << total_calc1 << std::endl;

}
