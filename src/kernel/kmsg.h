#include <string.h>

#define KMSG_LVL_WARNING 		0
#define KMSG_LVL_ERROR 			1
#define KMSG_LVL_MESSAGE 		2
#define KMSG_LVL_INFORMATION 	3
#define KMSG_LVL_NOTE 			4
#define KMSG_LVL_FATAL 			5

#define KMSG_WARNING(SOURCE, MESSAGE)		(kmsg(KMSG_LVL_WARNING, 	SOURCE, MESSAGE))
#define KMSG_ERROR(SOURCE, MESSAGE)			(kmsg(KMSG_LVL_ERROR,		SOURCE, MESSAGE))
#define KMSG_MESSAGE(SOURCE, MESSAGE)		(kmsg(KMSG_LVL_MESSAGE,		SOURCE, MESSAGE))
#define KMSG_INFORMATION(SOURCE, MESSAGE)	(kmsg(KMSG_LVL_INFORMATION,	SOURCE, MESSAGE))
#define KMSG_NOTE(SOURCE, MESSAGE)			(kmsg(KMSG_LVL_NOTE,		SOURCE, MESSAGE))
#define KMSG_FATAL(SOURCE, MESSAGE)			(kmsg(KMSG_LVL_FATAL,		SOURCE, MESSAGE))

//String kmsgGen(int __level, String __source, String __message);
void kmsg(int __level, String __source, String __message);
