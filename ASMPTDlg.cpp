
// ASMPTDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ASMPT.h"
#include "ASMPTDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CASMPTDlg 对话框



CASMPTDlg::CASMPTDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ASMPT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CASMPTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CASMPTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INSERT, &CASMPTDlg::OnBnClickedInsert)
	ON_LBN_SELCHANGE(IDC_ADD_SHAPE, &CASMPTDlg::OnLbnSelchangeAddShape)
	ON_LBN_SELCHANGE(IDC_ADD_DIR, &CASMPTDlg::OnLbnSelchangeAddDir)
	ON_BN_CLICKED(IDC_DELETE, &CASMPTDlg::OnBnClickedDelete)
	ON_LBN_SELCHANGE(IDC_DEL_TARGET, &CASMPTDlg::OnLbnSelchangeDelTarget)
	ON_LBN_SELCHANGE(IDC_ADD_COLOR, &CASMPTDlg::OnLbnSelchangeAddColor)
	ON_LBN_SELCHANGE(IDC_ADD_WIDTH, &CASMPTDlg::OnLbnSelchangeAddWidth)
	ON_LBN_SELCHANGE(IDC_ADD_HEIGHT, &CASMPTDlg::OnLbnSelchangeAddHeight)
	ON_LBN_SELCHANGE(IDC_ADD_REFERENCE, &CASMPTDlg::OnLbnSelchangeAddReference)
END_MESSAGE_MAP()


// CASMPTDlg 消息处理程序

BOOL CASMPTDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	/*
	 * 1. init 4 element
	 * 2. init static ListBox
	 *	2.1 init Shape ListBox
	 *	2.2. init method ListBox
	 *	2.3. init color ListBox
	 *	2.4. init width and height ListBox
	 * 3. init dynamic ListBox
	 */

	 // 1. init 4 element
	int init_element_num = 4;
	for (int i = 1; i <= init_element_num; ++i) {
		// Initialize graphic_elements_ with ASMPT::DefaultShape
		graphic_elements_.push_back(std::make_shared<ASMPT::DefaultShape>(i, ASMPT::INIT_WIDTH,
			ASMPT::INIT_HEIGHT, ASMPT::INIT_COLOR));
	}

	// 2.1 init Shape ListBox
	CListBox* lb = (CListBox*)(this->GetDlgItem(IDC_ADD_SHAPE));
	for (auto s : ASMPT::SHAPE_STR) lb->AddString(CString(s));
	// 2.2 init method ListBox
	lb = (CListBox*)(this->GetDlgItem(IDC_ADD_DIR));
	for (auto s : ASMPT::DIR_STR) lb->AddString(CString(s));
	// 2.3 init color ListBox
	lb = (CListBox*)(this->GetDlgItem(IDC_ADD_COLOR));
	for (auto s : ASMPT::COLOR_STR) lb->AddString(CString(s));
	// 2.4 init width and height ListBox
	CListBox* w_lb = (CListBox*)(this->GetDlgItem(IDC_ADD_WIDTH));
	CListBox* h_lb = (CListBox*)(this->GetDlgItem(IDC_ADD_HEIGHT));
	for (int i = ASMPT::SIZE_START; i <= ASMPT::SIZE_END; i += ASMPT::SIZE_STEP) {
		CString str;
		str.Format(_T("%d"), i);
		w_lb->AddString(str);
		h_lb->AddString(str);
	}

	// 3. init dynamic ListBox
	UpdateController();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CASMPTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CASMPTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		// Init paint
		PaintGraph();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CASMPTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CASMPTDlg::CanInsert(std::shared_ptr<ASMPT::Shape> shape)
{
	// Get window's width and height
	CRect rect;
	GetClientRect(rect);
	uint32_t window_width = rect.Width(), window_height = rect.Height();

	// If the height exceeds the height of the window, then do not draw
	if (shape->GetWidth() > window_height) return false;

	uint32_t total_width = 0;
	for (auto element : graphic_elements_) total_width += element->GetWidth();

	// If the width exceeds the width of the window, then do not draw
	if (total_width + shape->GetWidth() > window_width) return false;
	return true;
}

void CASMPTDlg::ClearGraph()
{
	CRect rect;
	GetClientRect(rect);
	RedrawWindow(CRect(0, 0, rect.Width(), rect.Height()));
}

void CASMPTDlg::PaintGraph()
{
	uint32_t element_num = 0, element_total_width = 0;
	for (auto element : graphic_elements_) {
		element_num++;
		element_total_width += element->GetWidth();
	}

	CRect rect;
	GetClientRect(rect);
	// If there are 4 elements in the graph, then there will be 5 gaps
	uint32_t space_width = (rect.Width() - element_total_width) / (element_num + 1);

	/*
	 *         The coordinate system in MFC is different from the coordinate system in mathematics.
	 *		   The following is a schematic diagram of the MFC coordinate system.
	 *
	 *         ----------------------------------------------> x
	 *        |
	 *        |
	 *        |
	 *        |               Shape is placed here.
	 *        |
	 *        |
	 *        |
	 *        |
	 *        y
	 */


	 // Draw a string of graphics at one-third of the window height
	uint32_t x = 0, y = rect.Height() / 3;

	CDC* cdc = GetDC();
	for (auto element : graphic_elements_) {
		x += space_width;
		// Each figure is abstracted into squares for calculating intervals
		x += element->GetWidth() / 2;

		// x, y are the barycentric coordinates of each shape
		element->Draw(x, y, cdc);

		x += element->GetWidth() / 2;
	}
}

void CASMPTDlg::UpdateController()
{
	// clear all elments
	CListBox* add_lb = (CListBox*)(this->GetDlgItem(IDC_ADD_REFERENCE));
	while (add_lb->GetCount() > 0) add_lb->DeleteString(0);
	CListBox* del_lb = (CListBox*)(this->GetDlgItem(IDC_DEL_TARGET));
	while (del_lb->GetCount() > 0) del_lb->DeleteString(0);

	// re-fill element
	for (auto element : graphic_elements_) {
		CString str;
		str.Format(_T("%.3f"), element->GetValue());
		add_lb->AddString(str);
		del_lb->AddString(str);
	}
}

void CASMPTDlg::RePaint()
{
	ClearGraph();
	PaintGraph();
	UpdateController();
}

void CASMPTDlg::OnBnClickedInsert()
{
	/*
	 * If graphic_elements_ is empty when inserting, then construct the node
	 * according to the DEFAULT_SHAPE_VALUE and insert it. At this time, it
	 * will not check whether insert_option_.reference_ is set.
	 */
	if (graphic_elements_.empty()) {
		switch (insert_option_.shape_type_) {
		case ASMPT::ShapeType::ShapeRectangle: {
			auto node = std::make_shared<ASMPT::Rectangle>(ASMPT::DEFAULT_SHAPE_VALUE, insert_option_.width_,
				insert_option_.height_, insert_option_.color_);
			graphic_elements_.push_back(node);
			break;
		}
		case ASMPT::ShapeType::ShapeSquare: {
			auto node = std::make_shared<ASMPT::Square>(ASMPT::DEFAULT_SHAPE_VALUE, insert_option_.width_,
				insert_option_.color_);
			graphic_elements_.push_back(node);
			break;
		}
		case ASMPT::ShapeType::ShapeCircle: {
			auto node = std::make_shared<ASMPT::Circle>(ASMPT::DEFAULT_SHAPE_VALUE, insert_option_.width_,
				insert_option_.color_);
			graphic_elements_.push_back(node);
			break;
		}
		default:
			break;
		}
		RePaint();
		return;
	}

	// If graphic_elements_ is not empty and insert_option_.reference_ 
	// is not set, then the user needs to be reminded to set.
	if (insert_option_.reference_ == ASMPT::INIT_REFERENCE) {
		AfxMessageBox(_T("Please set every ListBox!"), MB_OK | MB_ICONSTOP);
		return;
	}

	int padding = 0;
	if (insert_option_.dir_ == ASMPT::InsertDirection::Behind) padding = 1;

	// Calculate the value that should be inserted
	ASMPT::ShapeValue insert_value = 0;
	if (insert_option_.reference_ == 0 && insert_option_.dir_ == ASMPT::InsertDirection::Before) {
		// If it is inserted at the beginning, then the value = the value of the first element - 1
		insert_value = graphic_elements_.front()->GetValue() - 1;
	}
	else if (insert_option_.reference_ == graphic_elements_.size() - 1 && insert_option_.dir_ == ASMPT::InsertDirection::Behind) {
		// If inserted at the end, then value = value of last element + 1
		insert_value = graphic_elements_.back()->GetValue() + 1;
	}
	else {
		// Get the value of the elements on the left and right sides
		ASMPT::ShapeValue left, right;
		if (insert_option_.dir_ == ASMPT::InsertDirection::Before) {
			left = graphic_elements_[insert_option_.reference_ - 1]->GetValue();
			right = graphic_elements_[insert_option_.reference_]->GetValue();
		}
		else {
			left = graphic_elements_[insert_option_.reference_]->GetValue();
			right = graphic_elements_[insert_option_.reference_ + 1]->GetValue();
		}
		insert_value = (left + right) / 2;
	}

	// Create node, insert data node
	std::shared_ptr<ASMPT::Shape> node;
	if (insert_option_.shape_type_ == ASMPT::ShapeType::ShapeRectangle) {
		node = std::make_shared<ASMPT::Rectangle>(insert_value, insert_option_.width_, insert_option_.height_, insert_option_.color_);
	}
	else if (insert_option_.shape_type_ == ASMPT::ShapeType::ShapeSquare) {
		node = std::make_shared<ASMPT::Square>(insert_value, insert_option_.width_, insert_option_.color_);
	}
	else {
		node = std::make_shared<ASMPT::Circle>(insert_value, insert_option_.width_, insert_option_.color_);
	}

	// Insert if there is enough space, otherwise alert the user
	if (CanInsert(node)) {
		graphic_elements_.insert(graphic_elements_.begin() + insert_option_.reference_ + padding, node);
	}
	else {
		AfxMessageBox(_T("There is no enough space!"), MB_OK | MB_ICONSTOP);
	}
	RePaint();
	insert_option_.reference_ = ASMPT::INIT_REFERENCE;
}


void CASMPTDlg::OnLbnSelchangeAddShape()
{
	int index = ((CListBox*)GetDlgItem(IDC_ADD_SHAPE))->GetCurSel();
	if (index != LB_ERR) {
		switch (index) {
		case 0:
			insert_option_.shape_type_ = ASMPT::ShapeType::ShapeRectangle;
			((CListBox*)GetDlgItem(IDC_ADD_HEIGHT))->EnableWindow(true);
			break;
		case 1:
			insert_option_.shape_type_ = ASMPT::ShapeType::ShapeSquare;
			((CListBox*)GetDlgItem(IDC_ADD_HEIGHT))->EnableWindow(false);
			break;
		case 2:
			insert_option_.shape_type_ = ASMPT::ShapeType::ShapeCircle;
			((CListBox*)GetDlgItem(IDC_ADD_HEIGHT))->EnableWindow(false);
			break;
		default:
			break;
		}
	}
}


void CASMPTDlg::OnLbnSelchangeAddDir()
{
	int index = ((CListBox*)GetDlgItem(IDC_ADD_DIR))->GetCurSel();
	if (index != LB_ERR) {
		switch (index) {
		case 0:
			insert_option_.dir_ = ASMPT::InsertDirection::Before;
			break;
		case 1:
			insert_option_.dir_ = ASMPT::InsertDirection::Behind;
			break;
		default:
			break;
		}
	}
}


void CASMPTDlg::OnBnClickedDelete()
{
	// If no element has been selected to delete, prompt the user to make a selection
	if (delete_option_.reference_ == ASMPT::INIT_REFERENCE) {
		AfxMessageBox(_T("Please set delete ListBox!"), MB_OK | MB_ICONSTOP);
		return;
	}

	graphic_elements_.erase(graphic_elements_.begin() + delete_option_.reference_);
	RePaint();
	delete_option_.reference_ = ASMPT::INIT_REFERENCE;
}


void CASMPTDlg::OnLbnSelchangeDelTarget()
{
	int index = ((CListBox*)GetDlgItem(IDC_DEL_TARGET))->GetCurSel();
	if (index == LB_ERR) return;
	delete_option_.reference_ = index;
}


void CASMPTDlg::OnLbnSelchangeAddColor()
{
	int index = ((CListBox*)GetDlgItem(IDC_ADD_COLOR))->GetCurSel();
	if (index != LB_ERR) {
		switch (index) {
		case 0:
			insert_option_.color_ = ASMPT::ShapeColor::Red;
			break;
		case 1:
			insert_option_.color_ = ASMPT::ShapeColor::Green;
			break;
		case 2:
			insert_option_.color_ = ASMPT::ShapeColor::Blue;
			break;
		default:
			break;
		}
	}
}


void CASMPTDlg::OnLbnSelchangeAddWidth()
{
	int index = ((CListBox*)GetDlgItem(IDC_ADD_WIDTH))->GetCurSel();
	if (index == LB_ERR) return;
	insert_option_.width_ = ASMPT::SIZE_START + index * ASMPT::SIZE_STEP;
}


void CASMPTDlg::OnLbnSelchangeAddHeight()
{
	int index = ((CListBox*)GetDlgItem(IDC_ADD_HEIGHT))->GetCurSel();
	if (index == LB_ERR) return;
	insert_option_.height_ = ASMPT::SIZE_START + index * ASMPT::SIZE_STEP;
}


void CASMPTDlg::OnLbnSelchangeAddReference()
{
	int index = ((CListBox*)GetDlgItem(IDC_ADD_REFERENCE))->GetCurSel();
	if (index == LB_ERR) return;
	insert_option_.reference_ = index;
}
