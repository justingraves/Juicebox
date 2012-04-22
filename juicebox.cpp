//
//  database.cpp
//  Juicebox
//
//  Created by Justin Graves on 4/22/12.
//  Copyright (c) 2012 Infegy, Inc. All rights reserved.
//

#include "juicebox.h"

Juicebox::Juicebox() {
	meta.defaults();
}

bool Juicebox::load(string db_name, JuiceboxSettings jbs) {
	unload();
	settings = jbs;
	logger.setup(settings.log_filename);
	
	if(settings.data_path.length() < 1) {
		logger.log(JBLogError, "Juicebox::load() got blank data_path");
		return false;
	}
		
	if(settings.idx_path.length() < 1) {
		logger.log(JBLogError, "Juicebox::load() got blank idx_path");
		return false;
	}
	
	// Try to open meta file
	//if(settings.data_path[settings.data_path.length()-1]
	
	return false;
}

void Juicebox::unload() {
	// TODO Flush buffers
	
	
	// Close data files
	for(auto &df : data_files) {
		if(df.f.is_open())
			df.f.close();
	}
	// Close index file
	if(idx_file.f.is_open()) {
		idx_file.f.close();
	}
	
	meta.defaults();
	
	// TODO Free buffers, caches...
}

// Copy
Juicebox::Juicebox(const Juicebox& other) {
	
}

// Move
Juicebox::Juicebox(Juicebox&& other) {
	
}

// Assignment
Juicebox & Juicebox::operator= (const Juicebox & other) {
	return *this;
}

Juicebox::~Juicebox() {
	unload();
}