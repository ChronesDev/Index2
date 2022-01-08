#include "../ui.cc"

// Prototypes
namespace Index::UI
{
	struct HitTestResult;
	struct UITouchElement;
}

// struct HitTestResult
namespace Index::UI
{
	struct HitTestResult
	{
		bool HasSucceeded = false;
		UITouchElement* HitTarget = nullptr;
	};
}

// UITouchElement
namespace Index::UI
{
	struct UITouchElement
	{
	public:
		virtual bool GetIsHitTestVisible() const { return false; }
		INDEX_Property(get = GetIsHitTestVisible) bool IsHitTestVisible;

	public:
		virtual bool BoxHitTest() const
		{
			return false;
		}

		virtual bool PerformHitTest() const
		{
			// Children

			if (BoxHitTest()) return true;
			return false;
		}
	};
}