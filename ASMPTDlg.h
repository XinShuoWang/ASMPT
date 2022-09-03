
// ASMPTDlg.h: 头文件
//

#pragma once

#include "Values.h"
#include "EventOption.h"

#include <vector>
#include <memory>


// CASMPTDlg 对话框
class CASMPTDlg : public CDialogEx
{
// 构造
public:
	CASMPTDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ASMPT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	/* 
	 * This data structure is used as the interaction hub between the rendering module and the user module.
	 * The rendering module renders according to this data structure, and the user module will operate this
	 * data structure to achieve the purpose of adding or deleting.
	 * 
	 * Although using std::list may be more in line with the requirements,
	 * in order to facilitate the subsequent use of the index to insert nodes directly,
	 * I still use std::vector, and in the case of a small amount of data, there is almost 
	 * no performance gap between std::vector and std::list.
	 * 
	 * The use of pointers is to facilitate the use of C++'s polymorphic features.
	 * 
	 * Using smart pointers can reduce the mental burden of memory management.
	 */
	std::vector<std::shared_ptr<ASMPT::Shape>> graphic_elements_;
	
	// All operations of adding nodes will be recorded in this structure
	ASMPT::AddEventOption insert_option_;

	// All operations of deleting nodes will be recorded in this structure
	ASMPT::DelEventOption delete_option_;

private:
	/*
	 * This function is used to determine whether the following conditions will occur,
	 * resulting in the inability to add new nodes:
	 * 
	 * 1. When the sum of the widths of all nodes exceeds the width of the window, new nodes cannot be added.
	 * 2. When the height of the new node is greater than the height of the window, it cannot be added.
	 */
	bool CanInsert(std::shared_ptr<ASMPT::Shape>);

	// Clean up the graphics in the window
	void ClearGraph();

	// Render according to the data in this->graphic_elements_
	void PaintGraph();

	// When adding or deleting elements, the corresponding ListBox also needs to be updated
	void UpdateController();

	// Just a collection of several operations, easy to call
	void RePaint();

public:
	afx_msg void OnBnClickedInsert();
	afx_msg void OnLbnSelchangeAddShape();
	afx_msg void OnLbnSelchangeAddDir();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnLbnSelchangeDelTarget();
	afx_msg void OnLbnSelchangeAddColor();
	afx_msg void OnLbnSelchangeAddWidth();
	afx_msg void OnLbnSelchangeAddHeight();
	afx_msg void OnLbnSelchangeAddReference();
};
