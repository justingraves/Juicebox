//
//  datarow.h
//  Juicebox
//
//  Created by Justin Graves on 4/17/12.
//  Copyright (c) 2012 Infegy, Inc. All rights reserved.
//

#ifndef Juicebox_datarow_h
#define Juicebox_datarow_h

#include "jbtypes.h"

struct JBDataRow {
	jb_id id;
	jb_row_size size;
	uint8 * data;
};

#endif
