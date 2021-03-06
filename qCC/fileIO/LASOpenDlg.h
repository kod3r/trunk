//##########################################################################
//#                                                                        #
//#                            CLOUDCOMPARE                                #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#          COPYRIGHT: EDF R&D / TELECOM ParisTech (ENST-TSI)             #
//#                                                                        #
//##########################################################################

#ifndef CC_LAS_OPEN_DIALOG
#define CC_LAS_OPEN_DIALOG

//GUIs generated by Qt Designer
#include <ui_openLASFileDlg.h>

//system
#include <string.h>
#include <vector>

enum LAS_FIELDS {	LAS_X					= 0,
					LAS_Y					= 1,
					LAS_Z					= 2,
					LAS_INTENSITY			= 3,
					LAS_RETURN_NUMBER		= 4,
					LAS_NUMBER_OF_RETURNS	= 5,
					LAS_SCAN_DIRECTION		= 6,
					LAS_FLIGHT_LINE_EDGE	= 7,
					LAS_CLASSIFICATION		= 8,
					LAS_SCAN_ANGLE_RANK		= 9,
					LAS_USER_DATA			= 10,
					LAS_POINT_SOURCE_ID		= 11,
					LAS_RED					= 12,
					LAS_GREEN				= 13,
					LAS_BLUE				= 14,
					LAS_TIME				= 15,
					//Sub fields
					LAS_CLASSIF_VALUE		= 16,
					LAS_CLASSIF_SYNTHETIC	= 17,
					LAS_CLASSIF_KEYPOINT	= 18,
					LAS_CLASSIF_WITHHELD	= 19,
					//Invald flag
					LAS_INVALID				= 255
};

const char LAS_FIELD_NAMES[][28] = {"X",
									"Y",
									"Z",
									"Intensity",
									"Return Number",
									"Number of Returns",
									"Scan Direction",
									"Flightline Edge",
									"Classification",
									"Scan Angle Rank",
									"User Data",
									"Point Source ID",
									"Red",
									"Green",
									"Blue",
									"Time",
									"[Classif] Value",
									"[Classif] Synthetic flag",
									"[Classif] Key-point flag",
									"[Classif] Withheld flag",

};

//! Dialog to choose the LAS fields to load
class LASOpenDlg : public QDialog, public Ui::OpenLASFileDialog
{
public:
    
	//! Default constructor
	LASOpenDlg(QWidget* parent=0);

	//! Sets available dimensions
	void setDimensions(const std::vector<std::string>& dimensions);

	//! Whether to load a given field
	bool doLoad(LAS_FIELDS field) const;

	//! Auto-skip mode (to use the same parameters for ALL files afterwards)
	bool autoSkipMode() const;

};

#endif //CC_LAS_OPEN_DIALOG
