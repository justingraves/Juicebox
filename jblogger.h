//
//  jblogger.h
//  Juicebox
//
//  Created by Justin Graves on 4/22/12.
//  Copyright (c) 2012 Infegy, Inc. All rights reserved.
//

#ifndef Juicebox_jblogger_h
#define Juicebox_jblogger_h

#include <string>
using namespace std;

enum JBLogLevels {
	JBLogTrace = 0,
	JBLogDebug,
	JBLogMessage,
	JBLogWarning,
	JBLogError,
	JBLogFatal,
	JBLogLevelCount,
};

static JBLogLevels jblog_default_print_at = JBLogMessage;
static JBLogLevels jblog_default_log_at = JBLogWarning;

class JBLogger {
public:
	JBLogger() : log_filename("jb.log"), print_level(JBLogTrace), log_level(JBLogWarning) {}
	JBLogger(string filename, JBLogLevels print_at = jblog_default_print_at, JBLogLevels log_at = jblog_default_log_at) : log_filename(filename), print_level(print_at), log_level(log_at) {}
	~JBLogger() { }
	
	void setup(string filename, JBLogLevels print_at = jblog_default_print_at, JBLogLevels log_at = jblog_default_log_at);
	
	void log(JBLogLevels lvl, string msg);
	void logf(JBLogLevels lvl, const char * fmt, ...);
	
private:
	string log_filename;
	JBLogLevels print_level;
	JBLogLevels log_level;
};

#endif
