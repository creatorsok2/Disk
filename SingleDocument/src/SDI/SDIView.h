
// SDIView.h: CSDIView 클래스의 인터페이스
//

#pragma once


class CSDIView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSDIView() noexcept;
	DECLARE_DYNCREATE(CSDIView)

// 특성입니다.
public:
	CSDIDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void Init();
	void CreateRGBPalette(void);
	BOOL bSetupPixelFormat(void);
	unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift);
	void DrawScene(void);

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPlay();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

protected:
	BOOL m_bPlay = FALSE;
	
	CPalette    m_cPalette;
	CPalette*	m_pOldPalette = nullptr;
	CRect       m_oldRect;
	float       m_fRadius;

	CClientDC*	m_pDC = nullptr;
};

#ifndef _DEBUG  // SDIView.cpp의 디버그 버전
inline CSDIDoc* CSDIView::GetDocument() const
   { return reinterpret_cast<CSDIDoc*>(m_pDocument); }
#endif

