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
	protected:
		bool IsHitTestVisible_ = false;

	public:
	    bool GetIsHitTestVisible() const { return IsHitTestVisible_; }
		INDEX_Property(get = GetIsHitTestVisible) bool IsHitTestVisible;

	public:
		virtual bool HitTest(HitTestResult& e, Vec2F& p)
		{
			return false;
		}

		virtual void HitTestRecursive(HitTestResult& e, Vec2F& p)
		{
			if (HitTest(e, p)) return;
		}

		virtual HitTestResult PerformHitTest(Vec2F p)
		{
			HitTestResult result;
			HitTestRecursive(result, p);
			return result;
		}
	};
}