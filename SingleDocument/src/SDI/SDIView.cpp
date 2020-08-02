
// SDIView.cpp: CSDIView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SDI.h"
#endif

#include "SDIDoc.h"
#include "SDIView.h"

#include "gl/gl.h"
#include "gl/glu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


unsigned char threeto8[8] =
{
	0, 0111 >> 1, 0222 >> 1, 0333 >> 1, 0444 >> 1, 0555 >> 1, 0666 >> 1, 0377
};

unsigned char twoto8[4] =
{
	0, 0x55, 0xaa, 0xff
};

unsigned char oneto8[2] =
{
	0, 255
};

static int defaultOverride[13] =
{
	0, 3, 24, 27, 64, 67, 88, 173, 181, 236, 247, 164, 91
};

static PALETTEENTRY defaultPalEntry[20] =
{
	{ 0,   0,   0,    0 },
	{ 0x80,0,   0,    0 },
	{ 0,   0x80,0,    0 },
	{ 0x80,0x80,0,    0 },
	{ 0,   0,   0x80, 0 },
	{ 0x80,0,   0x80, 0 },
	{ 0,   0x80,0x80, 0 },
	{ 0xC0,0xC0,0xC0, 0 },

	{ 192, 220, 192,  0 },
	{ 166, 202, 240,  0 },
	{ 255, 251, 240,  0 },
	{ 160, 160, 164,  0 },

	{ 0x80,0x80,0x80, 0 },
	{ 0xFF,0,   0,    0 },
	{ 0,   0xFF,0,    0 },
	{ 0xFF,0xFF,0,    0 },
	{ 0,   0,   0xFF, 0 },
	{ 0xFF,0,   0xFF, 0 },
	{ 0,   0xFF,0xFF, 0 },
	{ 0xFF,0xFF,0xFF, 0 }
};

//////////////////////////////////////////////////

// CSDIView

IMPLEMENT_DYNCREATE(CSDIView, CView)

BEGIN_MESSAGE_MAP(CSDIView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_MENU_PLAY, OnPlay)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CSDIView 생성/소멸

CSDIView::CSDIView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSDIView::~CSDIView()
{
}

BOOL CSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CSDIView 그리기

void CSDIView::OnDraw(CDC* /*pDC*/)
{
	CSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	DrawScene();
}


// CSDIView 인쇄


void CSDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CSDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

// CSDIView 진단

#ifdef _DEBUG
void CSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIDoc* CSDIView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIDoc)));
	return (CSDIDoc*)m_pDocument;
}
#endif //_DEBUG

void CSDIView::Init()
{
	m_pDC = new CClientDC(this);
	ASSERT(m_pDC != nullptr);

	if (!bSetupPixelFormat())
		return;

	PIXELFORMATDESCRIPTOR pfd;

	auto pfm = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), pfm, sizeof(pfd), &pfd);

	CreateRGBPalette();

	auto hrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);

	GetClientRect(&m_oldRect);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	GLfloat fMaxObjSize, fAspect;
	GLfloat fNearPlane, fFarPlane;

	if (m_oldRect.bottom)
		fAspect = (GLfloat)m_oldRect.right / m_oldRect.bottom;
	else    // don't divide by zero, not that we should ever run into that...
		fAspect = 1.0f;
	fNearPlane = 3.0f;
	fFarPlane = 7.0f;
	fMaxObjSize = 3.0f;
	m_fRadius = fNearPlane + fMaxObjSize / 2.0f;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, fAspect, fNearPlane, fFarPlane);
	glMatrixMode(GL_MODELVIEW);
}

void CSDIView::CreateRGBPalette(void)
{
	PIXELFORMATDESCRIPTOR pfd;

	auto pf = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), pf, sizeof(pfd), &pfd);

	if (pfd.dwFlags & PFD_NEED_PALETTE)
	{
		pf = 1 << pfd.cColorBits;

		auto pPal = (PLOGPALETTE) new char[sizeof(LOGPALETTE) + pf * sizeof(PALETTEENTRY)];
		ASSERT(pPal != nullptr);
	
		pPal->palVersion = 0x300;
		pPal->palNumEntries = static_cast<WORD>(pf);
		for (auto i = 0; i < pf; ++i)
		{
			pPal->palPalEntry[i].peRed =
				ComponentFromIndex(i, pfd.cRedBits, pfd.cRedShift);
			pPal->palPalEntry[i].peGreen =
				ComponentFromIndex(i, pfd.cGreenBits, pfd.cGreenShift);
			pPal->palPalEntry[i].peBlue =
				ComponentFromIndex(i, pfd.cBlueBits, pfd.cBlueShift);
			pPal->palPalEntry[i].peFlags = 0;
		}

		/* fix up the palette to include the default GDI palette */
		if ((pfd.cColorBits == 8) &&
			(pfd.cRedBits == 3) && (pfd.cRedShift == 0) &&
			(pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&
			(pfd.cBlueBits == 2) && (pfd.cBlueShift == 6)
			)
		{
			for (auto i = 1; i <= 12; i++)
				pPal->palPalEntry[defaultOverride[i]] = defaultPalEntry[i];
		}

		m_cPalette.CreatePalette(pPal);
		delete[] pPal;

		m_pOldPalette = m_pDC->SelectPalette(&m_cPalette, FALSE);
		m_pDC->RealizePalette();
	}
}

BOOL CSDIView::bSetupPixelFormat(void)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		PFD_SUPPORT_OPENGL |	        // support OpenGL
		PFD_DOUBLEBUFFER,			    // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		24,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		32,                             // 32-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};

	int pixelformat = 0;
	if ((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)
	{
		std::cout << "ChoosePixelFormat failed" << std::endl;
		return FALSE;
	}

	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		std::cout << "SetPixelFormat failed" << std::endl;
		return FALSE;
	}

	return TRUE;
}

unsigned char CSDIView::ComponentFromIndex(int i, UINT nbits, UINT shift)
{
	unsigned char val;

	val = (unsigned char)(i >> shift);
	switch (nbits)
	{

	case 1:
		val &= 0x1;
		return oneto8[val];
	case 2:
		val &= 0x3;
		return twoto8[val];
	case 3:
		val &= 0x7;
		return threeto8[val];
	}
	return 0;
}

void CSDIView::DrawScene(void)
{
	static BOOL     bBusy = FALSE;
	static GLfloat  wAngleY = 10.0f;
	static GLfloat  wAngleX = 1.0f;
	static GLfloat  wAngleZ = 5.0f;

	if (bBusy)
		return;
	bBusy = TRUE;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	glTranslatef(0.0f, 0.0f, -m_fRadius);
	glRotatef(wAngleX, 1.0f, 0.0f, 0.0f);
	glRotatef(wAngleY, 0.0f, 1.0f, 0.0f);
	glRotatef(wAngleZ, 0.0f, 0.0f, 1.0f);

	wAngleX += 1.0f;
	wAngleY += 10.0f;
	wAngleZ += 5.0f;


	glBegin(GL_QUAD_STRIP);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glEnd();

	glPopMatrix();

	glFinish();
	SwapBuffers(wglGetCurrentDC());

	bBusy = FALSE;
}

// CSDIView 메시지 처리기

void CSDIView::OnPlay()
{
	m_bPlay = !m_bPlay;

	if (m_bPlay)
		SetTimer(1, 15, NULL);
	else
		KillTimer(1);
}

void CSDIView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	DrawScene();

	CView::OnTimer(nIDEvent);

	// Eat spurious WM_TIMER messages
	MSG msg;
	while (::PeekMessage(&msg, m_hWnd, WM_TIMER, WM_TIMER, PM_REMOVE));
}


int CSDIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	Init();

	return 0;
}


void CSDIView::OnDestroy()
{
	KillTimer(1);

	auto hrc = ::wglGetCurrentContext();

	::wglMakeCurrent(NULL, NULL);

	if (hrc)
		::wglDeleteContext(hrc);

	if (m_pOldPalette)
		m_pDC->SelectPalette(m_pOldPalette, FALSE);

	if (m_pDC)
		delete m_pDC;

	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


BOOL CSDIView::OnEraseBkgnd(CDC* )
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	return TRUE;
}


void CSDIView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (cy > 0)
	{
		glViewport(0, 0, cx, cy);

		if ((m_oldRect.right > cx) || (m_oldRect.bottom > cy))
			RedrawWindow();

		m_oldRect.right = cx;
		m_oldRect.bottom = cy;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLdouble)cx / cy, 3.0f, 7.0f);
		glMatrixMode(GL_MODELVIEW);
	}
}