#pragma once
#include "oaui/oaui.h"

namespace oaui
{
	struct WindowOption
	{
		char Type;
		union
		{
			int IntVal;
			unsigned int UIntVal;
			float FloatVal;
			double DoubleVal;
			bool BoolVal;
			std::string* StringVal;
		};

		~WindowOption()
		{
			if (Type == 5)
			{
				if (StringVal)
					delete StringVal;
			}
		}
		operator int() const { return IntVal; }
		operator unsigned int() const { return UIntVal; }
		operator float() const { return FloatVal; }
		operator double() const { return DoubleVal; }
		operator bool() const { return BoolVal; }
		operator std::string() const { return *StringVal; }

		WindowOption& operator=(const int& val) { Type = 0; IntVal = val;  return *this; }
		WindowOption& operator=(const unsigned int& val) { Type = 1; UIntVal = val;  return *this; }
		WindowOption& operator=(const float& val) { Type = 2; FloatVal = val;  return *this; }
		WindowOption& operator=(const double& val) { Type = 3; DoubleVal = val;  return *this; }
		WindowOption& operator=(const bool& val) { Type = 4; BoolVal = val;  return *this; }
		WindowOption& operator=(const std::string& val) 
		{ 
			Type = 5; 

			if (StringVal)
				delete StringVal;

			StringVal = new std::string{ val };
			return *this; 
		}
	};

	class Window
	{
	protected:
		bool        m_show;
		std::unordered_map<int, WindowOption> m_options;
	public:

		Window(bool show = false) : m_show(show) {}

		void Show();
		void Close();
		bool IsShowed();
		bool* GetShowPointer();

		template <typename T>
		T GetOptionValue(int option)
		{
			if (m_options.count(option) == 0)
				return T{};
			return m_options[option];
		};

		template <typename T>
		void SetOptionValue(int option, const T& value) 
		{
			m_options[option] = value;
		};

		virtual void Render(class UI* ui) = 0;
	};
}
