#ifndef CFilterOptions_H
#define CFilterOptions_H

struct CFilterOptions
{
	CFilterOptions(void)
	{
		m_bCheckboxes[0] = false;
		m_bCheckboxes[1] = false;
		m_bCheckboxes[2] = false;
		m_bCheckboxes[3] = false;
		m_iComboBoxes[0] = -1;
		m_iComboBoxes[1] = -1;
		m_iComboBoxes[2] = -1;
		m_strEditBoxes[0] = "";
		m_strEditBoxes[1] = "";
		m_strEditBoxes[2] = "";
	};

	bool						m_bCheckboxes[4];
	uint32				m_iComboBoxes[3];
	std::string					m_strEditBoxes[3];
};

#endif