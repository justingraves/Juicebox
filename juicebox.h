//
//  datafile.h
//  Juicebox
//
//  Created by Justin Graves on 4/17/12.
//  Copyright (c) 2012 Infegy, Inc. All rights reserved.
//

#ifndef Juicebox_juicebox_h
#define Juicebox_juicebox_h

#include <fstream>
#include <string>
#include <vector>
#include "jbtypes.h"
#include "jblogger.h"

using namespace std;

class JuiceboxSettings {
public:
	bool autocompress;		// True will try to compress data rows. Compression is only used if it actually shrinks data.
	uint64 data_file_limit;	// This will trigger creation of new data files at this size limit
	uint64 idx_cache_size;	// Maximum size (in bytes) of the index cache
	string data_path;		// Path to data file(s)
	string idx_path;		// Path to index file
	string log_filename;	// Filename for log
	
	JuiceboxSettings() : data_path("./"), idx_path("./"), log_filename("juicebox.log") {
		autocompress = true;
		data_file_limit = 0xFFFFFFFFFFFFFFFF;
		idx_cache_size = 8*1024*1024;	// 8 MB
	}
};

class JuiceboxMeta {	// Meta information (number of rows, version, size, etc.)
public:
	uint version;			// File version
	string name;			// Database name
	uint64 rows;			// Total number of rows stored
	uint64 storage_size;	// Stored (compressed + headers) size of data
	uint64 data_size;		// Uncompressed full size of all stored data
	uint16 data_file_count;	// Total number of data files
	jb_time min_data_time;	// Minimum timestamp of stored data	(should only change once)
	jb_time max_data_time;	// Maximum timestamp of stored data (changes as data is added)
	
	void defaults() {
		version = 1;
		name = "";
		rows = 0;
		storage_size = sizeof(JuiceboxMeta);
		data_size = 0;
		data_file_count = 0;
		min_data_time = 0;
		max_data_time = 0;
	}
};

struct JBFileRef {
	fstream f;
	string name;
};

class Juicebox {
public:
	Juicebox();
	
	bool load(string db_name, JuiceboxSettings jbs);
	
	void unload(void);
	
	// Copy
	Juicebox(const Juicebox& other);
	
	// Move
	Juicebox(Juicebox&& other);
	
	// Assignment
	Juicebox & operator= (const Juicebox & other);
	
	~Juicebox();
	
protected:
	vector<JBFileRef> data_files;	// Data files for DB data. Pair of file stream and filename.
	
	JBFileRef idx_file;
	
	JuiceboxMeta meta;	
	JuiceboxSettings settings;
	JBLogger logger;
};

#endif
