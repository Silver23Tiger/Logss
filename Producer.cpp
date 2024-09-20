// C Program for Message Queue (Writer Process) 
#include <stdio.h> 
#include <iostream>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"  
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/version.h>

#define MAX 10 

// structure for message queue 
struct mesg_buffer { 
	long mesg_type; 
	char mesg_text[100]; 
} message; 

int main() 
{ 
	// auto logger = spdlog::stdout_color_mt("console");
	// logger->info("This an Info Log");
	key_t key; 
	int msgid; 
	auto logger = spdlog::stdout_color_st("console");
	auto file_logger = spdlog::basic_logger_mt("file_logger","/home/muhammad-fardan/projects1/Parsing/producerlogs.txt");
    logger->warn("Enter correct data type");
	file_logger->warn("Enter Correct Data");
	key = ftok("Sample",67);
	
	if(key == -1)
	{
		logger->warn("ftok not running smoothly!");
		file_logger->warn("ftok not running smoothly!");
		file_logger->error("ftok returning -1");
	}
	else 
	{
		logger->info("ftok running smoothly");
	    file_logger->info("ftok running smoothly");
		logger->info("ftok returning 1");
	
	}
    std::cout << "spdlog version: " 
              << SPDLOG_VER_MAJOR << "." 
              << SPDLOG_VER_MINOR << "." 
              << SPDLOG_VER_PATCH << std::endl;

	msgid = msgget(key, 0666 | IPC_CREAT); 
	if(msgid == -1)
	{
		logger->error("Error in msggets");
		logger->error("msggets return -1" );
		file_logger->error("Error in msggets");
		file_logger->error("msggets return -1" );
	}
	else
	{
		logger->info("msggets running smoothly");
		logger->info("msggets return 1" );
		file_logger->info("msggets rinning smoothly");
		file_logger->info("msggets return 1" );
	}

	message.mesg_type = 1; 
	printf("Write Data : "); 
	fgets(message.mesg_text,MAX,stdin); 
	msgsnd(msgid, &message, sizeof(message), 0); 
	printf("Data send is : %s \n", message.mesg_text); 
	return 0; 
} 
