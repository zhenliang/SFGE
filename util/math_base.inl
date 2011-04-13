
template <class T1, class T2, class T3>
inline T1 Clam(const T1& num, const T2& low, const T3& high)
{
	assert(low < high);

	if (num < low)
		return low;

	if (num > high)
		return high;

	return num;
}

template <class T1, class T2>
inline T1 ClamUp(const T1& num, const T2& low)
{
    return num < low ? low : num;
}

template <class T1, class T2>
inline T1 ClamDown(const T1& num, const T2& high)
{
    return num > high ? high : num;
}

template <class Num, class Begin, class End>
inline bool InRange(Num num, Begin begin, End end)
{
	return (num >= begin) && (num <= end);
}

template <class NumX, class NumY, class Left, class Top, class Right, class Bottom>
inline bool InRect(NumX x, NumY y, Left left, Top top, Right right, Bottom bottom)
{
	return InRange(x, left, right) && InRange(y, top, bottom);
}