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

using namespace std;

class JuiceboxSettings {
public:
	bool autocompress;		// True will try to compress data rows. Compression is only used if it actually shrinks data.
	uint64 data_file_limit;	// This will trigger creation of new data files at this size limit
	uint64 idx_cache_size;	// Maximum size (in bytes) of the index cache
	string data_path;		// Path to data file(s)
	string idx_path;		// Path to index file
	
	JuiceboxSettings() : data_path("./"), idx_path("./") {
		autocompress = true;
		data_file_limit = 0xFFFFFFFFFFFFFFFF;
		idx_cache_size = 8*1024*1024;	// 8 MB
	}
};

class Juicebox {
public:
	Juicebox();
	
	bool Load(string db_name, JuiceboxSettings jbs);
	
	// Copy
	Juicebox(const Juicebox& other);
	
	// Move
	Juicebox(Juicebox&& other);
	
	// Assignment
	Juicebox & operator= (const Juicebox & other);
	
	~Juicebox();
	
protected:
	vector<pair<fstream, string>> data_files;	// Data files for DB data. Pair of file stream and filename.
	
	fstream	idx_file;		// Index file stream
	string idx_filename;	// Index file name
	
	struct JuiceboxMeta {	// Meta information (number of rows, version, size, etc.)
		uint version;			// File version
		string name;			// Database name
		uint64 rows;			// Total number of rows stored
		uint64 storage_size;	// Stored (compressed + headers) size of data
		uint64 data_size;		// Uncompressed full size of all stored data
		uint16 data_file_count;	// Total number of data files
		jb_time min_data_time;	// Minimum timestamp of stored data	(should only change once)
		jb_time max_data_time;	// Maximum timestamp of stored data (changes as data is added)
	} meta;
	
	JuiceboxSettings settings;
};

#endif
