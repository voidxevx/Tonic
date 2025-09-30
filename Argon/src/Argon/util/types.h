#pragma once

namespace argon
{
	constexpr double PI = 0x1.921fb54442d18469898cc51701b8p+1;
	constexpr double E = 0x1.5bf0a8b1457695355fb8ac404e7ap+1;

	static int Degrees(double rads)
	{
		return int(rads * (180 / PI));
	}
	template<typename _T>
	static _T Radians(int degs)
	{
		return _T(degs) * ((_T)PI / 180);
	}
}