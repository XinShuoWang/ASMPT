
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
	ASMPT::InsertEventOption insert_option_;

	// All operations of deleting nodes will be recorded in this structure
	ASMPT::DeleteEventOption delete_option_;

private:
	/*
	 * This function is used to determine whether the following conditions will occur,
	 * resulting in the inability to add new nodes:
	 *
	 * 1. When the sum of the widths of all nodes exceeds the width of the window, new nodes cannot be added.
	 * 2. When the height of the new node is greater than the height of the window, it cannot be added.
	 */
	bool HasEnoughSpace(std::shared_ptr<ASMPT::Shape>);

	/*
	 * This function calculates what the inserted value should be
	 * based on the value inside the insert_option_ variable
	 */
	ASMPT::ShapeValue GetInsertValue();

	/*
	 * The abstracted node insertion function only performs the node insertion operation 
	 * according to the configuration in the insert_option_ variable, which can fully simplify
	 * the operation logic of the insertion, and can also reduce the coupling 
	 * between the rendering logic and the user input logic.
	 */
	void DoInsert();

	/*
	 * The abstract delete node function only performs delete operations according to the 
	 * configuration in the delete_option_ variable, which can reduce the coupling 
	 * between user input logic and rendering logic
	 */
	void DoDelete();

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
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
