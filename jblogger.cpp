//
//  jblogger.cpp
//  Juicebox
//
//  Created by Justin Graves on 4/22/12.
//  Copyright (c) 2012 Infegy, Inc. All rights reserved.
//

#include "jblogger.h"
#include <cstdio>
#include <ctime>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdarg.h>

using namespace std;

static string JBLogLevelNames[] = { "TRACE", "DEBUG", "MESSAGE", "WARNING", "ERROR", "FATAL", "" };

void JBLogger::setup(string filename, JBLogLevels print_at, JBLogLevels log_at) {
	log_filename = filename;
	print_level = print_at;
	log_level = log_at;
}

void JBLogger::log(JBLogLevels lvl, string msg) {
	if(lvl < print_level && lvl < log_level)
		return;
	
	time_t rawtime;
	struct tm * timeinfo;
	char time_buffer[80];
	
	time (&rawtime);
	timeinfo = localtime(&rawtime);
	
	strftime(time_buffer, 80, "%Y-%m-%d @ %H:%M:%S", timeinfo);
	
	if(lvl >= print_level)
		cout << time_buffer << " [" << JBLogLevelNames[lvl] << "] " << msg << endl;
	if(lvl >= log_level) {
		ofstream f;
		f.open(log_filename, fstream::out | fstream::app);
		if(f.is_open())
			f << time_buffer << " [" << JBLogLevelNames[lvl] << "] " << msg << endl;
		f.close();
	}
}

void JBLogger::logf(JBLogLevels lvl, const char * fmt, ...) {
	va_list vararg;
	va_start(vararg, fmt);
	
	char * text_buffer = NULL;
	int len = vasprintf(&text_buffer, fmt, vararg);
	va_end(vararg);
	
	if(!text_buffer)
		return;
	
	if(!len) {
		free(text_buffer);
		return;
	}
	
	string s(text_buffer, len);
	free(text_buffer);
	
	log(lvl, s);
}