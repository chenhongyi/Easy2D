#pragma once
#include "e2dmacros.h"

namespace e2d
{


// 方向
enum class Direction : int
{
	Up,			/* 上 */
	Down,		/* 下 */
	Left,		/* 左 */
	Right		/* 右 */
};


// 线条相交样式
enum class Stroke : int
{
	Miter = 0,	/* 斜切 */
	Bevel = 1,	/* 斜角 */
	Round = 2	/* 圆角 */
};


class Size;

// 坐标
class Point
{
public:
	float x;	// X 坐标
	float y;	// Y 坐标

public:
	Point();

	Point(float x, float y);

	Point(const Point& other);

	Point operator + (Point const & point) const;
	Point operator - (Point const & point) const;
	Point operator * (float const & point) const;
	Point operator / (float const & point) const;
	Point operator - () const;
	bool operator== (const Point& point) const;

	operator e2d::Size() const;

	// 判断两点间距离
	static float distance(const Point&, const Point&);
};


// 二维向量
typedef Point Vector2;


// 大小
class Size
{
public:
	float width;	// 宽度
	float height;	// 高度

public:
	Size();

	Size(float width, float height);

	Size(const Size& other);

	Size operator + (Size const & size) const;
	Size operator - (Size const & size) const;
	Size operator * (float const & size) const;
	Size operator / (float const & size) const;
	Size operator - () const;
	bool operator== (const Size& size) const;

	operator e2d::Point() const;
};


// 矩形
class Rect
{
public:
	Point origin;	// 原点坐标
	Size  size;		// 宽度和高度

public:
	Rect();
	
	Rect(float x, float y, float width, float height);
	
	Rect(const Point& pos, const Size& size);
	
	Rect(const Rect& other);
	
	Rect& operator= (const Rect& other);

	bool operator== (const Rect& rect) const;
	
	// 设置矩形
	void setRect(
		float x, 
		float y, 
		float width, 
		float height
	);
	
	// 判断点是否在矩形内
	bool containsPoint(
		const Point& point
	) const;
	
	// 判断两矩形是否相交
	bool intersects(
		const Rect& rect
	) const;
};


// 字符串
class String
{
public:
	String();
	String(const String &);
	String(const char *);
	String(const wchar_t *);
	String(String &&);

	~String();

	// 获取字符串长度
	int length() const;

	// 获取该字符串的散列值
	size_t hash() const;

	// 判断字符串是否为空
	bool isEmpty() const;

	// 获取指定位置字符
	wchar_t at(
		int index
	) const;

	// 比较字符串
	int compare(
		const String & str
	) const;

	// 截取字符串
	e2d::String subtract(
		int offset,		/* 偏移量 */
		int count = -1	/* 截取字符数量 */
	) const;

	// 插入字符串
	void insert(
		const String & str,
		int pos
	);

	// 替换字符串中的指定内容
	void replace(
		const String & from,	/* 需替换内容 */
		const String & to		/* 替换成内容 */
	);

	// 删除字符串中的指定内容
	void erase(
		int offset,		/* 偏移量 */
		int count		/* 删除字符数量 */
	);

	// 搜索字符串
	int find(
		const String & str,	/* 查找内容 */
		int offset = 0		/* 偏移量 */
	) const;

	// 清空字符串
	void clear();

	// 获取大写字符串
	String toUpper() const;

	// 获取小写字符串
	String toLower() const;

	// 将字符串转化为 int 型
	int toInt() const;

	// 将字符串转化为 float 型
	float toFloat() const;

	// 将字符串转化为 double 型
	double toDouble() const;

	// 将字符串转化为 bool 型
	bool toBool() const;

	// 数字类型转字符串
	static String parse(int value);
	static String parse(unsigned int value);
	static String parse(float value);
	static String parse(double value);

	// 格式化字符串
	static String format(const char * format, ...);
	static String format(const wchar_t * format, ...);

	// 交换两字符串
	static void swap(String &str1, String &str2);

	// 赋值运算符
	String& operator= (const String &);
	String& operator= (const char *);
	String& operator= (const wchar_t *);

	// 运算符
	String& operator+= (const String &);
	String& operator+= (const char *);
	String& operator+= (const wchar_t *);
	String operator+ (const String &) const;
	String operator+ (const char *) const;
	String operator+ (const wchar_t *) const;

	// 友元运算符
	friend String operator+ (const char *, const String &);
	friend String operator+ (const wchar_t*, const String &);

	// 类型转换操作符
	E2D_OP_EXPLICIT operator const wchar_t* () const;
	E2D_OP_EXPLICIT operator wchar_t* () const;
	E2D_OP_EXPLICIT operator std::wstring () const;
	E2D_OP_EXPLICIT operator std::string () const;

	// 比较运算符
	bool operator== (const String &) const;
	bool operator== (const char *) const;
	bool operator== (const wchar_t *) const;
	bool operator!= (const String &) const;
	bool operator!= (const char *) const;
	bool operator!= (const wchar_t *) const;
	bool operator> (const String &) const;
	bool operator>= (const String &) const;
	bool operator< (const String &) const;
	bool operator<= (const String &) const;

	// << 运算符（后接字符串）
	String& operator<< (const String &);
	String& operator<< (const char *);
	String& operator<< (char *);
	String& operator<< (const wchar_t *);
	String& operator<< (wchar_t *);
	String& operator<< (int value);
	String& operator<< (unsigned int value);
	String& operator<< (float value);
	String& operator<< (double value);

	// 其他运算符
	wchar_t& operator[] (int);

	friend std::ostream& operator<< (std::ostream &, const String &);
	friend std::wostream& operator<< (std::wostream &, const String &);

	friend std::istream& operator>> (std::istream &, String &);
	friend std::wistream& operator>> (std::wistream &, String &);

private:
	std::wstring _str;
};


// 颜色
class Color
{
public:
	Color();

	Color(
		float r,
		float g,
		float b
	);

	Color(
		float r,
		float g,
		float b,
		float alpha
	);

	Color(
		UINT rgb
	);

	Color(
		UINT rgb,
		float alpha
	);

	Color(
		const D2D1_COLOR_F& color
	);

	E2D_OP_EXPLICIT operator D2D1_COLOR_F() const;

public:
	enum Value : UINT
	{
		Black = 0x000000,
		Blue = 0x0000FF,
		BlueViolet = 0x8A2BE2,
		Brown = 0xA52A2A,
		Chocolate = 0xD2691E,
		DarkBlue = 0x00008B,
		DarkGray = 0xA9A9A9,
		DarkGreen = 0x006400,
		DarkOrange = 0xFF8C00,
		DarkRed = 0x8B0000,
		DarkViolet = 0x9400D3,
		ForestGreen = 0x228B22,
		Gold = 0xFFD700,
		Gray = 0x808080,
		Green = 0x008000,
		GreenYellow = 0xADFF2F,
		LightBlue = 0xADD8E6,
		LightCyan = 0xE0FFFF,
		LightGreen = 0x90EE90,
		LightGray = 0xD3D3D3,
		LightPink = 0xFFB6C1,
		LightSeaGreen = 0x20B2AA,
		LightSkyBlue = 0x87CEFA,
		LightYellow = 0xFFFFE0,
		Orange = 0xFFA500,
		OrangeRed = 0xFF4500,
		Pink = 0xFFC0CB,
		Purple = 0x800080,
		Red = 0xFF0000,
		Silver = 0xC0C0C0,
		SkyBlue = 0x87CEEB,
		Snow = 0xFFFAFA,
		Violet = 0xEE82EE,
		Wheat = 0xF5DEB3,
		White = 0xFFFFFF,
		WhiteSmoke = 0xF5F5F5,
		Wood = 0xDEB887,
		Yellow = 0xFFFF00,
		Yellow_Green = 0x9ACD32
	};

private:
	void _init(
		UINT rgb,
		float alpha
	);

private:
	float r;
	float g;
	float b;
	float a;
};


// 键盘键值
enum class KeyCode : int
{
	Unknown = 0,
	Up = 0xC8,
	Left = 0xCB,
	Right = 0xCD,
	Down = 0xD0,
	Enter = 0x1C,
	Space = 0x39,
	Esc = 0x01,
	Q = 0x10,
	W = 0x11,
	E = 0x12,
	R = 0x13,
	T = 0x14,
	Y = 0x15,
	U = 0x16,
	I = 0x17,
	O = 0x18,
	P = 0x19,
	A = 0x1E,
	S = 0x1F,
	D = 0x20,
	F = 0x21,
	G = 0x22,
	H = 0x23,
	J = 0x24,
	K = 0x25,
	L = 0x26,
	Z = 0x2C,
	X = 0x2D,
	C = 0x2E,
	V = 0x2F,
	B = 0x30,
	N = 0x31,
	M = 0x32,
	Num1 = 0x02,
	Num2 = 0x03,
	Num3 = 0x04,
	Num4 = 0x05,
	Num5 = 0x06,
	Num6 = 0x07,
	Num7 = 0x08,
	Num8 = 0x09,
	Num9 = 0x0A,
	Num0 = 0x0B,
	Numpad7 = 0x47,
	Numpad8 = 0x48,
	Numpad9 = 0x49,
	Numpad4 = 0x4B,
	Numpad5 = 0x4C,
	Numpad6 = 0x4D,
	Numpad1 = 0x4F,
	Numpad2 = 0x50,
	Numpad3 = 0x51,
	Numpad0 = 0x52,
};


// 鼠标键值
enum class MouseCode : int
{
	Left,		/* 鼠标左键 */
	Right,		/* 鼠标右键 */
	Middle		/* 鼠标中键 */
};


// 函数对象
class Function
{
public:
	Function();

	Function(
		std::nullptr_t
	);

	Function(
		std::function<void()> func
	);

	template<typename Func>
	Function(Func func) : _func(func) {}

	template<typename Func, typename Object>
	Function(
		Func&& func,	/* 对象的成员函数 */
		Object&& obj	/* 对象指针 */
	)
	{
		_func = std::bind(func, obj);
	}

	void operator() (void) const;

	E2D_OP_EXPLICIT operator bool() const;

protected:
	std::function<void()> _func;
};


// 时间段
class Duration
{
public:
	Duration();

	explicit Duration(
		float seconds
	);

	// 获取毫秒数
	int milliseconds() const;

	// 获取秒数
	float seconds() const;

	bool operator== (const Duration &) const;
	bool operator!= (const Duration &) const;
	bool operator> (const Duration &) const;
	bool operator>= (const Duration &) const;
	bool operator< (const Duration &) const;
	bool operator<= (const Duration &) const;

	Duration operator + (Duration const &) const;
	Duration operator - (Duration const &) const;

	Duration& operator += (Duration const &);
	Duration& operator -= (Duration const &);

protected:
	std::chrono::milliseconds _ms;
};


// 时间点
class Time
{
public:
	Time();

	// 获取时间戳
	time_t getTimeStamp() const;

	// 是否是
	bool isZero() const;

	Time operator + (Duration const &) const;
	Time operator - (Duration const &) const;

	Time& operator += (Duration const &);
	Time& operator -= (Duration const &);
	
	Duration operator - (Time const &) const;

	// 获取当前时间
	static Time now();

protected:
	std::chrono::steady_clock::time_point _timePoint;
};


// 字体
class Font
{
public:
	String	family;			// 字体族
	float	size;			// 字号
	UINT	weight;			// 粗细值
	bool	italic;			// 斜体

public:
	// 字体粗细值
	enum Weight : UINT
	{
		Thin = 100,
		ExtraLight = 200,
		Light = 300,
		Normal = 400,
		Medium = 500,
		Bold = 700,
		ExtraBold = 800,
		Black = 900,
		ExtraBlack = 950
	};

public:
	Font();

	explicit Font(
		const String& family,
		float size = 22,
		UINT weight = Font::Weight::Normal,
		bool italic = false
	);
};


class Node;

// 碰撞体
class Collider
{
public:
	// 碰撞体形状
	enum class Shape
	{
		None,		/* 无 */
		Rect,		/* 矩形 */
		Circle,		/* 圆形 */
		Ellipse		/* 椭圆形 */
	};

	// 碰撞体交集关系
	enum class Relation : int
	{
		Unknown = 0,		/* 关系不确定 */
		Disjoin = 1,		/* 没有交集 */
		IsContained = 2,	/* 完全被包含 */
		Contains = 3,		/* 完全包含 */
		Overlap = 4			/* 部分重叠 */
	};

public:
	explicit Collider(
		Node * parent
	);

	virtual ~Collider();

	// 设置碰撞体形状
	void setShape(
		Shape shape
	);

	// 是否触发碰撞事件
	void setCollisionNotify(
		bool notify
	);

	// 启用或关闭该碰撞体
	void setEnabled(
		bool enabled
	);

	// 设置碰撞体的可见性
	void setVisible(
		bool visible
	);

	// 设置绘制颜色
	void setColor(
		Color color
	);

	// 判断两碰撞体的交集关系
	Relation getRelationWith(
		Collider * pCollider
	) const;

	// 是否启用碰撞体
	bool isEnabled() const;

	// 是否可见
	bool isVisible() const;

	// 是否触发碰撞事件
	bool isCollisionNotify() const;

	// 获取绘制颜色
	Color getColor() const;

	// 获取形状
	Shape getShape() const;

	// 获取绑定节点
	Node* getNode() const;

	// 获取 ID2D1Geometry* 对象
	ID2D1Geometry* getGeometry() const;

	// 重新生成
	void recreate();

	// 渲染碰撞体
	void render();

protected:
	E2D_DISABLE_COPY(Collider);

protected:
	bool	_enabled;
	bool	_visible;
	bool	_notify;
	Color	_color;
	Node *	_parentNode;
	Shape	_shape;
	ID2D1Geometry* _geometry;
};


// 资源
class Resource
{
public:
	Resource(
		size_t resNameId,			/* 资源名称 */
		const String& resType		/* 资源类型 */
	);

public:
	size_t	resNameId;
	String	resType;
};


// 引用计数对象
class Ref
{
public:
	Ref();

	virtual ~Ref();

	// 增加引用计数
	void retain();

	// 减少引用计数
	void release();

	// 获取引用计数
	int getRefCount() const;

protected:
	E2D_DISABLE_COPY(Ref);

private:
	int _refCount;
};


// 图片
class Image :
	public Ref
{
public:
	Image();

	explicit Image(
		const Resource& res
	);

	explicit Image(
		const Resource& res,
		const Rect& cropRect	/* 裁剪矩形 */
	);

	explicit Image(
		const String& fileName
	);

	explicit Image(
		const String& fileName,
		const Rect& cropRect	/* 裁剪矩形 */
	);

	virtual ~Image();

	// 加载图片资源
	bool open(
		const Resource& res
	);

	// 加载图片资源
	bool open(
		const String& fileName
	);

	// 将图片裁剪为矩形
	void crop(
		const Rect& cropRect	/* 裁剪矩形 */
	);

	// 获取宽度
	virtual float getWidth() const;

	// 获取高度
	virtual float getHeight() const;

	// 获取大小
	virtual Size getSize() const;

	// 获取源图片宽度
	virtual float getSourceWidth() const;

	// 获取源图片高度
	virtual float getSourceHeight() const;

	// 获取源图片大小
	virtual Size getSourceSize() const;
	
	// 获取裁剪位置 X 坐标
	virtual float getCropX() const;

	// 获取裁剪位置 Y 坐标
	virtual float getCropY() const;

	// 获取裁剪位置
	virtual Point getCropPos() const;

	// 获取 ID2D1Bitmap 对象
	ID2D1Bitmap * getBitmap();

	// 预加载图片资源
	static bool preload(
		const String& fileName
	);

	// 预加载图片资源
	static bool preload(
		const Resource& res
	);

	// 清空缓存
	static void clearCache();

protected:
	E2D_DISABLE_COPY(Image);

	// 设置 Bitmap
	void _setBitmap(
		ID2D1Bitmap * bitmap
	);

protected:
	Rect _cropRect;
	ID2D1Bitmap * _bitmap;

	static std::map<size_t, ID2D1Bitmap*> _bitmapCache;
};


}


namespace e2d
{
	struct autorelease_t { };

	extern autorelease_t const autorelease;
}

void* operator new(
	size_t size,
	e2d::autorelease_t const&
	) E2D_NOEXCEPT;

void operator delete(
	void* block,
	e2d::autorelease_t const&
	) E2D_NOEXCEPT;
