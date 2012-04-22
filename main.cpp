//
//  main.cpp
//  Juicebox
//
//  Created by Justin Graves on 4/17/12.
//  Copyright (c) 2012 Infegy, Inc. All rights reserved.
//

#include <iostream>
#include "juicebox.h"
#include "jblogger.h"

int main(int argc, const char * argv[])
{
	jblog_default_print_at = JBLogTrace;
	jblog_default_log_at = JBLogMessage;
	
	JBLogger logger("server.log");
	
	logger.logf(JBLogMessage, "Welcome to Juicebox");
	
	Juicebox db;
    return 0;
}

